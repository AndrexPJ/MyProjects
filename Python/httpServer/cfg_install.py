import ConfigParser

config = ConfigParser.RawConfigParser()

########## File Driver ############
config.add_section('fdriver')
config.set('fdriver', 'mime_path', './cfgs/mime_types.cfg')
config.set('fdriver', 'site_dir','./')
###################################

######### Method Producer ######### 
config.add_section('mproducer')
config.set('mproducer', 'default_page_name', 'index.html')
###################################

with open('./cfgs/main.cfg', 'wb') as configfile:
    config.write(configfile)

