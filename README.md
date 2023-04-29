SERVER:
 1. g++ *.cpp treecommand/*.cpp -o server [1]
 2. ./server PortAddress
 
 CLIENT:
 1. g++ *.cpp -o client
 2. ./client 127.0.0.1 PortAddress
 
 CAUTION:
 - PortAddress has to be the same in both server side and client side
 - When we have another task like keylogger, we can change command line to : 
      g++ *.cpp treecommand/*.cpp keylogger/*.cpp -o server
