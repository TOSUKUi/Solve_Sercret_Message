/*=============================
  情報実験1
  課題1-クライアント.ver2
  BP13007
  雨宮俊貴
  ©2015 雨宮俊貴
  ===============================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<errno.h>

#define SOCK_NAME "./socket"

int main(int argc, char *argv[])
{
  fd_set readfds;
  struct sockaddr_in saddr;
  int soc;
  char buf[1024];
  char temp[256];
  int i=0;
  int maxfd;
  int ret;
  struct timeval tv;    /* タイムアウト時間 */
      /* 戻り値保持用 */

  tv.tv_sec = 3;
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
  fprintf(stderr,"a");
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
  fprintf(stderr,"b");    
  read(soc,buf,1024);      
  fprintf(stderr,"c");
  fprintf(stderr,"%s\n",buf);
  sprintf(buf,"UID %s","bp13007");
  write(soc,buf,strlen(buf));
  fsync(soc);
  read(soc,buf,1024);  
  printf("read = %s\n",buf);
  if(!strncmp(buf,"Your key",8)){          
    fsync(soc);
    read(soc,buf,1024);
    printf("%s\n",buf);
    printf("input key is Encrypted with SHA256:");
    scanf("%s",temp);
    sprintf(buf,"PWD %s",temp);
    printf("buf = %s\n",buf);
    write(soc,buf,strlen(buf));
    fsync(soc);
    read(soc,buf,1024);
    scanf("%s",temp);
    printf("input key:");
    sprintf(buf,"INF %s",temp);
    printf("buf = %s\n",buf);
    write(soc,buf,strlen(buf));
    fsync(soc);
    read(soc,buf,1024);
    printf("%s\n",buf);
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
