# Python code to create child process  
#!/usr/bin/env python3
import os 
import time  
pid1 = os.fork() 
pid2 = os.fork() 
if pid1 == 0:
	print('\t\tChild process with id: ', os.getpid())
if pid2 == 0:
	print('\tChild process with id: ', os.getpid())
print('Parent process with id: ', os.getpid())