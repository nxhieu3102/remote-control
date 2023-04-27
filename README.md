How to run project:

--> Run server first
>> g++ -pthread SERVER/*.cpp -o server; ./server 8080

--> Next, run client
>> g++ -pthread CLIENT/*.cpp -o client -lncurses; ./client <"your local ip"> 8080

1. client sends request to server
2. server does the request and gets data 
3. server sends data to client


Client will ask to process in server's system:
-Client send the message in type:

    + 1 : List running processes
    + 2 : List installed programs
    + 3 : Capture the screen
    + 4 : Keylog
    + 5 : Browse the directory tree

-Server returns the message:

    + 1 : Vector of string that saves the information of running processes
    + 2 : Vector of string that saves the information of installed programs
    + 3 : Image (file .png, .JPEG, ...)
    + 4 : Every characters on the keyboard from 'start command' to 'end command'
    + 5 : Vector of string that saves the tree path

