import unittest
from urllib import urlopen
import json

from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time

requset_pattern =  'https://api.500px.com/v1/photos?feature=%s&consumer_key=%s&image_size=%s'
params = ("popular","YNGMv2DF8r2H2tFzBjAOtwPTznw0l4Ig6XBrOA1F","5")
#keys_list = ["photos","image_url"]

class TestDataCorrectness(unittest.TestCase):
    def test_data_correctness(self):

    	driver = webdriver.Firefox()
    	driver.get("http://pxgallery.herokuapp.com")
    	print "sleeping..."
    	time.sleep(5)

    	gallery_element = driver.find_element_by_id("gallery")
    	image_links = gallery_element.find_elements_by_tag_name("a")
    	
        raw_answer = urlopen(requset_pattern % params).read()
        json_answer = json.loads(raw_answer)

        true_json_links = json_answer["photos"]
        self.assertEquals(len(true_json_links),len(image_links))

        print "starting assertEquals..."
        for i in range(len(true_json_links)):
        	self.assertEquals(true_json_links[i]["image_url"], image_links[i].get_attribute("href"))

        driver.close()

        
if __name__ == '__main__':
    unittest.main()