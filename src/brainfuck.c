// Include all necessary dependencies:
#include <stdio.h>
#include <stdlib.h>
#include <cbug/Debug.h>
#include "config.h"
#include "reader.h"
#include "node.h"
#include "loop.h"


// Define the main method:
int main(int argc, char** argv) {
  debug_print("Creating the head ...")
  Node* head = newNode();

  // Define the files:
  FILE* proceedure = stdin;
  FILE* input = stdin;
  FILE* output = stdout;

  // If applicable, open the files specified by argv:
  if (argc > 1) {
    debug_print("Program file detected. Opening ...")
    proceedure = fopen(argv[1], "r");
  }
  if (argc > 2) {
    debug_print("Input file detected. Opening ...")
    input = fopen(argv[2], "r");
  }
  if (argc > 3) {
    debug_print("Output file detected. Opening ...")
    output = fopen(argv[3], "w");
  }

  // Prompt the user:
  prompt(VERSION, proceedure, input);

  // Initialize state variables:
  char c;
  CommandQueue* queue = createCommandQueue();

  // Run the command loop:
  while(getNextCommand(&c, queue, proceedure) == 0) {
    debug_print("Detected Command '%c'", c)
    debug_print("Queue State: %p, %p, %p", queue->previous, queue->current, queue->stack)

    // Run the proceedure corresponding to the command:
    switch(c) {
      // Move Left
      case '<':
        head = moveLeft(head);
        break;
      // Move Right:
      case '>':
        head = moveRight(head);
        break;
      // Increment:
      case '+':
        incrementNode(head);
        break;
      // Decrement:
      case '-':
        decrementNode(head);
        break;
      // Push loop:
      case '[':
        if (head->value == 0)
          skipLoop(queue, input);
        else
          pushLoop(queue);
        break;
      // Pop loop:
      case ']':
        popLoop(queue);
        break;
      // Write to buffer:
      case '.':
        printNode(output, head);
        break;
      // Read from buffer:
      case ',':
        if (readNode(input, head) != 0) {
          debug_error("EOF Caught in input stream. Program crashing ...")
          endPrompt(proceedure, input);
          return 1;
        }
        break;
      // Treat all other commands as comments:
      default:
        // Do nothing.
        debug_print("Command not recognized. Ignoring ...")
        break;
    }
  }

  // Cleanup:
  debug_print("Cleaning up ...")
  if (argc > 1) {
    debug_print("Closing program file ...")
    fclose(proceedure);
  }
  if (argc > 2) {
    debug_print("Closing input file ...")
    fclose(input);
  }
  if (argc > 3) {
    debug_print("Closing output file ...")
    fclose(output);
  }
  delNodeTree(head);
  delCommandQueue(queue);
  free(queue);

  // Say goodbye:
  endPrompt(proceedure, input);

  return 0;
}
