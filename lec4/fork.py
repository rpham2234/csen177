# Python code to create child process  
#!/usr/bin/env python3
import os 
x = 0;
os.fork()  
x += 1; 
print("I am process with id:", os.getpid(), x )
