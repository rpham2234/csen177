# Python code to create child process  
#!/usr/bin/env python3
import os 
import time  
pid = os.fork() 
# n greater than 0  means parent process 
if pid > 0: 
	i = 1
	while i < 100:
		print("This is the Parent code and value of i is:  ", i)
#		time.sleep(1) 
		i += 1
	print("Parent process id is : \n", os.getpid())

# n equals to 0 means child process 
else: 
	i = 1
	while i < 100:
		print("\t\t\tThis is the Child code and value of i is:  ", i) 
#		time.sleep(1)	
		i += 1
	print("Child process id is : ", os.getpid()) 
