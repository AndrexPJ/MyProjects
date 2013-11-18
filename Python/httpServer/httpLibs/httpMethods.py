import sys

import ConfigParser
import os.path

sys.path.append("./Errors/")
import Errors.errors as errors
sys.path.pop()

sys.path.append("./fileDriver/")
import fileDriver.fileDriver as fileDriver 
sys.path.pop()


class page_generator_factory:
    def __init__(self, cfg_path):
        self.__config__ = ConfigParser.RawConfigParser()
        self.__config__.read(cfg_path)
        self.generators = {}
        for (gname,gpath) in self.__config__.items('pgenerators'):
                    print "Loading page generator : [", gname ,"] from: [", gpath,"]"
                    sys.path.append(gpath)
                    try:
                        temp_module = __import__(gname)
                        print "YES"
                        sys.path.pop()
                        self.generators[gname] = temp_module.generator()
                    except ImportError:
                        print "NO"
                        sys.path.pop()
    def get_generator(self,name):
        try:
            return self.generators[name]
        except KeyError:
            raise errors.ClientError(404,"Not Found")
            
        
        

########################################################
########################################################
class method_producer:
       def __init__(self):
                self.__config__ = ConfigParser.RawConfigParser()
                self.__config__.read('./cfgs/main.cfg')
                self.__default_pg__ = self.__config__.get('mproducer', 'default_page_name')
                self.__fdriver__ = fileDriver.driver()
                self.__generator_factory__  = page_generator_factory(self.__config__.get('pgenerator_cfg','pgenerator_cfg_path'))
       def GET(self,path,params):
                if(path[len(path)-1] == "/"):
                        path = path + self.__default_pg__
                if(path.find('.') == -1):
                        tmp = path.split('/')
                        generator = self.__generator_factory__.get_generator(tmp[len(tmp)-1])
                        return generator.generate(tmp[len(tmp)-1],params)
                        
                return self.__fdriver__.getfile(path)

       def produce(self,method_name):
                try:
                        return getattr(self,method_name)
                except AttributeError:
                        raise errors.ClientError(405,"Method Not Allowed")

########################################################
########################################################
