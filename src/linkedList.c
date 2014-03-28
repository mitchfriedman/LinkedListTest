/*************************linkedList.c****************************
Student Name: Mitchell Friedman              Student Number: 0828745
Date:         Wed, March 26, 2014            Course Name:    CIS2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

MusicRec * createRecord(char * title, char * artist, double fileSize, int length, char theType)
{
    MusicRec * temp;

    /* malloc memory for 1 MusicRec */
    temp = malloc(sizeof(MusicRec));

    /* malloc failed, lets get outta here */
    if(temp == NULL)
    {
        return NULL;
    }
    /* malloc memory for the title */
    temp->title = malloc(sizeof(char) * (strlen(title) +1));

    /* malloc memory for the artist */
    temp->artist = malloc(sizeof(char) * (strlen(artist) + 1));

    /* if malloc fails return NULL */
    if(temp->title == NULL)
    {
        free(temp->artist);
        return NULL;
    }
    
    if(temp->artist == NULL)
    {
        free(temp->title);
        return NULL;
    }

    strcpy(temp->title,  title);
    strcpy(temp->artist, artist);
    /* copy the rest of the stuff */
    temp->sizeInKB = fileSize;
    temp->lengthInSeconds = length;
    temp->type = theType;
    temp->next = NULL;

    return temp;
}

char * printRecord(MusicRec * toPrint)
{
    char * thePrint;
    char * title;
    char * artist;
    char * fileSize;
    char * length;

    /* put all the information into char * so
    we can copy everything to a new string to return */

    title = malloc(sizeof(char)*strlen(toPrint->title)+1);
    strcpy(title, toPrint->title);

    artist = malloc(sizeof(char)*strlen(toPrint->artist)+1);
    strcpy(artist, toPrint->artist);

    fileSize = malloc(sizeof(char)*12);
    sprintf(fileSize, "%.2f", toPrint->sizeInKB);

    length = malloc(sizeof(char)*10);
    sprintf(length, "%d", toPrint->lengthInSeconds);

    thePrint = malloc(sizeof(char)*strlen(title)+strlen(artist)+25);
    
    /* copy all the required information as needed */
    strcpy(thePrint, title);
    strcat(thePrint, " (");
    strcat(thePrint, artist);
    strcat(thePrint, "):");
    strcat(thePrint, length);
    strcat(thePrint, "[");
    strcat(thePrint, fileSize);
    strcat(thePrint, "]");

    /* free the memory we malloced */
    free(title);
    free(artist);
    free(fileSize);
    free(length);

    return thePrint;


}
void destroyRecord(MusicRec * theRecord)
{
    /* if we try to destroy NULL, don't do anything */
    if(theRecord != NULL)
    {
        /* if the title is there, free it */
        if(theRecord->title != NULL && strlen(theRecord->title) != 0)
              free(theRecord->title);

        /* if the artist is there, free it */
        if(theRecord->artist != NULL && strlen(theRecord->artist) != 0)
            free(theRecord->artist);

        /* free the record itself */
        free(theRecord);
    }
    
}

MusicRec * addToFront(MusicRec * theList, MusicRec * toBeAdded)
{
    /* make the pointer to be added to the front
    point to the first element */
    toBeAdded->next = theList;
    /* make the list point to the newly added element */
    theList = toBeAdded;
    return theList;
}

MusicRec * addToBack(MusicRec *  theList, MusicRec * toBeAdded)
{
    MusicRec * last;

    if(theList == NULL)
    {
        return NULL;
    }
    /* find the last item */
    last = getLastItem(theList);

    /* set the next pointer of the last item to the toBeAdded struct */
    last->next = toBeAdded;

    return theList;
}
MusicRec * removeFromFront(MusicRec * theList)
{
    MusicRec * next;
    /* if the list is empty */
    if(theList == NULL)
    {
        return NULL;
    }

    /* get the second element of the list and return it */
    next = theList->next;

    return next;
}
MusicRec * removeFromBack(MusicRec *  theList)
{
    MusicRec * current;
    MusicRec * parent;
    MusicRec * last;

    /* if the list is empty */
    if(theList == NULL)
    {
        return NULL;
    }
    /* start the beginning */
    current = theList;

    /* go until the last element is NULL */
    while(current->next != NULL)
    {
        parent = current;
        current = current->next;
    }
    /* we have the last element */
    last = parent->next;
    /* REMOVE next->next */
    parent->next = NULL;

    return last;
}
MusicRec * getLastItem(MusicRec * theList)
{
    MusicRec * next; 

    /* if the list is empty */
    if(theList == NULL)
    {
        return NULL;
    }
    /* start at the second item */
    next = theList->next;

    /* go until the next item is NULL */
    while(next->next != NULL)
    {
        next = next->next;
    }
    /* return the last item */
    return next;
}

bool isEmpty(MusicRec * theList)
{
    /* if the list is empty, it is empty */
    if(theList == NULL)
    {
        return true;
    }
    return false;
}
void printList(MusicRec *  theList)
{
    MusicRec * next;
    char * toPrint;

    /* if the list is empty */
    if(theList == NULL)
    {
        return;
    }
    /* star at the beginning */
    next = theList;

    /* go until the end */
    while(next != NULL)
    {
        /* print the record and free the memory */
        toPrint = printRecord(next);
        printf("%s\n", toPrint);
        free(toPrint);
        /* go to the next element */
        next = next->next;
    }
    
}
void destroyList(MusicRec * theList)
{
    MusicRec * current;
    MusicRec * next;

    next = theList;
    /* if it is already empty... */
    if(theList == NULL)
    {
        return;
    }
    else
    {
        /* start at the beginning */
        next = theList;

        /* empty the list */
        while(next != NULL)
        {
            current = next;
            next = current->next;
            destroyRecord(current);
            
        }
        
    }
    
}





