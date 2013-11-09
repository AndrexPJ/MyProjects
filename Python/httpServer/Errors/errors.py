

class Error(Exception):
        def __init__(self,code,msg):
                self.code = code
                self.msg = msg
        def __str__(self):
                return str(self.code)+" "+self.msg


class ClientError(Error):
        pass

class ServerError(Error):
        pass
        



