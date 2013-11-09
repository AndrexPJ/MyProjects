
import Partition
import ImageLoader
import Data.Binary
import Graphics.GD
import System.Environment
type FInfo = ((Int,Int),(Int,Int),(Int,Int),(Int,Int),[((Int,Int),(Int,Int),(Float,Float))]) -- for serial.

-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
getResizedDomains img (imgW,imgH) (partW,partH) (dW,dH) (rankW,rankH) = 
                getResizedDomains' img (partW,partH) (rankW,rankH) parts []
                where parts = getPartition imgW imgH partW partH dW dH

getResizedDomains' _ _ _ [] buf = do return $ reverse $ buf
getResizedDomains' img (partW,partH) (rankW,rankH) (p:parts) buf =
                                     do
                                       let (n,c) = p
                                       img_ <- getSubScaledImg c (rankW,rankH) img
                                       let turple = (n,(rankW,rankH),img_)
                                       getResizedDomains' img (partW,partH) (rankW,rankH) parts (turple:buf)


getRanks img (imgW,imgH) (rankW,rankH) = getRanks' img (rankW,rankH) parts []
                                         where parts = getPartition imgW imgH rankW rankH 0 0

getRanks' _ _ [] buf = do return $ reverse buf
getRanks' img (rankW,rankH) (p:parts) buf = do
                                               let (n,c) = p
                                               img_ <- getSubImg c img
                                               let turple = (n,(rankW,rankH),img_)
                                               getRanks' img (rankW,rankH) parts (turple:buf)

getImgsWithKs :: [((Int,Int),(Int,Int), Graphics.GD.Image)] -> IO [((Int,Int),(Int,Int),([Int],(Float,Float)))]
getImgsWithKs list = getImgsWithKs' list []

getImgsWithKs' [] buf = do return $ reverse buf
getImgsWithKs' (l:list) buf = do
                                let (n,size,img) = l
                                ls <- monoImg2List img size
                                ks <- getImgBetaK img size
                                let turple = (n,size,(ls,ks))
                                getImgsWithKs' list (turple:buf)
                                

getBetterDomainN rank (d:domains) = getBetterDomainN' rank domains d (quad,(o,s))  
                                    where (nD,sizeD,(listD,(bD,kD))) = d
                                          (nR,sizeR,(listR,(bR,kR))) = rank
                                          alpha = getImgAlpha listD listR kD kR
                                          (o,s) = getImgOS alpha bD kD kR
                                          quad = getImgQuadD listD listR (o,s)

getBetterDomainN' rank [] bDmn (bQuad,(o',s')) =
                  (nR,nD,(o',s'))
                  where (nD,sizeD,(listD,(bD,kD))) = bDmn
                        (nR,sizeR,(listR,(bR,kR))) = rank


getBetterDomainN' rank (d:domains) bDmn (bQuad,(o',s')) = if (quad < bQuad) then getBetterDomainN' rank domains d (quad,(o,s))
                                                          else getBetterDomainN' rank domains bDmn (bQuad,(o',s'))  
                                                          where (nD,sizeD,(listD,(bD,kD))) = d
                                                                (nR,sizeR,(listR,(bR,kR))) = rank
                                                                alpha = getImgAlpha listD listR kD kR
                                                                (o,s) = getImgOS alpha bD kD kR
                                                                quad = getImgQuadD listD listR (o,s)



---(number,size,(list,ks))
getComparedList ranks domains = map (\r -> getBetterDomainN r domains) ranks


-----------------------------------------------------------------------------------
main = compress
-----------------------------------------------------------------------------------
compress = 
        do
          [fName] <- getArgs
          img <- loadMonoIMG fName
          size <- imgSize img
          -------------------------------------------------------------------------
          let (iW,iH) = size
          let (rW,rH) = (4,4)
          let (sW,sH) = (2,2)
          let (dW,dH) = (8,8)
          -------------------------------------------------------------------------
          ranks <- getRanks img size (rW,rH)
          ranks' <- getImgsWithKs ranks
          domains <- getResizedDomains img size (dW,dH) (sW,sH) (rW,rH)
          domains' <- getImgsWithKs domains
          print $ length domains'
          let info = getComparedList ranks' domains'
          encodeFile "out.fractal" ((iW::Int,iH::Int),(rW::Int,rH::Int),(dW::Int,dH::Int),(sW::Int,sH::Int),info)
          print "DONE!"
                                     
test = do
          img <- loadMonoIMG "test.jpg"
          size <- imgSize img
          ranks <- getRanks img size (100,100)
          (p:parts) <- getImgsWithKs ranks
          imgSave "out.jpg" img
