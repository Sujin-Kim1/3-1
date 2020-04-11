// Student ID : 20171596
// Name : 김수진

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void response(int, char[]);


int main(int argc, char *argv[]) {
    struct sockaddr_in server, remote;
    int request_sock, new_sock;
    int bytesread, f;
    int content_length = 0, send_length = 0;
    socklen_t addrlen;
    char buf[BUFSIZ], *file_buf;

    if (argc != 2) {
        (void) fprintf(stderr, "usage: %s portnum \n", argv[0]);
        exit(1);
    }

    int portnum = atoi(argv[1]);

    if ((request_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        exit(1);
    }

    printf("Student ID : 20171596\n");
    printf("Name : Sujin Kim\n");

    // Create a Server Socket
    memset((void *) &server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons((u_short) atoi(argv[1]));
    if (bind(request_sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind");
        exit(1);
    }
    if (listen(request_sock, SOMAXCONN) < 0) {
        perror("listen");
        exit(1);
    }


    while (1) {
        /* a new connection is available on the connection socket */
        addrlen = sizeof(remote);

        // Accept new connections
        new_sock = accept(request_sock,
                          (struct sockaddr *) &remote, &addrlen);
        if (new_sock < 0) {
            perror("accept");
            exit(1);
        }
        printf("Connection : Host IP %s, Port %d, socket %d\n", inet_ntoa(remote.sin_addr),
               ntohs(remote.sin_port), new_sock);
        try {
            // Read data from connected socket
            for (;;) {
                bytesread = read(new_sock, buf, sizeof(buf) - 1);
                // if receive error or no data to read, close the socket
                if (bytesread <= 0) {
                    break;
                }

                buf[bytesread] = '\0';
                printf("%s", buf);

                char *token = strtok(buf, " ");
                char *file_name;

                // 파일 이름 저장
                while (token) {
                    string str_token = token;
                    if (str_token.compare("GET")) {
                        file_name = token;
                        break;
                    }
                    token = strtok(NULL, " ");
                }

                f = open(file_name + 1);

                // 파일이 존재할 경우, 브라우저로 보낸다.
                if (f != -1) {
                    struct stat stat_buf;
                     int rc = fstat(f, &stat_buf);
                     if (rc == 0)
                         content_length =


                    // 헤더 메시지 전송
                    char header[1000] = "HTTP/1.0 200 OK\r\n"
                                        "Connection: close\r\n"
                                        "ID: 20171596\r\n"
                                        "Content-Length: ";
                    strcat(header, to_string(content_length).c_str());
                    strcat(header, "\r\nContent-Type: text/html\r\n\r\n");

                    if (write(new_sock, header, strlen(header)) != strlen(header))
                        perror("echo");

                    send_length += strlen(header);

                    // 파일 내용 전송
                    for (;;) {
                        bytesread = f.read(file_buf, content_length - 1);
                        if (bytesread <= 0)
                            break;
                        buf[bytesread] = '\0';
                        if (write(new_sock, file_buf, bytesread) != bytesread)
                            perror("echo");
                    }

                } else {
                    cout << "fail" << endl;

                }

                f.close();

            }
        }
        catch (int e) {
            break;
        }

    }
    close(new_sock);
} /* main - hw2.c */
