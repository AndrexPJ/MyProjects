module Partition where

getPartition :: Int -> Int -> Int -> Int -> Int -> Int -> [((Int,Int),((Int,Int),(Int,Int)))]
getPartition imageW imageH partW partH dW dH = filter (\(_,((dw,dh),(dW,dH)))->(dw <= imageW) && (dh <= imageH) && (dW <= imageW) && (dH <= imageH)) 
                                               $ concat $ map (\dh -> map(\dw ->((round ((fromIntegral dh)/(fromIntegral partH)),round ((fromIntegral dw)/(fromIntegral partW))),((dw,dh),(dw+partW,dh+partH)) ) ) 
                                               [0,dW+partW..imageW-(partW+dW)]) [0,dH+partH..imageH-(partH+dH)]








