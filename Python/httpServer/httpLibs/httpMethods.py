import sys

import ConfigParser
import os.path

sys.path.append("./Errors")
import Errors.errors as errors


sys.path.append("./fileDriver")
import fileDriver.fileDriver as fileDriver 

sys.path.append("./pageGen")
import pxGen


########################################################
########################################################
class method_producer:
       def __init__(self):
                self.__config__ = ConfigParser.RawConfigParser()
                self.__config__.read('./cfgs/main.cfg')
                self.__default_pg__ = self.__config__.get('mproducer', 'default_page_name')
                self.__fdriver__ = fileDriver.driver()
                self.__pgenerator__ = pxGen.pxHTMLGenerator("./pageGen/default.html")
       def GET(self,path,params):
                if(path[len(path)-1] == "/"):
                        path = path + self.__default_pg__
                if(path.find('.') == -1):
                        tmp = path.split('/')
                        return self.__pgenerator__.generate(tmp[len(tmp)-1],params)
                        
                return self.__fdriver__.getfile(path)

       def produce(self,method_name):
                try:
                        return getattr(self,method_name)
                except AttributeError:
                        raise errors.ClientError(405,"Method Not Allowed")

########################################################
########################################################

