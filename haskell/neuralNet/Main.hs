import NeuralNet
import System.Random
import Debug.Trace
main = do
         putStrLn "teaching ..."
         net  <- return $ buildSimpleTNet ([[([0.0,0.0,0.0],(\x->1.0,\x->1.0)),([0.1,-0.2,0.1],(f,f')),([0.1,-0.1,0.3],(f,f'))],[([0.2,0.2,0.3],(f,f'))]])
         map  <- return $ buildSignalMap 3 [3,3,1]
         (net',map') <- netTeacher net 0.5 (buildDeltas net) map [([1.0,1.0],[0.0]),([0.0,0.0],[0.0]),([0.0,1.0],[1.0]),([1.0,0.0],[1.0])] 0.1 100000 1 0.5
         putStrLn "error is..."
         print $ testNet net' map' [([0.0,1.0],[1.0]),([1.0,0.0],[1.0]),([0.0,0.0],[0.0]),([1.0,1.0],[0.0])]


f  x = 1/(1+ exp (-x+0.5))	
f' x = fx * (1 - fx)
       where fx = f x

getRandomP :: [a] -> IO a
getRandomP pairs = randomRIO (0,(length pairs - 1)) >>= return . (pairs !!)


netTeacher net _ _ signalMap _ _ 0 _ _ = do return (net,signalMap)
netTeacher net alpha oldDeltas signalMap pairs eps maxIter n error =
                                                                    if (error < eps) then do return (net,signalMap)
                                                                    else do                                                                   
                                                                           p <- getRandomP pairs
                                                                           (net',error'',signalMap',deltas) <- return $ backPropStep net alpha oldDeltas p signalMap (0.5)
                                                                           error' <- return $ sqrt error''
                                                                           print  (n ,error,error',p)
                                                                           netTeacher net' alpha deltas signalMap' pairs eps (maxIter-1) (n+1) ((error'+error*(n-1))/n)
                                                                
                                                                                                 
           
					  
