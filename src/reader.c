// Include all necesary dependencies:
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cbug/Debug.h>
#include "reader.h"

// Declare global variables:
char* buffer = NULL;
size_t bufferIndex = 0;

// Display the welcome prompt:
void prompt(char* version, FILE* source1, FILE* source2) {
  if(!isatty(fileno(source1)) && !isatty(fileno(source1))) {
    debug_print("No TTY detected. Skipping prompt ...")
    return;
  }

  // Display the prompt:
  debug_print("Displaying prompt ...")
  fprintf(stderr, "Welcome to brainfuck-shell, version %s!\n", version);
  fprintf(stderr, " Enter BrainFuck commands at the \"command>\" prompt, and single-character input at the \"input>\" prompt.\n");
  fprintf(stderr, " Press [CTRL+D] at any time to exit the shell.\n");
}

// Display the ending prompt:
void endPrompt(FILE* source1, FILE* source2) {
  if(!isatty(fileno(source1)) && !isatty(fileno(source1))) {
    debug_print("No TTY detected. Skipping end prompt ...")
    return;
  }

  // Display the end prompt:
  debug_print("Displaying end prompt ...")
  fprintf(stderr, "\nGoodbye! See you later ...\n");
}

// Read the next command from the stream:
int readNextCommand(FILE* source, char* out) {
  debug_print("Attempting to read command ...")
  // Handle TTYs:
  if(isatty(fileno(source))) {
    debug_print("TTY detected")

    // Read a new line if necessary:
    if (buffer == NULL || buffer[bufferIndex] == '\n') {
      debug_print("Preparing to read new line ...")
      fflush(stdout); // This prevents messages from showing up out of order
      if (buffer != NULL)
        free(buffer);
      buffer = NULL;
      bufferIndex = 0;
      fprintf(stderr, "\ncommand> ");
      if (getline(&buffer, &bufferIndex, source) == -1) {
        debug_print("Caught EOF. Returning 1 ...")
  			return 1;
  		}
      bufferIndex = -1;
    }

    // Set the output:
    *out = buffer[++bufferIndex];
    debug_print("Read complete.")
    return 0;
  }

  // Handle pipes:
  debug_print("Pipe detected")
  if (fscanf(source, "%c", out) < 0) {
    debug_print("Caught EOF. Returning 1 ...")
    return 1;
  }
  debug_print("Read complete.")
  return 0;
}

// Read the next input from the stream:
int readNextInput(FILE* source, char* out) {
  debug_print("Attempting to read input ...")
  // Handle TTY prompts:
  if(isatty(fileno(source))) {
    debug_print("TTY detected")
    char* input = NULL;
    size_t inputSize = 0;
		fprintf(stderr, "input> ");
    if (getline(&input, &inputSize, source) == -1) {
      fprintf(stderr, "\n");
      debug_error("Caught EOF. Returning 1 ...")
      return 1;
    }
    debug_print("Input size: %zu", inputSize)
    debug_print("Input: %s", input)
    *out = *input;
    free(input);
    debug_print("Read complete.");
    return 0;
  }

  // Handle pipes:
  debug_print("Pipe detected")
  if (fscanf(source, "%c", out) < 0) {
    debug_error("Caught EOF. Returning 1 ...")
    return 1;
  }
  debug_print("Read complete.")
  return 0;
}
