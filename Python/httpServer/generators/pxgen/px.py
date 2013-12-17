from jinja2 import Environment


class generator:
        def __init__(self):
                def_page_path = "./generators/pxgen/default.html"
                with open(def_page_path, 'r') as content_file:
                        self.content = content_file.read()
                self.env = Environment()

        def generate(self,page_name,query_params):
                return self.env.from_string(self.content).render()
                



 





