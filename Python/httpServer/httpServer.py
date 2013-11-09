import time
import socket
import signal
import sys

sys.path.append("./threadPool")
import threadPool

sys.path.append("./httpLibs")
import httpParser 

parser = httpParser.Parser("\r\n")





def clientProcess(sock):
                buf = sock.recv(1024)
                resp = parser.get_response(buf)
                #print resp
                sock.sendall(resp)
                sock.close()


host = "192.168.0.2"
port = 2001

pool = threadPool.threadPool(5,10);


###################################
def ctrlc_handler(signum, frame):
    pool.stop()
    exit(0)

signal.signal(signal.SIGINT, ctrlc_handler)
####################################


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))
pool.start()
s.listen(5)
while True:
        (sock, addr) = s.accept()
        pool.job(clientProcess,[sock],1)
#pool.stop()






