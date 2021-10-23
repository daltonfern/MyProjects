import select
import socket
import argparse
import sys
import threading
import signal

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)    #User socket which connects to server using TCP (SOCK_STREAM)
guser = ''    #Global var for username to address user in signal handler
BUFFER_SIZE = 2048

def main():

    signal.signal(signal.SIGINT, signal_handler)
    
    parser = argparse.ArgumentParser()
    parser.add_argument("user", help="Username of the user")    
    parser.add_argument("address", help="Address for connection to chat server")
    args = parser.parse_args()    #Initialize arguments
    user = args.user
    guser = ''.join(user)
    address = args.address
    host = ''
    port = ''
    adrChar = ''
    portChar = ''
    i = 7    #Index after "chat://"
    j = 0
    
    while address[i] != ':':     #Loop until port begins
        adrChar = address[i]
        host = ''.join((host,adrChar))    #Assign charecters from address from argument to host variable
        i += 1
        j += 1
    m = i + 1
    while m < (len(address)):    #Loop until port ends
        portChar = address[m]
        port = ''.join((port,portChar))   #Assign charecters from port from argument to port variable
        m += 1
    portNum = int(port)
    print('Connecting to server ...')
    server.connect((host, portNum))    #Connect client to server
    print('Connection to server established. Sending intro message...')
    server.send((user).encode())    #Send username to complete attempt to registration to server
    print('Registration successful. Ready for messaging!')

def signal_handler(sig, frame):    #Catch when user attempts to exit client
    server.send(('DISCONNECT' + guser + "CHAT/1.0").encode())   #Notify server which user is disconnect
    print("Disconnected from server ... exiting!")
    
def rec():
    while True:    #Always be open to receving messages
        try:
            message = server.recv(BUFFER_SIZE).decode()    #Decode messages recieved from server
            if message == 'DISCONNECT CHAT/1.0':    #Check for server disconnection message
                print('Server disconnected, shutting down client')
                sys.exit(0)
            if message == '401 CLIENT ALREADY REGISTERED':    #Check for registration error message
                print('Error registering, shutting down client')
                sys.exit(0)
            if message[0] == '@':    #Print any message recieved aside from control messages
                print(message)
        except:
            continue
            
def send():
    while True:    #Always be allowed to send messages to the server
        message = sys.stdin.readline()    #Read user input and initalize as message
        server.send((message).encode())   #Send message to server

recieve_thread = threading.Thread(target=rec)    #Allow for receiving multiple messages at the same time
recieve_thread.start()
write_thread = threading.Thread(target=send)    #Allow for sending multiple messages at the same time
write_thread.start()
        
if __name__ == '__main__':
    main()
        
        
    
