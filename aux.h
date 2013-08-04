#ifndef _AUX_H_
#define _AUX_H_

int 
arplstr 
( const char * str, char ** dst, const char * find, const char * repl);

char * freadln (FILE * restrict file);

size_t 
strftime_millis
(char * __restrict__ buf, size_t maxsize,
 const char* __restrict__ format, 
 const struct timeval* __restrict__ timeptr);

#endif

