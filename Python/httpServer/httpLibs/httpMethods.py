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

    def split_path(self,path,splitter,steps):
        temp = path[::-1].split('/',steps)
        out = (map(lambda s : s[::-1],temp))[::-1]
        return out

    def generate_real_path(self,fake_path):
        count  = len(fake_path.split('/'))
        for step in range(1,count):
            tmp = self.split_path(fake_path,'/',step)
            try:
                tmp[0] = self.check_path(tmp[0]+'/')
                return '/'.join(tmp)
            except KeyError:
                pass
        return '/'.join(tmp)

    def check_path(self,path):
        return self.staticpaths[path]

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
                if (path[len(path)-1] == "/"):
                    path = path + self.__default_pg__
                ######## page generator #########
                if(path.find('.') == -1):
                        print "Loaded page generator" 
                        generator = self.__generator_factory__.get_generator(path[1::])
                        return generator.generate(path,params)
                ####### ############### #########

                #######   static page   #########
                real_path = self.__static_path_gen__.generate_real_path(path)
                print "Loaded :" + real_path
                return self.__fdriver__.getfile(real_path)
                ###### ################ #########

       def produce(self,method_name):
                try:
                        return getattr(self,method_name)
                except AttributeError:
                        raise errors.ClientError(405,"Method Not Allowed")

########################################################
########################################################
