#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"

//By Farzain Majeed

node *createNode(char data) {
	
	node *ptr = malloc(sizeof(node));

	if (ptr == NULL) {
		fprintf(stderr, "Its all ogre\n");
		exit(1);
	}

	ptr->data = data;
	ptr->next = NULL;

	return ptr;
}

node *insertAtTail(node *head, char data) {

	node *temp;

	if(head == NULL) 
       return createNode(data);

	for(temp = head; temp->next != NULL; temp = temp->next)
       ;
	//Here we have a tail insert.
	temp->next = createNode(data);
	return head;

}

void printList (node *head) {

	if (head == NULL) {
		printf("(empty string)\n");
		return;
	}

	for ( ; head != NULL; head = head->next) {
		printf("%c", head->data);
	}

	printf("\n");

}
//This is where we make our first string a list.
node *stringToList(char *str)  {

	int i;
	node *head = NULL;
	
	for (i = 0; i < strlen(str); i++) {
		//There is a special case for the head because it has to start somewhere!
		if (i == 0) {
			head = createNode(str[0]);
			continue;
		}
		//I used a tail insert function so that each char goes after the other.
		insertAtTail(head, str[i]);
	}

	return head;
}

node *reverseList(node *head) {

	//Lets make the past node NULL because, well, there is no previous node.
	//We would segfault w/o this
	node* past = NULL; 
    node* present = head;
    node* future;

    //We want to keep going until we hit the end of our list.
    while (present != NULL)
    {
    	//Set future = next node in linked list.
        future  = present->next; 
        //Set = to your past node.  This starts at NULL. 
        present->next = past;   
        //This is where we actually reverse. Set the address of the previous node
        //to the one we are on RIGHT NOW.
        past = present;
        //This is here to continue the loop, so we hit the end of our lsit. 
        present = future;
    }
    //At the end of the loop, past will be the start of our list.
    head = past;

    return head;

}

node *replaceChar(node *head, char key, char *str) {

	node* tempHead = NULL;
	node* present = head;
	node* past;
	node* tempDeath;
	node* head2;
	node* temp2;
	node* tempCopy;
	node* tempCopy2;
	node* head3;

	//This checks for NULL or empty strings.
	if(str == NULL || strcmp(str, "") == 0) {

		while (present != NULL) {
			//If we get an empty or NULL string, we want to delete the nodes
			//that have our key
			if(key == present->data) {

				//There is a special case for the head, since head has no past.
				if (head == present) {
					//Lets move our head along.
					head = present->next;
					//Free our old head.
					free(present);
					//Lets set our present again
					present = head;
					//I continue because everything at this point is done.
					continue;
				}

				//Lets store what we want to destory.
				tempDeath = present;
				//Move our past long
				past->next = present->next;
				//Move our present along
				present = present->next;
				free(tempDeath);	
				continue;
			}
			//This is here to make sure that past/present move on... 
			//Even if there is match with the key.
			past = present;
			present = present->next;
		}
		return head;
	}

	//If the program reaches this point, it means we have encountered a string.
	else {
		//I just use this as a tester.
		head2 = stringToList(str);

		while(present != NULL) {
			if(key == present->data) {

				if (head == present) {
					
					//Lets free what we want to replace
					head = present->next;
					node* headHolder = present->next;
					free(present);
					//This holds the first node of our NEW string.
       				tempCopy = createNode(head2->data);
       				//We want to repalce our OLD head node with the NEW one. 
       				head = tempCopy;
       				//Lets start going through our NEW list.
       				tempCopy2 = head2->next;

       				//While our NEW list != NULL
       				while(tempCopy2 != NULL) {
       					//Insert NEW node into OLD list.
       					tempCopy->next = createNode(tempCopy2->data);
       					//Move this along so it grabs the next NEW node.
       					tempCopy2 = tempCopy2->next;
       					//Move this along so our OLD list pointer gets the next node.
       					tempCopy = tempCopy->next;
       				}

       				//At this point tempCopy is at the end of our new List
       				//It's next need to be equal to present->next
       				tempCopy->next = headHolder;
       				//Our present has moved along.
       				present = headHolder;
					continue;
				}

				//All this code here is very similar to the code up top.
				//I'll include the main differences.
				tempDeath = present;
				//First, we have a past pointer! This chnages things up.
				past->next = present->next;
				present = present->next;
				free(tempDeath);

				//This hold access to our NEW head.
				tempCopy =  createNode(head2->data);
				//Set the next of our OLD->next so its our new one now.
				past->next = tempCopy;
				//This will help is access our OLD linked list.
				tempCopy2 = head2->next;

				//This is the same while loop as above.
				while(tempCopy2 != NULL) {
					tempCopy->next = createNode(tempCopy2->data);
					tempCopy2 = tempCopy2->next;
					tempCopy = tempCopy->next;
				}
				
       			tempCopy->next = present;
       			//We need to move the past along!
       			past = tempCopy;
				continue;
			}

			//We still move past along if nothing is found.
			past = present;
			present = present->next;

		}
		return head;

	}


}


int main(int argc, char **argv) {

	int i, c;
	char firstInput[1024];
	char keyReplacer[1024];
	char keyToReplace;
	char toDelete;
	node *head = NULL;
	node *temp;

	//This is a loop to find all arguments passed to main.
	//for (i = 0; i < argc; i++)
	//	printf("argv[%d]: %s\n", i, argv[i]);

	FILE *file;
	//We use argv[1] since thats the filename passed from main.
	file = fopen(argv[1], "r");
	//Lets grab that first string.
	fscanf(file, "%s", firstInput);
	head = stringToList(firstInput);
	
	//Lets get the rest of the input.
	while((c = getc(file)) != EOF) {

		//printf("%c", c);

		//We use a nice elegant switch here!
		switch(c) {
			case '@':
				fscanf(file, " %c", &keyToReplace);
				//printf("Your key is: %c", keyToReplace); 
				fscanf(file, " %s", keyReplacer);
				//printf(" Your replacement is: %s\n", keyReplacer);
				head = replaceChar(head, keyToReplace, keyReplacer);
				break;
			
			case '-':
				fscanf(file, " %c", &toDelete);
				head = replaceChar(head, toDelete, "");
				break;

			case '~':
				head = reverseList(head);
				break;

			case '!': {
				printList(head);
				break;
			}
		}
	}


	fclose(file);

	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}


	return 0;

}
