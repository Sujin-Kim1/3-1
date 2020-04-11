from socket import *
import sys
import os


class MyServer:
    def __init__(self, port):
        self.port = port

    def create_server(self):
        """
        Create server and bind socket address
        """
        try:
            server_socket = socket(AF_INET, SOCK_STREAM) # create socket
            server_socket.bind(('', self.port)) # bind socket and address
            server_socket.listen(1) # server begins listening for incoming TCP requests
            self.handle_client(server_socket)
            server_socket.close()

        except Exception as e:
            print(e)

    def get_HTTP_Response_message(self, response_code, content_length, content_type):
        """
        Generate HTTP Response message
        :param response_code: If file is valid, response_code is 200. Else, response_code is 404
        :param content_length: Length of file
        :param content_type: Type of file (Ex.text/html)
        :return: HTTP Response message
        """
        response_message = ''
        if response_code == 200:
            response_message += 'HTTP/1.0 200 OK\r\n'
        elif response_code == 404:
            response_message += 'HTTP/1.0 404 NOT FOUND\r\n'

        response_message += 'Connection: close\r\n'
        response_message += 'ID: 20171596\r\n'
        response_message += 'Name: Sujin Kim\r\n'
        response_message += 'Content-Length: {length}\r\n'.format(length=content_length)
        response_message += 'Content-Type: {type}\r\n\r\n'.format(type=content_type)
        return response_message.encode()

    def handle_client(self, server_socket):
        """
        Handle client socket and serve file
        :param server_socket: server socket created in create_server function
        """
        while True:
            # server waits on accept() for incoming requests,
            # new socket created on return
            client_socket, addr = server_socket.accept()

            print('Connection : Host IP {ip}, Port {port}, socket {sock}'
                  .format(ip=addr[1], port=addr[1], sock=str(client_socket).split(" ")[1][-2]))

            request_message = client_socket.recv(1024).decode()
            print(request_message[:request_message.index('\r\n\r\n')] + '\r\n') # print HTTP Request message

            file_name = request_message.split(' ')[1][1:]
            path = os.getcwd() # get current path
            file_path = path + '/' + file_name
            content_length = 0
            content_type = 'text/html'
            is_file = os.path.isfile(file_name)

            if is_file:
                # get http response message
                content_length = os.path.getsize(file_path)
                header = self.get_HTTP_Response_message(200, content_length, content_type)
                # send response message + file data
                f = open(file_name, 'rb')
                body = f.read()
                response_message = header + body
                client_socket.send(response_message)
                send_length = len(response_message)
                print('finish {send_length} {file_length}'.format(send_length=send_length, file_length=content_length))

            else:
                print('Server Error : No such file ./{}!'.format(file_name))
                response_message = self.get_HTTP_Response_message(404, content_length, content_type)
                client_socket.send(response_message)


if __name__ == '__main__':
    print('Student ID : 20171596')
    print('Name : Sujin Kim')
    PORT = int(sys.argv[1])
    server = MyServer(PORT)
    server.create_server()
