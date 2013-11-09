module Neuron where
import Data.Array
import Debug.Trace
import System.Random
import Data.Binary

type AFType a = (a->a) -- type of Activation function and its derivative function
type Link a = (a,Int,Int) -- is a layer, neuron No. and its weigth
type Links a = Array Int (Link a)
type SignalMap a = Array Int (Array Int (a,a)) -- (outSignal,sum) 
data Neuron a  =  Neuron (Links a)  (AFType a ,AFType a) 

--instance (Binary a) => Binary (Neuron a)  where
--         put (Neuron arr fs) = do put arr
--                                  put fs


--instance (Show a) => Show (Neuron a) where show (Neuron arr f) =  show $ elems arr

--------------------------

--test = getFsType (f,f)
--getFsType (f,f') = (0,0)
--------------------------

getRandom :: (Num a,Random a) => a -> IO a
getRandom max = randomRIO (0,max)

getArray :: (Num a) => [Link a] -> Links a
getArray list = listArray (0,ln) list
                 where ln = (length list) - 1

getNeuronLinks :: (Num a) => Neuron a -> [Link a]
getNeuronLinks neuron = elems arr
                where Neuron arr _ = neuron

getNeuronWs :: (Num a) => Neuron a -> [a]
getNeuronWs neuron = map (\(w,_,_)->w) $ elems arr
                     where Neuron arr _ = neuron

getNeuronLinkn :: (Num a) => Neuron a -> Int -> Link a
getNeuronLinkn neuron n = arr ! n
                          where Neuron arr _  = neuron

getNeuronWn :: (Num a) => Neuron a -> Int -> a
getNeuronWn neuron n = w
                        where Neuron arr _ = neuron
                              (w,_,_) = arr ! n

getNeuronWsErrors :: (Fractional a) => SignalMap a -> Int -> Int -> a -> [a]
getNeuronWsErrors signalMap neuronN layerN delta = map (*delta) (map (fst) $ elems $ signalMap!(layerN-1))
----------------------------------------------------------------
----------------------------------------------------------------
map2d _ [] _ = []
map2d _ _ [] = []
map2d f (l1:list1) (l2:list2) = (f l1 l2) : map2d f list1 list2

numMap f list = numMap' f list 0
numMap' f (l:list) n = (f n l) : (numMap' f list (n+1))
numMap' _ [] _ = []
----------------------------------------------------------------
----------------------------------------------------------------
changeNeuronWs :: (Num a) => Neuron a -> [a] -> Neuron a
changeNeuronWs neuron dws = Neuron w' funcs
                            where w' = getArray $ map2d (\(el,n1,n2) dw -> ((el + dw),n1,n2)) (elems w) dws
                                  Neuron w funcs  = neuron

buildNeuron  :: (Num a) => [Link a] -> (AFType a, AFType a) -> Neuron a
buildNeuron weights fs = Neuron arr fs
                         where  arr = getArray weights

getSignal :: (Num a) => Neuron a -> SignalMap a -> (Int,Int) -> SignalMap a
getSignal neuron signalMap (layerN,neuronN) = signalMap // [(layerN,layerMap//[(neuronN,(outSignal,outSum))])]
                                              where   Neuron arrayLinks (actFunc,_) = neuron
                                                      links = elems arrayLinks
                                                      outSum = sum $ map (\(w,l,n) -> w * fst ((signalMap!l)!n) ) links
                                                      outSignal = actFunc outSum
                                                      layerMap = signalMap!layerN

getNeuronF' :: (Num a) => Neuron a -> AFType a
getNeuronF' neuron = f'
                     where Neuron _ (_,f') = neuron

