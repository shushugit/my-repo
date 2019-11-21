/*
 * Simple Time Server For 2016 Introduction to Computer Network
 * Author: vicky-sunshine @ HSNL-TAs
 * 2016/09
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>     /* provide functions about string, ex: `bzero()`, `strlen()`*/
#include <sys/types.h>  /* contains a number of basic derived types */
#include <sys/socket.h> /* provide functions and data structures of socket */
#include <arpa/inet.h>  /* convert internet address and dotted-decimal notation */
#include <netinet/in.h> /* provide constants and structures needed for internet domain addresses*/
#include <unistd.h>     /* `read()` and `write()` functions */
#include <time.h>       /* provide functions about time */

#define PORT 8888
#define MAX_SIZE 2048
#define MAX_CONNECTION 5


int main() {

  int svr_fd;                   //server�y�z��, socket()�^��,�����ݦ�server 
  struct sockaddr_in svr_addr;  //server�a�}, bind()�|�Ψ�,�Nserver�a�}��socket�j�w 
  								//struct sockaddr_in�O�@�ӫ��A 

  int cli_fd;                   //incomming client�y�z��, accept()�^�� ,�����ݦ�client,�ҥH�Oaccept client���s�u 
  struct sockaddr_in cli_addr;  //client�a�}, accept()�|�Ψ� 
  socklen_t addr_len;           //client���a�}����, accept()�|�Ψ� 

  time_t ticks;                 // �{�b�ɶ� 
  int write_bytes;              // number of byte�T����Ƽƶq, write()�^�� 
  char buf[MAX_SIZE];           // buffer to �x�s�T�� 

   
  /* 1) Create the socket, use `socket()`
        AF_INET: IPv4
        SOCK_STREAM: Stream Socket (TCP)
  */
  svr_fd = socket(AF_INET, SOCK_STREAM, 0);//svr_fd�N�Oserver 
  if (svr_fd < 0) {//svr_fd=-1�N��s�@socket���� 
    perror("Create socket failed.");
    exit(1);
  }

  /* 2) Bind�j�w the socket to port, with prepared (struct sockaddr_in)�o�ӫ��A�� svr_addr,�N�Oserver�a�}*/
  bzero(&svr_addr, sizeof(svr_addr));//serer�a�} 
  svr_addr.sin_family = AF_INET;//ipv4 
  svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);//ip�a�}(�����ݦr�`���ন�����ݦr�`��) 
  svr_addr.sin_port = htons(PORT);//��f���X 

  if (bind(svr_fd, (struct sockaddr*)&svr_addr , sizeof(svr_addr)) < 0) {
    perror("Bind socket failed.");
    exit(1);
  }

  /* 3) Listen on socket */
  if (listen(svr_fd, MAX_CONNECTION) < 0) {
    perror("Listen socket failed.");
    exit(1);
  }

  printf("Server started\n");
  printf("Maximum connections set to %d\n", MAX_CONNECTION);
  printf("Listening on %s:%d\n", inet_ntoa(svr_addr.sin_addr), PORT);//�bserver�ۤv�a�}��8888portť 
  printf("Waiting for client...\n\n");

  addr_len = sizeof(struct sockaddr_in);//�w�qaddr_len=�a�}���� 

  while(1) {//�p�G��������client 
    /* 4) Accept client connections */
    cli_fd = accept(svr_fd, (struct sockaddr*)&cli_addr, (socklen_t*)&addr_len);
	//server����,client��},client��}���� 
    if (cli_fd < 0) {
      perror("Accept failed");
      exit(1);
    }

    printf("Connection accepted\n");
    printf("Client is from %s:%d\n\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    //client�a�},client port���X 

    /* Handle message, write current time to client */
    ticks = time(NULL);
    snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));

    write_bytes = write(cli_fd, buf, strlen(buf));
    if(write_bytes < 0) {
      perror("Write Failed");
      exit(1);
    }
    
    
	  while (1) {
      int read = recv(cli_fd, buf, sizeof(buf), 0);

      if (!read) break; // done reading
      if (read < 0) perror("Client read failed\n");

      read = send(cli_fd, buf, read, 0);
      if (read < 0) perror("Client write failed\n");
      
      
	  
	  printf("Client message : %s",buf);
	  printf("\n\n");
    }
    

    close(cli_fd);
  }

  close(svr_fd);
  return 0;
}
