import time
import socket
import signal
import sys
import os

sys.path.append("./threadPool")
import threadPool
sys.path.pop()

sys.path.append("./httpLibs")
import httpParser 
sys.path.pop()

parser = httpParser.Parser("\r\n")


class httpServer:
	def __init__(self,host,port,thread_count):
		self.thread_count = thread_count
		self.pool = threadPool.threadPool(thread_count,10)
		self.serv_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.serv_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.serv_socket.bind((host, port))
	
	def start(self):
		self.pool.start()
		self.__listener__()
	
	def __listener__(self):
		self.serv_socket.listen(self.thread_count)
		while True:
		    (sock, addr) = self.serv_socket.accept()
		    self.pool.job(self.clientProcess,[sock],1)
	
	def clientProcess(self,sock):
        	buf = sock.recv(2048)
        	resp = parser.get_response(buf)
        	sock.sendall(resp)
        	sock.close()
	
	def stop(self):
		self.pool.stop()




host = "0.0.0.0"
port = int(os.environ.get("PORT", 5000))

server = httpServer(host,2002,5)

###################################
def ctrlc_handler(signum, frame):
    server.stop()
    exit(0)

signal.signal(signal.SIGINT, ctrlc_handler)
###################################

server.start()










