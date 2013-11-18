import APIWorker



class pxWorker:
        def __init__(self,requset_pattern,params,keys_list):
                self.keys_list = keys_list
                self.api = APIWorker.APIWorker(requset_pattern,params)
        def getImageURLs(self):
                return self.api.getInfoByKeys(self.keys_list)
        def setRequest(self,request_pattern,params):
                self.api.setRequest(request_pattern,params)
        def setRequestParams(self,params):
                self.api.setRequestParams(params)
        def setImageSize(self,size):
                params = self.api.getRequestParams()    
                self.api.setRequestParams((params[0],params[1],str(size)))
                return True
                



        
