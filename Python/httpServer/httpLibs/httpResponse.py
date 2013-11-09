import sys

sys.path.append("./Errors")
import Errors.errors as errors

###########################################
class statusLine:
        status_line = ""
        def __init__(self,string):
                self.status_line = string
        #def __init__(self,http_version,status_code,reason_phrase,end_line):
        #        self.status_line = http_version + " " + status_code + " " + reason_phrase + end_line;
        def getline(self):
                return self.status_line
###########################################
###########################################


class Response:
        def __init__(self,status,body,end_line):
                self.status = statusLine(status)
                self.body = body;
                self.end_line = end_line
        def getresponse(self):
                return self.status.getline() + self.end_line + self.end_line + self.body;
