module ImageLoader where

import Graphics.GD

        
printM val = do
               val' <- val
               print val'                                

poly2Mono :: (Int,Int,Int,Int) -> (Int,Int,Int,Int)
poly2Mono (r,g,b,a) = (c,c,c,a)
                      where c = div (r+r+b+g+g+g) 6

takeMonoPixel coord img  = do
                             clr <- getPixel coord img
                             let (r,g,b,a) = poly2Mono $ toRGBA clr
                             let clr' = rgba r g b a
                             img_ <- setPixel coord clr' img
                             return img_

getMonoClr coord img = do
                         clr <- getPixel coord img
                         let (c,_,_,_) = toRGBA clr
                         return c
                         

loadMonoIMG fileName = do
                         img <- loadJpegFile fileName
                         (w,h) <- imageSize img
                         mapM_ (\x -> mapM_ (\y -> takeMonoPixel (x,y) img ) [0..h] ) [0..w]
                         return img

getSubImg (toplft,rightbtm) img = do
                                    let ((x1,y1),(x2,y2)) = (toplft,rightbtm)
                                    let (w,h) = (x2-x1,y2-y1)
                                    img' <- newImage (w,h)
                                    copyRegion (x1,y1) (w,h) img (0,0) img'
                                    return img'
                                    
scaleImg (w,h) img = do
                        img' <- newImage (w,h)
                        (w_,h_) <- imageSize img
                        copyRegionScaled (0,0) (w_,h_) img (0,0) (w,h) img'
                        return img'

monoImg2List' img (w,h) x y buf = if (y==h) then do return $ reverse buf
                                  else if (x==w) then do
                                          monoImg2List' img (w,h) 0 (y+1) buf
                                       else do
                                          el <- getMonoClr (x,y) img
                                          monoImg2List' img (w,h) (x+1) y (el:buf)
                                    

monoImg2List img (w,h) = monoImg2List' img (w,h) 0 0 []




sumM [] = do return 0
sumM (l:list) = do
                  s <- sumM list 
                  l' <- l
                  return (l'+s)

map2 f l1 l2 = if (length l1 == length l2) then reverse $ map2' f l1 l2 []
               else error "bad lengths in map2!!"
map2' _ [] [] buf = buf
map2' f (el1:l1) (el2:l2) buf = map2' f l1 l2 ((f el1 el2):buf)

-----------------------------------------------------------
-----------------------------------------------------------
getImgK list (w,h) = (fromIntegral s) / (fromIntegral p)
                     where s = sum list 
                           p = w*h

getImgBeta list d_ = sum $ map (\d -> ((fromIntegral d) - d_)^2) list

getImgAlpha listD listR d_ r_ = sum $ map2 (\d r -> ((fromIntegral d) - d_)*((fromIntegral r) - r_) ) listD listR     
                   
getImgOS a b d_ r_ = (r_ - s * d_,s)
                     where s = a/b

getImgBetaK img (w,h) = do
                          list <- monoImg2List img (w,h)
                          let k = getImgK list (w,h)
                          let beta = getImgBeta list k 
                          return (beta,k)
                         
getImgDrms list1 list2 = sqrt s 
                         where s = sum $ map2 (\l1 l2 ->  ( abs ((fromIntegral l1) - (fromIntegral l2)) )^2 ) list1 list2

getImgQuadD listD listR (o,s) = sum $ map2 (\d r -> (s*(fromIntegral d) + o - (fromIntegral r))^2) listD listR
-----------------------------------------------------------
-----------------------------------------------------------
getSubScaledImg (toplft,rightbtm) (w,h) img = do
                                                img_ <- getSubImg (toplft,rightbtm) img
                                                scaleImg (w,h) img_

                       
imgSize img = imageSize img

imgSave fileName img = saveJpegFile 95 fileName img


test = do
         --img <- loadMonoIMG "test.jpg"
         --(w,h) <- imgSize img
         --list <- monoImg2List img (w,h)
         let (w,h) = (2,2)
         let list1 = [10,20,30,40]
         let list2 = [1,3,3,4]
         let k1 = getImgK list1 (w,h)
         let k2 = getImgK list2 (w,h)
         print (k1,k2)
         let a = getImgAlpha list1 list2 k1 k2
         print a
         let b = getImgBeta list1 k1 
         print b
         let (o,s) = getImgOS a b k1 k2
         print (o,s)
         print $ getImgQuadD list1 list2 (o,s)
         --saveJpegFile 95 "out.jpg" img'
         return ()
