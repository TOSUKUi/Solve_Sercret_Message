#include <stdio.h>
#include <string.h>

extern void compute_sha256( char *, int, char * );

int main( void ) {
  char s[256];
  char key[65];

  while( 1 ) {
    scanf( "%s", s );
    compute_sha256( s, strlen(s), key );

    printf( "SHA256(%s): %s\n", s, key );
  }
  return 0;
}
