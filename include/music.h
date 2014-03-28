#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"


/*
Description: 
A function to create the linked list (the playlist) of songs 
and connect them together and fill them information provided in the text files

Parameters:
This function takes in a string that is the full path to the file name where the
songs information is

Return:
returns the head of the newly created list
*/
MusicRec * CreateList(char * fileName);

/*
Description: 
A function to parse a single line from the text file and create a single song 
struct out of the information

Parameters:
This function takes in the string value of the current line it is parsing

Return:
returns the MusicRec struct that it created 
*/
MusicRec * ParseLine(char * line);

/*
Description: 
A function to print the total length of the playlist to stdout

Parameters:
This function takes in the head of the list

Return:
no return, void function
*/
void PrintLengthOfPlayList(MusicRec * theList);

/*
Description: 
A function to print the average file size of the playlist

Parameters:
This function takes in the head of the list

Return:
no return, void function
*/
void PrintAverageSize(MusicRec * theList);