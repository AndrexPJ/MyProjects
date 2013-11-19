import json
import requests

class APIWorker:
        def __init__(self,request_pattern,params):
                self.request_pattern = request_pattern
                self.params = params
        def __getByKeys__(self,obj,keys):
                if(keys == []):
                        return []
                key = keys[0]
                try:
                        obj_list = obj[key]
                        if (type(obj_list) is list):
                                out_list = []
                                for new_obj in obj_list:
                                        out_list.append(self.__getByKeys__(new_obj,keys[1:]))
                                return out_list
                        return obj_list
                except KeyError:
                        print "Bad key : "+key
                        return []

        def setRequest(self,request_pattern,params):
                self.request_pattern = request_pattern
                self.params = params
        def setRequestParams(self,params):
                self.params = params
        def getRequestParams(self):
                return self.params
        def getRequestPattern(self):
                return self.request_pattern
        def getInfoByKeys(self,keys_list):
                try:
                        request = requests.get(self.request_pattern % self.params)
                        jsn =  request.json()
                        out =  self.__getByKeys__(jsn,keys_list)
                        return out
                except requests.ConnectionError:
                        print "500px connection problem"
                        return []



