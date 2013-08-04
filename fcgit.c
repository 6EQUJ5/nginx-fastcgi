#include <fcgi_stdio.h>
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/time.h>

#include "aux.h"

char * freadln (FILE *  file);

int main(int argn, char ** argv) {  
  struct utsname unameData;
  uname(&unameData);
  char strn[1024];
  sprintf(strn, "[%s:%s:%s:%s:%s]%s", unameData.sysname, unameData.nodename, 
                                    unameData.release, unameData.version, unameData.machine, "<br/>");
  while ( FCGI_Accept () >= 0 ) {
    printf( "Content-Type: text/html\r\n" );
    printf ("Status: 200 OK\r\n\r\n");
//    printf( "Hello world in C\r\n" );
    FILE * inxfl = fopen ( "/home/junis/www/index.html", "r");
    char * ln;
    char * rpln;
    char * rrpln;
    char strs[1024];
    struct timeval tv;
    gettimeofday(&tv, NULL );
    strftime_millis(strs, 1024, "%D %R:%S.%i", & tv);

    strcat (strs, "\r\n\r\n");
    strcat (strs, "<br/><br/>");
    strcat (strs, strn);

//      printf("[%s]\n", strs);
    while ((ln = freadln (inxfl)) != NULL) {

      arplstr(ln, &rpln, "UNAME_SYSNAME", strs);
      printf ("%s\r\n", rpln);
      free(rpln);
      free(ln);
    }
//    printf ("[%d][%d]", inxfl, ln);
    fclose (inxfl);
  }

  return 0;
}

char * freadln (FILE *  file)
{
  int default_line_length = 64;
  void * line = malloc (sizeof(char) * default_line_length);
  char character;
  unsigned short index = 0;
  while ( ( character = fgetc (file)) != '\n' &&
            character != EOF) {
    ( (char *) line)[index] = character;
    index++;
    if (index >= default_line_length - 1 )
      line = realloc( line, default_line_length *= 2 );
  }
  if (character == EOF && index == 0) {
    free ( line );
    return NULL;
  }
  ( (char *) line)[index] = '\0';
  return (char *) line;
}


