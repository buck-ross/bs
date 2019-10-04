// Include all necesary dependencies:
#include <stdlib.h>
#include <cbug/Debug.h>
#include "reader.h"
#include "node.h"

// Allocate a new node on the heap:
Node* newNode() {
	debug_print("Creating a new Node ...")
	Node* out = (Node*)malloc(sizeof(Node));
	out->left = NULL;
	out->right = NULL;
	out->value = 0;
	return out;
}

// When given a Node, free all connected Nodes, including the provided Node:
void delNodeTree(Node* head) {
	// Handle the NULL case:
	if (head == NULL) {
		debug_print("NULL Case detected. Nothing deleted ...")
		return;
	}

	// Delete the left side:
	debug_print("Deleting left side ...")
	Node* index = head->left;
	Node* tmp;
	while (index != NULL) {
		tmp = index;
		index = index->left;
		free(tmp);
	}

	// Delete the head & right side:
	debug_print("Deleting right side ...")
	index = head;
	while(index != NULL) {
		tmp = index;
		index = index->right;
		free(tmp);
	}

	debug_print("Delete complete.")
}

// Retrieve the Node to the left of the current Node. If no such Node exists, create one:
Node* moveLeft(Node* current) {
	debug_print("Shifting left ...")
	if (current->left == NULL) {
		current->left = newNode();
		current->left->right = current;
	}
	return current->left;
}

// Retrieve the Node to the right of the current Node. If no such Node exists, create one:
Node* moveRight(Node* current) {
	debug_print("Shifting right ...")
	if (current->right == NULL) {
		current->right = newNode();
		current->right->left = current;
	}
	return current->right;
}

// Print the character value of the current Node to the screen:
void printNode(FILE* dest, const Node* current) {
	debug_print("Printing node ...")
	fprintf(dest, "%c", current->value);
}

// Read a single from stdin and store it in the current Node:
int readNode(FILE* src, Node* current) {
	debug_print("Reading into node ...")
	if (readNextInput(src, &(current->value))) {
		debug_print("Caught EOF. Returning 1 ...")
		return 1;
	}
	debug_print("Read value '%c' into node.", current->value)
	return 0;
}

void incrementNode(Node* current) {
	debug_print("Incrementing node ...")
	current->value++;
}

void decrementNode(Node* current) {
	debug_print("Decrementing node ...")
	current->value--;
}
