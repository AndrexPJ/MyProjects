import sys

sys.path.append("./Errors")
import Errors.errors as errors
sys.path.pop()

###########################################
class requestLine:
        method = ""
        request_uri = ""
        http_version = ""
        parametrs = ""
        def __init__(self,string):
                words = string.split()
                if(len(words) != 3):
                        raise errors.ClientError(400,"Bad Request")
                self.method = words[0]
                tmp_req = words[1].split('?',1)
                if(len(tmp_req) == 2):
                        self.parametrs = tmp_req[1]
                self.request_uri = tmp_req[0]        
                self.http_version = words[2]

###########################################
###########################################

class Request:
       def __init__(self,string,end_line):
                words = string.split(end_line)
                if(len(words) < 1):
                        raise errors.ClientError(400,"Bad Request")
                self.requestline = requestLine(words[0])
                #(self.headers,self.body) = self.__headers_and_body__(words[1:])
       def __headers_and_body__(self,words):
                body = []
                headers = {}
                index = 0
                for line in words:
                        if (len(line)==0):
                                break
                        index+=1
                        tmp = line.split(':',1)
                        headers[tmp[0]]=tmp[1]
                while (index < len(words)-1) & (len(words[index])==0):
                        index+=1
                body = words[index:]
                return (headers,body)
                        
       def getRequestLine(self):
                return self.requestline
               
