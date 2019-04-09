#include <HEADERS.h>

// This two functions below belong to standard I/O procedures.
// (see IO_Procedures_Standard.h for function prototypes)
// They provide general procedures to filtering out missing values,
// when they are initially marked with a given flag.

#if defined R_SHLIB

void IO_ERROR( int n_0, int n_1, char * Exit_Message)
{
  error(n_0, n_1, Exit_Message);
}
#else

void IO_ERROR( int n_0, int n_1, char * Exit_Message)
{
  printf("---> Immediate Exit: %s\n", Exit_Message);
  exit(1);
}
#endif
