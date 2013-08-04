#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "aux.h"


/* will replace the occurences of find in str with repl
 * the resulting string will be in *dst 
 * calling functions should take care to free the new string
 * when it is no longer needed */
int 
arplstr 
( const char * str, char ** dst, const char * find, const char * repl) 
{
  // first find the number of occurences of the string to replace 
  int nocc = 0;
  char * idx = strstr (str, find);
  while ( idx != NULL ) {
    nocc ++;
    idx = strstr ((idx + strlen(find)), find);
  }

  if ( nocc == 0 ) {
    *dst = malloc (strlen (str) + 1);
    strcpy ( *dst, str );
    return 0;
  }

  int nstrlen = 
    strlen (str) - nocc * strlen (find) + nocc * strlen (repl);
  *dst = malloc (nstrlen + 1);
//  (*dst) [ nstrlen ] = '\0';

  /* idxp to idxn is the interval between the end of the last find 
   * and the beginning of the next find */
  const char * idxp = str;
  const char * idxn = str;
  idx = *dst;
  idxn = strstr ( str, find );
  while ( idxn != NULL ) {
    idx = stpncpy ( idx , idxp, ( idxn - idxp));
    idx = stpncpy ( idx, repl, strlen (repl));
    idxp = idxn + strlen (find);
    idxn = strstr ( idxp , find);
  }
  strcpy (idx, idxp);

  return nocc;
}

size_t 
strftime_millis
(char * __restrict__ buf, size_t maxsize,
 const char* __restrict__ format, 
 const struct timeval* __restrict__ timeptr)
{
  time_t milliseconds = timeptr -> tv_usec / 1000;
  char milliseconds_string[4];
  sprintf(milliseconds_string, "%03d", milliseconds);

  char * new_format;
  arplstr(format, & new_format, "%i", milliseconds_string);

  struct tm* tmptr = localtime (& timeptr -> tv_sec);
 
  size_t retval = 
    strftime (buf, maxsize, new_format, tmptr );

  if( new_format != NULL ) free (new_format);

  return retval ;
 
}


/*
int main(int argn, char ** argv) {  
    FILE * inxfl = fopen ( "/home/junis/www/index.html", "r");
    char * ln;
    char * rpln;
    while (ln = freadln (inxfl)) {
      arplstr(ln, &rpln, "UNAME_SYSNAME", "now that's nice" );
      printf ("%s\r\n", rpln);
      free(rpln);
      free(ln);
    }
    fclose (inxfl);
}
*/


