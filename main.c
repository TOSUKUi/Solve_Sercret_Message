/*main.c*/
/*===============================
  IE1
  謎解き.main ver1
  TOSUKUi
  ©201 TOSUKUi
  ===============================*/

#include<stdio.h>
#include "Protocol_begin.h"



int main(int argc, char *argv[])
{
  char *ip_address;
  char *port;
  char *protocol_output_begin;
  char *protocol_output_A;
  char *protocol_output_B;
  char *protocol_output_C;

  protocol_output_begin = func_protocol_begin(argv[1],argv[2]);
  if(protocol_output_begin != NULL)
    func_protocol_A(,);
 



  printf("This is Socket Commuication system\n");
  
  
  return 0;
}

