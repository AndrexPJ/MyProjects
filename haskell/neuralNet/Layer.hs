module Layer where
import Neuron
import Data.Array
import Debug.Trace

type Layer a = Array Int (Neuron a)

getSignals :: (Num a) => Layer a -> SignalMap a -> Int -> SignalMap a
getSignals layer signalMap layerN = getSignals' layer signalMap layerN (neuronLn)
                                    where neuronLn = snd $ bounds $ layer

getSignals' _ signalMap _ (-1) = signalMap
getSignals' layer signalMap layerN n = getSignals' layer (getSignal (layer!n) signalMap (layerN,n)) layerN (n-1)
			      
getLayerWsErrors :: (Fractional a) => SignalMap a -> Int -> [a] -> [[a]]
getLayerWsErrors signalMap layerN deltas = numMap (\n d -> getNeuronWsErrors signalMap n layerN d) deltas

changeLayerWs :: (Num a) => Layer a -> [[a]] -> Layer a
changeLayerWs layer dw = listArray (0,ln) $ map2d (\n ws -> changeNeuronWs n ws ) (elems layer) dw
			 where ln = snd $ bounds layer

buildSimpleLayer :: (Num a) => [[a]] -> (AFType a, AFType a) -> Int -> Layer a
buildSimpleLayer layer fs layerN  = listArray (0,ln) (map (\w -> buildNeuron w fs ) layer')
			            where layer' = getFullLinks layer (layerN - 1)
			                  ln = (length layer)-1


buildSimpleTLayer :: (Num a) => [([a],(AFType a,AFType a))] -> Int -> Layer a
buildSimpleTLayer layer layerN  = listArray (0,ln) (map (\(w,fs) -> buildNeuron w fs ) layer')
			            where 
                                          (ws,f) = unzip layer
                                          layer' = zip (getFullLinks ws (layerN - 1)) f
			                  ln = (length layer)-1

buildLayerMap :: (Num a) => Int -> Array Int (a,a)
buildLayerMap ln = array (0,ln-1) [ (i,(0,0)) | i <- [0..ln-1] ]

getLinksList :: (Num a) => [a] -> Int -> [Link a]
getLinksList list n = getLinksList' list n 0
getLinksList' [] _ _ = []
getLinksList' (w:list) n num = (w,n,num) : (getLinksList' list n (num+1)) 
			   
getFullLinks :: (Num a) => [[a]] -> Int -> [[Link a]]
getFullLinks [] _ = []
getFullLinks (l:layer) n = lnks : (getFullLinks layer n)
			    where lnks = getLinksList l n

getLayerF' :: (Num a) => Layer a -> [AFType a]
getLayerF' layer = map (\n -> getNeuronF' n) layer'
                   where layer' = elems layer

getNeuronL :: (Num a) => Layer a -> Int -> Neuron a
getNeuronL l n = l!n 
