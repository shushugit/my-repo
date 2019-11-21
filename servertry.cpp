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

  int svr_fd;                   //server描述檔, socket()回傳,直接看成server 
  struct sockaddr_in svr_addr;  //server地址, bind()會用到,將server地址跟socket綁定 
  								//struct sockaddr_in是一個型態 

  int cli_fd;                   //incomming client描述檔, accept()回傳 ,直接看成client,所以是accept client的連線 
  struct sockaddr_in cli_addr;  //client地址, accept()會用到 
  socklen_t addr_len;           //client的地址長度, accept()會用到 

  time_t ticks;                 // 現在時間 
  int write_bytes;              // number of byte訊息資料數量, write()回傳 
  char buf[MAX_SIZE];           // buffer to 儲存訊息 

   
  /* 1) Create the socket, use `socket()`
        AF_INET: IPv4
        SOCK_STREAM: Stream Socket (TCP)
  */
  svr_fd = socket(AF_INET, SOCK_STREAM, 0);//svr_fd就是server 
  if (svr_fd < 0) {//svr_fd=-1代表製作socket失敗 
    perror("Create socket failed.");
    exit(1);
  }

  /* 2) Bind綁定 the socket to port, with prepared (struct sockaddr_in)這個型態的 svr_addr,就是server地址*/
  bzero(&svr_addr, sizeof(svr_addr));//serer地址 
  svr_addr.sin_family = AF_INET;//ipv4 
  svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);//ip地址(本機端字節序轉成網路端字節序) 
  svr_addr.sin_port = htons(PORT);//港口號碼 

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
  printf("Listening on %s:%d\n", inet_ntoa(svr_addr.sin_addr), PORT);//在server自己地址的8888port聽 
  printf("Waiting for client...\n\n");

  addr_len = sizeof(struct sockaddr_in);//定義addr_len=地址長度 

  while(1) {//如果有偵測到client 
    /* 4) Accept client connections */
    cli_fd = accept(svr_fd, (struct sockaddr*)&cli_addr, (socklen_t*)&addr_len);
	//server接受,client位址,client位址長度 
    if (cli_fd < 0) {
      perror("Accept failed");
      exit(1);
    }

    printf("Connection accepted\n");
    printf("Client is from %s:%d\n\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    //client地址,client port號碼 

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

      err = send(client_fd, buf, read, 0);
      if (err < 0) perror("Client write failed\n");
    }
    

    close(cli_fd);
  }

  close(svr_fd);
  return 0;
}
