#include <stdio.h>
#include <stdlib.h>

// Define Node Struct
typedef struct {
	void* next;
	int data;
}Node;

// Global Head
Node *head = NULL;

// Add a node to the list
Node *addNode(int data)
{
	Node *new_node = NULL;

	// --- Two cases ---
	// List is empty
	if (head == NULL)
	{
		new_node = malloc(sizeof(Node));
		if (new_node == NULL)
		{
			// Node memory allocation failed.
			return NULL;
		}

		new_node->data = data;
		head = new_node;
		new_node->next = NULL;
	}
	else
	{
		// Items already exist in list
		new_node = malloc(sizeof(Node));
		if (new_node == NULL)
		{
			// Node memory allocation failed.
			return NULL;
		}
		new_node->data = data;
		// Direction: New node added from the left side. Eg. NEW_NODE->0->0->0->HEAD
		new_node->next = head;
		head = new_node;
	}
	return new_node;
}

void printMenu()
{
	printf("Choose from the following:\n");
	printf("\t1. Add a node to the list.\n");
	printf("\t2. Remove a node from list.\n");
	printf("\t3. Insert a node to the list.\n");
	printf("\t4. Print LinkedList.\n");
	printf("\t5. Quit.\n");
	return;
}

int removeNode(int data)
{
	// Keep track of current and previous node
	Node *current = head;
	Node *prev = head;

	while (current != NULL)
	{
		if (current->data == data)
		{
			// Current node is list head
			if (current == head)
			{
				head = current->next;
			}
			else
			{
				prev->next = current->next;
				free(current);
				current = NULL;
			}
			// Return success
			return 1;
		}

		// Keep looping
		prev = current;
		current = current->next;
	}
	// Return failed
	return 0;
}

Node *insertNode(int data, int position)
{
	Node *current = head;

	// Loop to the end
	while(current != NULL && position != 0)
	{
		position--;
	}

	// Position variable reached 0, then not available
	if (position != 0)
	{
		printf("Position too far into list!\n");
		return NULL;
	}

	// Found location that is safe
	Node *new_node = malloc(sizeof(Node));
	if (new_node == NULL)
	{
		return NULL;
	}

	new_node->data = data;

	// New nodes next is the current nodes next
	new_node->next = current->next;

	// The current nodes next is new node
	current->next = new_node;

	return new_node;

}

void printLinkedList()
{
	Node* current = head;

	while (current != NULL)
	{
		printf("%d->", current->data);
		// Move onto next iteration
		current = current->next;
	}
	printf("\n");
	return;

}

int main(int argc, char **argv)
{
	int option = -1;
	int arg1 = 0;
	int arg2 = 0;

	Node *new = NULL;

	// Keep looping until exit (5)
	while (option != 5)
	{
		printMenu();
		int usr_input = scanf("%d", &option);
		if (usr_input == 1 && option > 0 && option <= 5)
		{

			switch(option)
			{
				case 1:
					// Add
					printf("Enter an Integer: ");
					scanf("%d", &arg1);
					new = addNode(arg1);
					break;
				case 2:
					// Remove
					printf("What should be removed? ");
					scanf("%d", &arg1);
					int success = removeNode(arg1);
					if(!success)
					{
						printf("Element not found!\n");
					}
					break;
				case 3:
					// Insert
					printf("What value? ");
					scanf("%d", &arg1);
					printf("What position? ");
					scanf("%d", &arg2);
					new = insertNode(arg1, arg2);
					if (new == NULL)
					{
						printf("Failed to insert into list.\n");
					}
					break;
				case 4:
					// Print
					printLinkedList();
					break;
				case 5:
					// Exit
					
					// Loop through and free all allocated nodes;
					while (new != NULL)
					{
						free(new);
						new = new->next;
					}
					
					break;
			}
		}
	}
	return 0;
}
