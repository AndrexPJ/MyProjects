import ConfigParser

config = ConfigParser.RawConfigParser()

########## File Driver ############
config.add_section('fdriver')
config.set('fdriver', 'mime_path', './cfgs/mime_types.cfg')
config.set('fdriver', 'site_dir','./sites')
###################################

######### Method Producer ######### 
config.add_section('mproducer')
config.set('mproducer', 'default_page_name', 'index.html')
###################################

######### Page Generators #########
config.add_section('pgenerator_cfg')
config.set('pgenerator_cfg','pgenerator_cfg_path','./cfgs/pgenerator.cfg')
######### ############### #########

######### Static   Pages  #########
config.add_section('pstatic_cfg')
config.set('pstatic_cfg','pstatic_cfg_path','./cfgs/pstatic.cfg')
###################################

with open('./cfgs/main.cfg', 'wb') as configfile:
    config.write(configfile)




######### Page Generators #########
config = ConfigParser.RawConfigParser()
config.add_section('pgenerator')
config.add_section('pgenerators')
config.set('pgenerators', 'pxgenerator', './generators/pxgen/',)

with open('./cfgs/pgenerator.cfg', 'wb') as configfile:
    config.write(configfile)
###################################


######### Static   Pages  #########
config = ConfigParser.RawConfigParser()
config.add_section('static_paths')
config.set('static_paths','./','./sites/moais-webapps/')

with open('./cfgs/pstatic.cfg', 'wb') as configfile:
    config.write(configfile)
###################################