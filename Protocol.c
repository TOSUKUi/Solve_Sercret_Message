/*=============================
  IE1
  nazotoki.ver2
  
  TOSUKUi
  2015 TOSUKUi
  ===============================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<errno.h>
#include "Sha256.h"

#define SOCK_NAME "./socket"
#define PASS_ERROR "Password Incorrect. Connection closed."


int main(int argc, char *argv[])
{
  fd_set readfds;
  struct sockaddr_in saddr;
  
  char buf[1024];
  char temp[256];
  char key[65];
  char command[256];
  int i=0;
  int soc;
  int maxfd;
  int ret;
  struct timeval tv;    /* タイムアウト時間 */
  /* 戻り値保持用 */

  tv.tv_sec = 1;
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

  read(soc,buf,1024);      

  fprintf(stderr,"%s\n",buf);
  sprintf(buf,"UID %s\n","bp13007");

  write(soc,buf,strlen(buf) + 1);
  fsync(soc);
  read(soc,buf,1024);  
  printf("read = %s\n",buf);
      
  if(!strncmp(buf,"Your key",8)){          
    {
      sscanf(buf,"Your key: %s\n",temp);

      compute_sha256(temp,strlen(temp),key);
    }
    fsync(soc);
    read(soc,buf,1024);
    printf("%s\n",buf);    
    sprintf(buf,"PWD %s",key);

    write(soc,buf,strlen(buf) + 1);
    ret = select(soc+1, &readfds, NULL, NULL, &tv); //受信の場合
    if(ret < 0){
    perror("select()");
    fprintf(stderr,"select error\n");
    return 0;
    }
    else if(ret==0){

      sprintf(command,"INF %s",temp);

      strcpy(buf,command);
      write(soc,buf,strlen(buf) + 1);
      fsync(soc);
      read(soc,buf,1024);
      fprintf(stderr,"%s\n",buf);
      return 0;
    }
    
    read(soc,buf,1024);
    fprintf(stderr,"%s\n",buf);
    if(!strcmp(buf,PASS_ERROR)){
      close(soc);
      return 0;
    }
    fprintf(stderr,"input key:");
    scanf("%s",temp);    
    sprintf(buf,"INF %s",temp);
    printf("buf = %s\n",buf);
    write(soc,buf,strlen(buf) + 1);
    fsync(soc);
    read(soc,buf,1024);
    printf("%s\n",buf);
  }else if(!strncmp(buf,"Unregistered",12)){
    printf("miss id\n");
    close(soc);
    return 0;
  }else{
    printf("its not true server\n");
    close(soc);
    return 0;
  }


  /*
    while( fgets( buf, 1024, stdin ) ) {
    if ( buf[strlen(buf)-1] == '\n' ) buf[strlen(buf)-1] = '\0';
    write( soc, buf, strlen(buf)+1 );
    fsync( soc );
    read( soc, buf, strlen(buf)+1 );
    fprintf( stdout, "%s\n", buf );
    }
  */
  close( soc );

  return 0;
}
