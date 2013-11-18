import sys

import ConfigParser
import os.path
import os

sys.path.append("./Errors/")
import Errors.errors as errors
sys.path.pop()

sys.path.append("./fileDriver/")
import fileDriver.fileDriver as fileDriver 
sys.path.pop()

############## page generator factory ##################
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


############# static page path generator ###############
class static_path_generator:
    def __init__(self, cfg_path):
        self.__config__ = ConfigParser.RawConfigParser()
        self.__config__.read(cfg_path)
        self.staticpaths = {}
        for (pname,ppath) in self.__config__.items('static_paths'):
            print "Checking static path : [", pname ,"] path : [", ppath,"]"
            if(os.path.exists(ppath)):
                self.staticpaths[pname] = ppath
                print "YES"
            else:
                print "NO"
    def generate_path(self,name):
        try:
            return self.staticpaths[name]
        except KeyError:
            return name
    def generate_path_from_list(self,path_list):
            return "/".join(map(lambda p: self.generate_path(p),path_list))
############# ########################## ###############
        

########################################################
class method_producer:
       def __init__(self):
                self.__config__ = ConfigParser.RawConfigParser()
                self.__config__.read('./cfgs/main.cfg')
                self.__default_pg__ = self.__config__.get('mproducer', 'default_page_name')
                self.__fdriver__ = fileDriver.driver()
                self.__generator_factory__  = page_generator_factory(self.__config__.get('pgenerator_cfg','pgenerator_cfg_path'))
                self.__static_path_gen__ = static_path_generator(self.__config__.get('pstatic_cfg','pstatic_cfg_path'))
       def GET(self,path,params):
                if(path.find('.') == -1):
                        ##tmp = path.split('/')
                        generator = self.__generator_factory__.get_generator(path[1::])
                        return generator.generate(path,params)
                if(path[len(path)-1] == "/"):
                        path = path + self.__default_pg__
                tmp = path[::-1].split('/',1)
                file_name = tmp[0][::-1]
                file_path = tmp[1][::-1]
                #print file_name
                #print file_path
                if (file_path == ""):
                    file_path = "/"
                really_path = self.__static_path_gen__.generate_path("."+file_path)
                print really_path
                return self.__fdriver__.getfile(really_path + "/" + file_name)

       def produce(self,method_name):
                try:
                        return getattr(self,method_name)
                except AttributeError:
                        raise errors.ClientError(405,"Method Not Allowed")

########################################################
########################################################
