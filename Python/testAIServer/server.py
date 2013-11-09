import socket
import time
host = "192.168.0.2"
port = 2001

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))
s.listen(5)

(sock, addr) = s.accept()


print sock.recv(1024)
time.sleep(3)
sock.send("ACK")

while(1):
        buf = sock.recv(1024)
        print buf
        if((buf[0] == 'E') & (buf[1] == 'O') & (buf[2] == 'G')):
                sock.close()
                s.close()
                exit()
        elif((buf[2] == 'S') & (buf[3] == 'C')):
                sock.send("ACK RET WALL 1.0 1.0 CAT 2.0 2.1 DOG 1.1 1.2 OMG 100123 123\r\n")
                #print "sended sc"
        else:
                sock.send("ACK\r\n")
                #print "sended ACK"
