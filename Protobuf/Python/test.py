#!/usr/bin/env python

import Messages_pb2
import Status_pb2
import socket
import time
import Response_pb2
def test():
	msg = Messages_pb2.Message()
	msg.type=1
	msg.msgBody="tester,im python"
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect(('localhost', 3000))
	#time.sleep(2)
	data = sock.recv(1024)
	rs = Response_pb2.Response()
	#print data
	#print dir(rs)
	rs.ParseFromString(data)
	print rs.data
	print rs.status
	print rs.type
	#time.sleep(2)
	sock.send(msg.SerializeToString())
	
	sock.close()


if __name__=="__main__":
    test()