#include <stdlib.h>
#include <cbug/Debug.h>
#include "reader.h"
#include "loop.h"


// Create a new Command Queue object to track loops:
CommandQueue* createCommandQueue() {
	debug_print("Creating a new Command Queue ...")
	CommandQueue* out= (CommandQueue*)malloc(sizeof(CommandQueue));
	out->previous = NULL;
	out->current = NULL;
	out->stack = NULL;
	return out;
}

// Delete the CommandQueue object:
void delCommandQueue(CommandQueue* target) {
	// Free all markers, keeping track of the starting pointer of the last one:
	debug_print("Freeing all Marker objects ...")
	Command* pos = (target->previous != NULL) ? target->previous : target->current;
	Marker* tmp;
	while(target->stack != NULL) {
		pos = target->stack->start;
		tmp = target->stack;
		target->stack = target->stack->next;
		free(tmp);
	}

	// Free the Commands list:
	debug_print("Freeing all Command objects ...")
	target->current = pos;
	while(target->current != NULL) {
		pos = target->current;
		target->current = target->current->next;
		free(pos);
	}

	// Nullify all fields:
	target->previous = NULL;
	target->current = NULL;
	target->stack = NULL;
}

// Push the current command pointer to the loop stack:
void pushLoop(CommandQueue* queue) {
	debug_print("Pushing loop statement ...")
	// Handle the NULL case:
	if (queue->previous == NULL) {
		debug_print("Detected NULL queue. Pushing first loop ...")
		Command* cmd = (Command*)malloc(sizeof(Command));
		cmd->command = '[';
		queue->previous = cmd;
	}

	// Push "pos" to the stack:
	debug_print("Pushing loop pointer ...")
	Marker* tmp = (Marker*)malloc(sizeof(Marker));
	tmp->start = queue->previous;
	tmp->next = queue->stack;
	queue->stack = tmp;
}

// Popo the last loop statement off the stack for reevaluation:
void popLoop(CommandQueue* queue) {
	debug_print("Popping loop statement ...")
	// Handle the NULL case:
	if (queue->stack == NULL) {
		debug_warn("No loop detected. Ignoring end-loop command ...");
		return;
	}

	// Pop the loop statement & set the read state:
	debug_print("Poping the last loop statement off the stack ...")
	queue->current = queue->stack->start;
	Marker* tmp = queue->stack;
	queue->stack = tmp->next;
	free(tmp);
}

void skipLoop(CommandQueue* queue, FILE* source) {
	debug_print("Skipping loop statement ...")
	if (queue->current == NULL) {
		// Handle skipping while loop is still in write mode:
		debug_print("Write mode detected.")
		unsigned int count = 1;
		char out;
		while (count > 0) {
			debug_print("Count = %d", count)
			// Read a character:
			if (readNextCommand(source, &out) < 0) {
				debug_print("Caught EOF. Returning ...")
				return;
			}

			// Detect loop statements:
			if (out == '[')
				count++;
			else if (out == ']')
				count--;

			// Buffer data:
			if (queue->previous != NULL) {
				debug_print("Buffering to queue ...")
				Command* tmp = (Command*)malloc(sizeof(Command));
				tmp->command = out;
				queue->previous->next = tmp;
				queue->previous = queue->previous->next;
			}
		}
	} else if (queue->stack != NULL) {
		// Handle skipping while node is in read mode:
		debug_print("Nested read mode detected.")
		unsigned int count = 0;
		queue->current = queue->previous;
		do {
			if (queue->current->command == '[')
				count++;
			else if (queue->current->command == ']')
				count--;
			queue->previous = queue->current;
			queue->current = queue->current->next;
		} while (count != 0);
	} else {
		// Handle skipping while outer loop is in read mode:
		debug_print("Outer read mode detected.")
		delCommandQueue(queue);
	}
}

// Retreive the next command from the queue or read it from the input file:
int getNextCommand(char* out, CommandQueue* queue, FILE* source) {
	debug_print("Getting next command ...")
	if (queue->current != NULL) {
		// Recalling from previous run:
		debug_print("Initialized loop detected. Recalling command ...")
		*out = queue->current->command;
		queue->previous = queue->current;
		queue->current = queue->current->next;
	} else if (queue->previous != NULL) {
		// Recording for the first time:
		debug_print("Uninitialized loop detected. Recording command ...")
		if (readNextCommand(source, out) < 0) {
			debug_print("Caught EOF. Returning 1 ...")
			return 1;
		}
		Command* tmp = (Command*)malloc(sizeof(Command));
		tmp->command = *out;
		queue->previous->next = tmp;
		queue->previous = queue->previous->next;
	} else {
		// Handle the NULL case
		debug_print("No loop detected. Reading command ...")
		if (readNextCommand(source, out) != 0) {
			debug_print("Caught EOF. Returning 1 ...")
			return 1;
		}
	}
	return 0;
}

