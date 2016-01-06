# ListyStrings
**Main concepts explored in this program:**

Linked list manipulation (such as replacement and reversal), structs, dynamic memory allocation, input file commands, command line arguments.

**Description**

This program takes in a string and converts the string into a linked list with each char representing a node in the list. It takes commands from a file to manipulate the linked list using specfic chars.

**File Commands**


*First input of file will always be a string*.

Command "*@ (key) (str)*" where (key) is a char and (str) is a string. If the (key) is found in the linked list then it will be replaced with the (str) that is given.


Command "*- (key)*" where (key) is a single char.  If they (key) is found in the linked list than it will be deleted. 


Command "*~*" will reverse the linked list.


Command "*!*" will print the linked list. 

**Sample Input**
```
elder
!
~
!
- e
!
@ r ri
!
```

**Sample Output**
```
elder
redle
rdle
riddle
```



 
