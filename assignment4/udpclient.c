/*//////////////////////////////////////////

Names: Somesh Khandelia & Subhranil Mondal
Roll no.: 14/CS/105 & 13/CS/111
Assignment No.4
Group no. B24

*////////////////////////////////////////////
/*
 * udpclient.c - A simple UDP client
 * usage: udpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 1024

/*
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd, portno, n;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buf[BUFSIZE];
    char result[100];

    /* check command line arguments */
    if (argc != 2) {
       fprintf(stderr,"usage: %s <hostname>\n", argv[0]);
       exit(0);
    }
    hostname = argv[1];
  //  portno = atoi(argv[2]);

    do{
      /* socket: create the socket */
      sockfd = socket(AF_INET, SOCK_DGRAM, 0);
      if (sockfd < 0)
          error("ERROR opening socket");

      /* gethostbyname: get the server's DNS entry */
      server = gethostbyname(hostname);
      if (server == NULL) {
          fprintf(stderr,"ERROR, no such host as %s\n", hostname);
          exit(0);
      }

      /* build the server's Internet address */
      bzero((char *) &serveraddr, sizeof(serveraddr));
      serveraddr.sin_family = AF_INET;
      bcopy((char *)server->h_addr,
  	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
      serveraddr.sin_port = htons(6000);

      /* get a message from the user */
      bzero(buf, BUFSIZE);
      printf("\n\nThis is UDP client\n\nEnter the text to be sent to server: ");
      gets(buf);
      serverlen = sizeof(serveraddr);
      n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&serveraddr, serverlen);
      close(sockfd);

    }while(1);

    return 0;
}
