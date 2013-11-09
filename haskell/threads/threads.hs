import Control.Concurrent

threadFunc :: [Int] -> IO()
threadFunc list = mapM_ (\element -> putStrLn $ show element) list
		     


mainLoop :: IO ()
mainLoop = do
		--putStrLn "main"
		mainLoop

main = do
  	  forkIO (threadFunc [0..10000])
	  forkIO (threadFunc [10000..20000])
	  forkIO (threadFunc [20000..30000])
          threadDelay 10000000


