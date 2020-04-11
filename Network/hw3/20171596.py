"""
    Student ID : 20171596
    Name : 김수진
"""

# select(reading, writing, errors)

import sys
import socket
import select
import queue


def display():
    print('Student ID : 20171596')
    print('Name : Sujin Kim')


def create_server():
    # initialize the client socket descriptors
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.setblocking(False)  # make it non blocking
    port = 10000 if len(sys.argv) == 1 else int(sys.argv[1])
    server_sock.bind(('', port))
    server_sock.listen(5)

    handle_client(server_sock)


def handle_client(server_sock):
    # sockets from which we expect to read
    readers = [server_sock]
    # sockets to which we expect to write
    writers = []
    # create dictionary to be sent
    queues = {}
    # socket descriptor list
    sd_list = []

    # main loop
    while readers:
        # readable list have incoming data buffered and available to be read
        # writable list have free space in their buffer and can be written to
        # exceptional list has had an error
        readable, writable, exceptional = select.select(readers, writers, readers)

        """
        Handle readable
        """
        for sock in readable:
            # server_sock is ready to accept another connection
            if sock is server_sock:
                client_sock, addr = server_sock.accept()
                # socket descriptor
                sd = str(client_sock).split("=")[1].split(',')[0]
                sd_list.append(sd)
                # max 16 client
                if len(sd_list) <= 16:
                    print('connection from host {}, port {}, socket {}'
                          .format(addr[0], addr[1], sd))
                    client_sock.setblocking(False)  # make it non blocking
                    readers.append(client_sock)
                    queues[client_sock] = queue.Queue()  # make a queue for data we want to send
                else:
                    print('We can connect up to 16. Please connect next time')
                    sd_list.pop()
                    continue

            # if client has already sent data, receive the data.
            else:
                data = sock.recv(1024)

                if data:
                    queues[sock].put(data)
                    if sock not in writers:
                        writers.append(sock)
                    # Send the contents to the rest of the socket, except for the incoming socket
                    for reader in readers:
                        if reader != server_sock and reader != sock:
                            try:
                                reader.send(data)
                            except:
                                reader.close()
                                readers.remove(reader)

                else:
                    sd = str(sock).split("=")[1].split(',')[0]
                    print('Connection closed {}'.format(sd))
                    sd_list.remove(sd)
                    # Stop writing
                    if sock in writers:
                        writers.remove(sock)
                    # Stop reading
                    readers.remove(sock)
                    sock.close()
                    del queues[sock]

        """
        Handle writable
        """

        for sock in writable:
            try:
                # get the next chunk of data in queues
                data = queues[sock].get_nowait()
            except queue.Empty:
                writers.remove(sock)

        """
        Handle exceptional
        """

        # if there is error, close the socket
        for sock in exceptional:
            readers.remove(sock)
            if sock in writers:
                writers.remove(sock)
            sock.close()
            del queues[sock]


if __name__ == '__main__':
    display()
    create_server()
