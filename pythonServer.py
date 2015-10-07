from socket import *

tcpIP = '127.0.0.1'
serverPort = 4242
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind((tcpIP,serverPort))
serverSocket.listen(1)

print ('The server is ready to receive')
run = True
while run:
	connectionSocket, addr = serverSocket.accept()
	sentence = connectionSocket.recv(1024)
	filename = sentence.split()[1]
	try:
		f = open(filename[1:])
		outputdata = f.read()
		connectionSocket.send('HTTP/1.0 200 OK\r\nContent-type:text/html;charset=utf8\r\n\r\n')
		connectionSocket.send(outputdata)
		connectionSocket.close()
	except:
		connectionSocket.send('404 NOT FOUND')
		connectionSocket.close()
	# If the `q` key is pressed, break from the lop
	if key == ord("q"):
		# Closing application
		# Maybe provide some output when done
		# Can provide a list of datapoints that can be overlayed any image 
		# Or plotted
		break
	