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

#define PROMPT() {printf("\n> ");fflush(stdout);}
#define GETCMD "wget"
#define QUITCMD "quit"


int main(int argc, char *argv[]) {
//    int socktoserver = -1;
    struct hostent *hostp;
    struct sockaddr_in server;
	char buf[BUFSIZ];
    int sock;
    int bytesread;

	char fname[BUFSIZ];	

	printf("Student ID : 20171956\n");
	printf("Name : Sujin Kim\n");

	PROMPT(); 

	for (;;) {
		if (!fgets(buf, BUFSIZ - 1, stdin)) {
			if (ferror(stdin)) {
				perror("stdin");
				exit(1);
			}
			exit(0);
		}

		char *cmd = strtok(buf, " \t\n\r");

		if((cmd == NULL) || (strcmp(cmd, "") == 0)) {
			PROMPT(); 
			continue;
		} else if(strcasecmp(cmd, QUITCMD) == 0) {
				exit(0);
		}

		if(!strcasecmp(cmd, GETCMD) == 0) {
			printf("Wrong command %s\n", cmd);
			PROMPT(); 
			continue;
		}

		// connect to a server
		char *hostname = strtok(NULL, " \t\n\r");
		char *pnum = strtok(NULL, " ");
		char *filename = strtok(NULL, " \t\n\r");

		// just for Debugging, print the URL
		printf("%s:%s%s\n", hostname, pnum, filename);

		// NEED TO IMPLEMENT HERE
        
        // Creating Socket Descriptor for TCP
        if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
            perror("socket");
            exit(1);
        }
        
        


	}
} 




