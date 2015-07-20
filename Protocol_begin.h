#ifndef PRO_BEGIN
#define PRO_BEGIN

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
#define ID_ERROR "ID Input Error"
#define PASS_ERROR "Password Incorrect. Connection closed."
#define COMMAND_ERROE "COMMAND ERROR"

char *func_protocol_begin(char *,char *);
#endif
