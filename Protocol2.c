/*Protocol2.c*/
/*===============================
  IE1
  nazotoki ver2-2
  TOSUKUi
  TOSUKUi
  ===============================*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<errno.h>
#include<math.h>
#include "Sha256.h"
#include<time.h>
//#include"ProtocolA.h"
//#include"ProtocolB.h"
//#include"protocolC.h"

#define SOCK_NAME "./socket"
#define PASS_ERROR "Password Incorrect. Connection closed."
#define TIMEOUT 2
#define TRUE_SERVER_MSG "INFOEXP1-MIYOSHI-1503_2_Ver8.00"
#define KEY "mZn3Slef"
#define ProtocolB3_START "Bonjour,monsieur!"
int main(int argc, char *argv[])
{
  char buf[1024];
  char command[256];
  char *ip_address;
  char *port;
  char protocol_output_A[20];
  char protocol_key_B[10];
  
  int soc;
  int maxfd;

  fd_set readfds;
  struct sockaddr_in saddr;
  struct timeval tv;    /* タイムアウト時間 */


  tv.tv_sec = TIMEOUT;
  tv.tv_usec = 0;

  if(argc < 3){
    printf("You didnt input any information of oponent.\nusage: kadai1_Client.out IP_Address port_number\n");
    exit(1);
  }

  if ( ( soc = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
    perror( "socket" );
    exit( 1 );
  }
    
  memset( (char *)&saddr, 0, sizeof( saddr ) );
  saddr.sin_family=AF_INET;
  saddr.sin_addr.s_addr = inet_addr(argv[1]);
  saddr.sin_port = htons(atoi(argv[2]));

  /*
    struct hostent *hp;
    if((hp=gethostbyname("localhost"))==NULL){
    perror("connect");
    exit(1);
    }
      
    memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);
  */
  
    
  //strcpy( saddr.sun_path, SOCK_NAME );
    
  if ( connect( soc, ( struct sockaddr * )&saddr, ( socklen_t )sizeof( saddr ) ) < 0 ) {
    perror( "connect" ); 
    fprintf(stderr,"Port%s : any process isnt running.\n",argv[2]);
    exit( 1 );
  }
  FD_ZERO(&readfds);
  FD_SET(soc,&readfds);
  maxfd = soc;
  




 
  fprintf( stderr, "Connection established: socket %d used and Port : %s.\n", soc,argv[2]);       


  if(!func_select(soc,readfds,tv))
    return 0;
  read(soc,buf,1024);
  fprintf(stderr,"%s\n",buf);
  if(strcmp(buf,TRUE_SERVER_MSG)){
    printf("its not true server\n");
    return 0;
  }else{
    printf("This is Socket Commuication system\n");
    sprintf(command,"OPEN %s%s",KEY,"bp13007");
    strcpy(buf,command);
    write(soc,buf,strlen(buf)+1);
    fsync(soc);
    read(soc,buf,1024);
    fprintf(stderr,"%s\n",buf);
    read(soc,buf,1024);
    fprintf(stderr,"%s\n",buf);
    sscanf(buf,"Your protocol is: %s\n",protocol_output_A);
    strcpy(buf,"OK");
    write(soc,buf,strlen(buf)+1);
    fsync(soc);
    func_protocolB(readfds,soc,tv,protocol_output_A,protocol_key_B);
    func_protocolC(readfds,soc,tv,protocol_key_B);
  }
  

  
  return 0;
}

int func_select(fd_set readfds,int soc,struct timeval tv)
{
  int ret;
  ret = select(soc+1, &readfds, NULL, NULL, &tv); //受信の場合
  if(ret < 0){
    perror("select()");
    fprintf(stderr,"select error\n");
    return 0;
  }
  else if(ret==0){
    printf("its not true server Port\n");
    return 0;
  }
  return 1;
}


void func_protocolB(fd_set readfds,int soc,struct timeval tv,char *operator,char *output)
{
  char buf[1024];
  char command[256];  
 
  int x,y;
  int i;
  for (i = 0; i < 5; i++) {
    switch(operator[i] - '0'){
    case 0:
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      sprintf(command,"ANSR %x",atoi(buf));
      if(i == 0){
	sprintf(output,"%x",buf);
      }
      strcpy(buf,command);
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      strcpy(buf,"OK");
      fprintf(stderr,"%s 0",buf);
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      break;

    case 1:
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      x = atoi(buf);
      sprintf(command,"ANSR %d",2*x*x*x-3*x*x-5*x+2);
      if(i==0)
	sprintf(output,"%d",2*x*x*x-3*x*x-5*x+2);
      strcpy(buf,command);
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      strcpy(buf,"OK");
      fprintf(stderr,"%s 1",buf);
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      break;

    case 2:
      fsync(soc);
      strcpy(buf,"START PROTOCOL2");
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      x = atoi(buf);
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      y = atoi(buf);
      sprintf(command,"ANSR %d",x*y);
      if (i==0)
	sprintf(output,"%d",x*y);
      strcpy(buf,command);
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      strcpy(buf,"OK");
      fprintf(stderr,"%s 2",buf);
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      break;
      
    case 3:
      fsync(soc);
      tv.tv_sec = 5;
      strcpy(buf,"Bonjour, monsieur!");
      write(soc,buf,strlen(buf)+1);
      sleep(2);
      strcpy(buf,"START PROTOCOL3");
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      x = atoi(buf);
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      y = atoi(buf);
      sprintf(buf,"ANSR %d",min(abs(x),abs(y)));
      if(i==0)
	sprintf(output,"%d",min(abs(x),abs(y)));
      write(soc,buf,strlen(buf)+1);
      fsync(soc);
      read(soc,buf,1024);
      strcpy(buf,"OK");
      fprintf(stderr,"%s 3",buf);
      write(soc,buf,strlen(buf)+1);
      break;
      
    }
      
  } 
  
}

void func_protocolC(fd_set readfds,int soc,struct timeval tv,char *key){
  char buf[1024];
  sprintf(buf,"GETMSG %s%s","bp13007",key);
  write(soc,buf,strlen(buf)+1);
  fsync(soc);
  read(soc,buf,1024);
  fprintf(stderr,"%s",buf);
}

int min(int x,int y){
  if(x < y)
    return x;
  else return y;
}

      
      


    
