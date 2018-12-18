#ifndef LOOP_H_INCLUDED
#define LOOP_H_INCLUDED

#include <stdio.h>

typedef struct Command_t {
  struct Command_t* next;
  char command;
} Command;

typedef struct Marker_t {
  struct Marker_t* next;
  Command* start;
} Marker;

typedef struct CommandQueue_t {
  Command* previous;
  Command* current;
  Marker* stack;
} CommandQueue;

// Define managment methods:
CommandQueue* createCommandQueue();
void delCommandQueue(CommandQueue*);
void pushLoop(CommandQueue*);
void popLoop(CommandQueue*);
void skipLoop(CommandQueue*, FILE*);
int getNextCommand(char*, CommandQueue*, FILE*);

#endif // LOOP_H_INCLUDED
