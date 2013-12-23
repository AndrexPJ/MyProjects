import unittest
from urllib import urlopen
import json


class TestPxApi(unittest.TestCase):
    def test_px(self):
    	for feature in ["popular","upcoming","editors","fresh_today","fresh_week","fresh_yesterday"]:	
        	raw_answer = urlopen('http://pxgallery.herokuapp.com/pxapi?feature='+feature).read()
        	json_answer = json.loads(raw_answer)
        	self.assertEquals(json_answer["feature"],feature)
        	
if __name__ == '__main__':
    unittest.main()