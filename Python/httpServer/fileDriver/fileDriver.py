import os.path
import Errors.errors as errors
import ConfigParser


########################################################
########################################################
class mime_checker:
         __mime_types__ = {}
         __mime_ext__ = {}
         def __init__(self,mime_path):
                with open(mime_path, 'r') as f:
                        for line in f:
                                words = line.split()
                                if(len(words)):
                                        self.__mime_types__[words[1]] = True
                                        self.__mime_ext__[words[0]] = True
                        f.closed
      
         def exists(self,extension,ftype):
                try:
                        self.__mime_types__[ftype]
                        self.__mime_ext__[extension]
                        return True
                except KeyError:
                        return False

         def exists(self,extension):
                try:
                        self.__mime_ext__[extension]
                        return True
                except KeyError:
                        return False
                
########################################################
########################################################




########################################################
########################################################
class driver:
        def __init__(self):
                self.__config__ = ConfigParser.RawConfigParser()
                self.__config__.read('./cfgs/main.cfg')
                m_path = self.__config__.get('fdriver','mime_path')
                self.__site_dir__ = self.__config__.get('fdriver','site_dir')
                self.__mimes__ = mime_checker(m_path)

        def getfile(self,file_path):
                extension = file_path.split(".")[-1]
                if(not self.__mimes__.exists(extension)):
                        raise errors.ClientError(403,"Forbidden");
                else:
                        fdriver = self.getDriver(extension)
                        return fdriver(file_path)

        def getDriver(self,driver_name):        
                try:
                        return getattr(self,driver_name)

                except AttributeError:
                        return getattr(self,"default")



########################################################
        def html(self,file_path):
                return self.default(file_path)        

                
        def default(self,file_path):
                if (not self.path_checker(self.__site_dir__+"/"+file_path)):
                        raise(errors.ClientError(403,"Forbidden"))
                else:
                        try :
                                with open(self.__site_dir__+"/"+file_path, 'r') as content_file:
                                        content = content_file.read()
                                        return content
                        except IOError:
                                raise(errors.ClientError(404,"Not Found"))
########################################################

        def path_checker(self,file_path):
                if (os.path.abspath(self.__site_dir__) in os.path.abspath(file_path)):
                        return True
                else:
                        return False   
                   
########################################################
########################################################





