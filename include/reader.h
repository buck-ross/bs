#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include <stdio.h>

// Declare the methods that read the character input stream:
void prompt(char*, FILE*, FILE*);
void endPrompt(FILE*, FILE*);
int readNextCommand(FILE*, char*);
int readNextInput(FILE*, char*);

#endif // READER_H_INCLUDED
