import socket
import select
import signal
import sys
import threading

BUFFER_SIZE = 2048
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)    #Create server socket which clients will connect to
server_socket.bind(('', 0))    #Give server socket a random IP address and port which is available
server_socket.listen(100)    #Allow for upto 100 users, CAN BE CHANGED
clients = []    #List of all connected addresses
users = []      #List of all connected users

def signal_handler(sig, frame):
    print('Interrupt received, shutting down ...')
    sendToOthers('DISCONNECT CHAT/1.0', None)    #When the server shuts down notify all connected users
    sys.exit(0)

def rec(client):
    while True:    #Always be allowed to recieve messages
        try:
            message = client.recv(BUFFER_SIZE).decode()    #Decode and initalize message variable w/recieved message
            for user in users:
                if message == ("DISCONNECTCHAT/1.0"):    #Check for disconnection control message
                    disconnect(client)
            print('Received message from user ' + users[clients.index(client)] + ': ' + '@' + users[clients.index(client)] + ': ' + message)    #Server display of message which was recieved
            message = ('@' + users[clients.index(client)] + ': ' + message)    #Reformat message to be sent and displayed on other clients
            sendToOthers(message, client)
        except:
            continue

def disconnect(client):
    user = users[clients.index(client)]    #Find user who is disconnecting
    print('Disconnecting user ' + user)
    clients.remove(client)
    users.remove(user)
    client.close()    #Close the user's connection to the server

def sendToOthers(message, client):
    for cli in clients:
        if client != cli:    #If reciever address is different from sender address
            cli.send((message).encode())

def sendToOne(message, client):
    client.send((message).encode())
    
def main():

    signal.signal(signal.SIGINT, signal_handler)
    
    print('Will waiting for client connections at port: ' + str(server_socket.getsockname()[1]))    #Report random port server is functioning on
    print('Waiting for incoming client connections ...')

    while True:    #Always allow for new connections
        conn, addr = server_socket.accept()    #Record socket and address of sender
        clients.append(conn)
        print('Accepted connection from client address: ' + str(addr))
        user = conn.recv(2048).decode()    #Decode sender's username message
        if user in users:    #If the username provided by the client is already a registered username
            print("401 CLIENT ALREADY REGISTERED")
            sendToOne('FAILED REGISTRATION CHAT/1.0', conn)    #Send to client attempting to connect, their connection has failed
        users.append(user)
        sendToOne("200 REGISTRATION SUCCESSFUL", conn)    #Notify client w/control message when they have successfully connected
        print('Connection to client established, waiting to receive messages from user: ' + user)

        thread = threading.Thread(target=rec, args=(conn,))    #Allow for simultaneous sending and recieving of messages
        thread.start()
        
if __name__ == '__main__':
    main()
    
