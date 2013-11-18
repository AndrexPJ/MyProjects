import pxWorker
from jinja2 import Environment

requset_pattern =  'https://api.500px.com/v1/photos?feature=%s&consumer_key=%s&image_size=%s'
params = ("upcoming","YNGMv2DF8r2H2tFzBjAOtwPTznw0l4Ig6XBrOA1F","5")
keys_list = ["photos","image_url"]


class generator:
        def __init__(self):
                def_page_path = "./pxgen2/default.html"
                with open(def_page_path, 'r') as content_file:
                        self.content = content_file.read()
                self.worker = pxWorker.pxWorker(requset_pattern,params,keys_list)
                self.env = Environment()
        def getResizedImgUrl(self,url,size):
                tmp = url[::-1].split('.',1)
                #print tmp
                prefix = tmp[0]
                sufix  = tmp[1]
                ##print (prefix," ",sufix)
                return  (prefix+"."+str(size)+sufix[1:])[::-1]
        def generate(self,page_name,query_params):
                if(len(query_params) != 0):
                        query_words = query_params.split('&')
                        tmp = []
                        for query in query_words:
                                tmp = query.split('=')
                                if (tmp[0]=="feature"):
                                        break
                        new_params = (tmp[1],params[1],params[2])
                        self.worker.setRequestParams(new_params)
                imgs = self.worker.getImageURLs()
                imgs_small = map(lambda u : self.getResizedImgUrl(u,3),imgs)
                #self.worker.setRequestParams(params)

                return self.env.from_string(self.content).render(images = zip(imgs,imgs_small))
                
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




 





