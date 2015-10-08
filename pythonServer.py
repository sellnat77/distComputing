from socket import *

#The ip and port to bind to 
tcpIP = '127.255.0.1'
serverPort = 4242
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind((tcpIP,serverPort))
serverSocket.listen(1)

print ('The server is ready to receive')
run = True
while run:
	connectionSocket, addr = serverSocket.accept()
	sentence = connectionSocket.recv(1024)
	#get the filename requested
	filename = sentence.split()[1]
	#this is a way to stop the server
	if "close" in filename[1:]:
		print("Server is now turned off")
		break
	try:
		f = open(filename[1:])
		outputdata = f.read()
		#Send the 200 response
		connectionSocket.send('HTTP/1.0 200 OK\r\nContent-type:text/html;charset=utf8\r\n\r\n')
		#append the files data
		connectionSocket.send(outputdata)
		connectionSocket.close()
	except:
		#If the file is not found, infor the user
		connectionSocket.send('404 NOT FOUND')
		connectionSocket.close()
		