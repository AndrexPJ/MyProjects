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

######### Page Generators #########
config.add_section('pgenerator_cfg')
config.set('pgenerator_cfg','pgenerator_cfg_path','./cfgs/pgenerator.cfg')
######### ############### #########

with open('./cfgs/main.cfg', 'wb') as configfile:
    config.write(configfile)


######### Page Generators #########
config = ConfigParser.RawConfigParser()
config.add_section('pgenerator')
config.add_section('pgenerators')
config.set('pgenerators', 'pxgenerator', './pageGen/',)

with open('./cfgs/pgenerator.cfg', 'wb') as configfile:
    config.write(configfile)
###################################
