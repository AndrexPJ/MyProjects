import sys

import httpRequest
import httpResponse
import httpMethods

sys.path.append("./Errors")
import Errors.errors as errors
sys.path.pop()

class Parser:
        def __init__(self,end_line):
                self.end_line = end_line;
                self.mproducer = httpMethods.method_producer() 
        def get_response(self,request):                
                try:   
                        req = httpRequest.Request(request,self.end_line)
                        reqline = req.getRequestLine()     
                        method = self.mproducer.produce(reqline.method)
                        resp = httpResponse.Response(reqline.http_version+" 200 OK",method(reqline.request_uri,reqline.parametrs),self.end_line)
                        return resp.getresponse()
                except (errors.ClientError,errors.ServerError) as ex:
                        resp = httpResponse.Response("HTTP/1.1 "+" "+ str(ex),"",self.end_line)
                        return resp.getresponse()
                                    



#pars = Parser("\r\n")
#print pars.get_response("GET /bart.png HTTP/1.1")
