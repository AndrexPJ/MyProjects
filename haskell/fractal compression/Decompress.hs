--module Decompress where

import Partition
import ImageLoader
import Data.Binary
import Graphics.GD
import Data.Map
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
                                       let turple = (n,img_)
                                       getResizedDomains' img (partW,partH) (rankW,rankH) parts (turple:buf)



getColor c s o = round c'
                 where c' = (s * c + o)

mulImg img1 img2 (w,h) (o,s) (sX,sY) = mulImg' img1 img2 (w,h) (o,s) (sX,sY) (sX,sY)

mulImg' img1 img2 (w,h) (o,s) (x,y) (sX,sY) = if (y == sY+h) then do return img1
                                              else if (x == sX+w) then mulImg' img1 img2 (w,h) (o,s) (sX,(y+1)) (sX,sY)
                                              else do
                                                     clr <- getPixel (x-sX,y-sY) img2
                                                     let (c,_,_,a) = toRGBA clr
                                                     let c' =  getColor (fromIntegral c) s o
                                                     let clr' = rgba c' c' c' a
                                                     setPixel (x,y) clr' img1
                                                     mulImg' img1 img2 (w,h) (o,s) ((x+1),y) (sX,sY)

changeImg img (w,h) rank domain (o,s) = do                                          
                                           let ((x1,y1),(x2,y2)) = rank
                                           mulImg img domain (x2 - x1+1,y2 - y1+1) (o,s) (x1,y1)
                                          

decompressIter img _ [] _ _ = return img
decompressIter img (w,h) (rule:rules) mapD mapR
                                                = do 
                                                    let (nR,nD,(o,s)) = rule
                                                    let rank = mapR ! nR
                                                    let domain = mapD ! nD
                                                    img' <- changeImg img (w,h) rank domain (o,s) 
                                                    decompressIter img (w,h) rules mapD mapR
                                                  

decompress max rules img (w,h) mapR dInf = decompress' max rules img (w,h) mapR dInf 0
decompress' max rules img (w,h) mapR dInf n = if (n==max) then return img
                                                 else do
                                                        let ((w,h),(dW,dH),(sW,sH),(rW,rH)) = dInf
                                                        dms <- getResizedDomains img (w,h) (dW,dH) (sW,sH) (rW,rH)
                                                        let mapD = fromList dms  
                                                        img' <- decompressIter img (w,h) rules mapD mapR
                                                        decompress' max rules img' (w,h) mapR dInf (n+1)

saveDmns [] _ = return ()
saveDmns (d:domains) n = do
                           let (_,img) = d
                           saveJpegFile 95 ("1/"++(show n)++".jpg") img
                           saveDmns domains (n+1)

decompressMain frName fName = do
                                fr <- decodeFile frName :: IO FInfo
                                img <- loadMonoIMG fName
                                (w,h) <- imgSize img
                                let ((iOW,iOH),(rOW,rOH),(dOW,dOH),(sOW,sOH),rules) = fr
                                let (kW,kH) = ((fromIntegral w) / (fromIntegral iOW),(fromIntegral h)/ (fromIntegral iOH))
                                let (dW,dH) = (round ((fromIntegral dOW) * kW),round ((fromIntegral dOH) * kH))
                                let (rW,rH) = (round ((fromIntegral rOW) * kW),round ((fromIntegral rOH) * kH))
                                let (sW,sH) = (round ((fromIntegral sOW) * kW),round ((fromIntegral sOH) * kH))
                                let dmnInf = ((w,h),(dW,dH),(sW,sH),(rW,rH))
                                let mapR = fromList $ getPartition w h rW rH 0 0
                                img' <- decompress 1 rules img (w,h) mapR dmnInf
                                saveJpegFile 95 "test2.jpg" img'
                                return ()

main =
      do
        [frName,fName] <- getArgs  
        decompressMain frName fName

test = do
         img <- loadMonoIMG "test.jpg"
         (w,h) <- imgSize img
         (img') <- mulImg img img (w,h) (200,0.5) (0,0)
         saveJpegFile 95 "out.jpg" img'
         return ()

