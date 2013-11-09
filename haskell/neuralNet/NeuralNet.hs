module NeuralNet  where

import Neuron
import Layer
import Data.Array
import Data.Binary

type NeuralNet a = [Layer a]


getNetTestingError net map (testIn,testOut) = getError $ zipWith (-) testOut $ getOutputSignals $ getNetSignals net $ setInputSignals testIn map

testNet :: (Floating a) => NeuralNet a -> SignalMap a -> [([a],[a])] -> a
testNet net smap pairs = (\x -> x/(fromIntegral $ length pairs)) $ sum $ map (\p -> sqrt $ getNetTestingError net smap p) pairs

buildDeltas net  = map (\layer -> map (\(Neuron links _) -> [0 | _ <- [0.. snd $ bounds links] ] ) $ elems layer) net

getNetSignals :: (Num a) => NeuralNet a -> SignalMap a  -> SignalMap a
getNetSignals net signalMap = getNetSignals' net signalMap (0)
getNetSignals' [] signalMap _ = signalMap 
getNetSignals' (layer:net) signalMap n = getNetSignals' net signalMap' (n+1)
                                         where signalMap' = getSignals layer signalMap n

buildSimpleNet :: (Num a) => [[[a]]] -> (AFType a,AFType a) -> NeuralNet a   
buildSimpleNet weights fs = buildSimpleNet' weights fs 0
buildSimpleNet' [] _ _ = []
buildSimpleNet' (ws:weights) fs n = (buildSimpleLayer ws fs n) : (buildSimpleNet' weights fs (n+1) )

buildSimpleTNet :: (Num a) => [[([a],(AFType a,AFType a))]] -> NeuralNet a
buildSimpleTNet rawNeurons = buildSimpleTNet' rawNeurons 0
buildSimpleTNet' [] _ = []
buildSimpleTNet' (rawNeus:rawNeurons) n = (buildSimpleTLayer rawNeus n) : (buildSimpleTNet' rawNeurons (n+1) )

--buildRandomSimpleNet layerLns (f,f') = do
 --                                         rawNet <- map (\n ->  ([0.0|_<-[0..(layerLns!!(n-1))-1]],(\x->1.0,\x->1.0)) : [([(getRandom 1.0)|_<-[0..(layerLns!!(n-1))-1]],(f,f'))|_<-[0..(layerLns!!n)-1]]   ) [1..(length layerLns)-1]
--                                          return $ buildSimpleTNet rawNet

buildSignalMap :: (Num a) => Int -> [Int] -> SignalMap a
buildSignalMap layersCount layersLn = array (-1,layersCount-2) $ map (\n -> (n, buildLayerMap ( layersLn!!(n+1) ) ) ) [-1..layersCount-2]

getOutputSignals :: (Num a) => SignalMap a -> [a]
getOutputSignals signalMap = map (fst) $ elems $ signalMap!n
                             where n = snd $ bounds signalMap

setInputSignals :: (Num a) => [a] -> SignalMap a -> SignalMap a
setInputSignals input signalMap =  signalMap //[(-1, listArray (0,(length input)) $ (1,1) : zip input [0 | i <- [1..length input]] )]

getError :: (Floating a) => [a] -> a
getError div = (sum $ map (\x -> x^2) div)/2

getNeuronfromNet :: (Num a) => Int -> Int -> NeuralNet a -> Neuron a
getNeuronfromNet l n net = getNeuronL (net!!l) n 

changeNetWs :: (Num a) => NeuralNet a -> [[[a]]] -> NeuralNet a
changeNetWs net [] = net
changeNetWs net dws = map2d (\l dw -> changeLayerWs l dw) net dws

backPropStep :: (Floating a) => NeuralNet a -> a -> [[[a]]] -> ([a], [a]) -> SignalMap a -> a -> (NeuralNet a, a, SignalMap a, [[[a]]])
backPropStep net alpha oldDeltas pair signalMap step = (net',error, signalMap',deltas)
			                               where 
				                        (testIn,desiredOut) = pair
                                                        reallyOut = getOutputSignals signalMap'
                                                        signalMap' =  getNetSignals net $ setInputSignals testIn signalMap
                                                        div = zipWith (-) desiredOut reallyOut
				                        error = getError div
				                        deltas = zipWith (zipWith (zipWith(+))) (map(map(map(* alpha))) oldDeltas) $  
                                                                 getWsErrors signalMap' $ getErrorList (reverse net) div signalMap' step
                                                        net' = changeNetWs net deltas

getWsErrors :: (Fractional a) => SignalMap a -> [[a]] -> [[[a]]]
getWsErrors signalMap deltas = numMap (\n ds -> getLayerWsErrors signalMap n ds) deltas

getErrorList :: (Fractional a) => NeuralNet a -> [a] -> SignalMap a -> a -> [[a]]
getErrorList (layer:layers) div signalMap step = reverse $ (errors) : ( getErrorList' layers errors signalMap step layer (ln-1))
					         where errors = map (* (step))  $ zipWith (*) f's div
						       f's = zipWith (\x->x) (getLayerF' layer) (map (snd) $ elems $ signalMap!ln) 
                                                       ln =  (length layers)

getErrorList' :: (Fractional a) => [Layer a] -> [a] -> SignalMap a -> a -> Layer a -> Int -> [[a]]
getErrorList' [] _ _ _ _ _ =  []
getErrorList' (layer:layers) errors signalMap step prevLayer layerN =   (errors') : (getErrorList' layers errors' signalMap step layer (layerN-1))
								        where errors' =  map (* (step)) $ zipWith (*) f's sums
									      f's = zipWith (\x->x) (getLayerF' layer) (map (snd) $ elems $ signalMap!(layerN))
								              sums = map (\j -> getSum errors prevLayer j) [0..ln]
									      ln = snd $ bounds layer

getSum errors prevLayer j = sum $ zipWith (*) errors $ map (\nK -> getNeuronWn nK j ) (elems prevLayer)

