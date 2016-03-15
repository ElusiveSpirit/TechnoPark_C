import socket
import os
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1', 8080))
s.listen(10)
while True:
    conn, addr = s.accept()
    path = conn.recv(512).decode('utf8').rstrip("\r\n")
    try:
        file = open('/home/konstantin/www' + str(path.split()[1]), 'r')
        data = file.read().encode('utf8')
        data = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + data
        file.close()
    except IOError:
        data = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\nerror 404"

    conn.sendall(data)
    conn.close()
