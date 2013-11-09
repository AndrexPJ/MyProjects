import pxWorker

requset_pattern =  'https://api.500px.com/v1/photos?feature=%s&consumer_key=%s&image_size=%s'
params = ("upcoming","YNGMv2DF8r2H2tFzBjAOtwPTznw0l4Ig6XBrOA1F","5")
keys_list = ["photos","image_url"]


class pxHTMLGenerator:
        def __init__(self):
                with open("./default.html", 'r') as content_file:
                        self.content = content_file.read()
                self.worker = pxWorker.pxWorker(requset_pattern,params,keys_list)

        def generate(self):
                imgs = self.worker.getImageURLs()
                self.worker.setImageSize(3)
                imgs_small = self.worker.getImageURLs()
                rtext = self.tagsGenerateFromList('<a href="%s"><img src="%s" /></a>',(imgs,imgs_small),len(imgs))
                return self.content.replace("[[MEDIAIN]]",rtext)
                
        def tagsGenerateFromList(self,pattern,args,ln):
                outStr = ""
                for i in range(ln):
                        try:
                                ar = tuple(map(lambda a: a.pop(),args))
                                outStr = outStr+self.tagsGenerate(pattern,ar)+'\n'
                        except IndexError:
                                return outStr
                return outStr
              
        def tagsGenerate(self,pattern,args):
                return pattern % args


gen = pxHTMLGenerator()

with open("./index.html", 'w') as content_file:
        content_file.write(gen.generate())
                


 





