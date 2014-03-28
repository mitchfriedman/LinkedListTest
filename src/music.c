/*************************music.c****************************
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
#include "music.h"


int main(int argc, char * argv[])
{
    MusicRec * head;

    /* make sure the user entered a file in the command line arguments */
    if(argc != 2)
    {
        printf("Please specify a file name as a command line argument.\n");
        exit(0);
    }

    /* create the list with the text file */
    head = CreateList(argv[1]);

    /* print all the required information */
    PrintLengthOfPlayList(head);
    PrintAverageSize(head);
    printList(head);

    /* free the memory in the list */
    destroyList(head);

    return(0);
}
void PrintLengthOfPlayList(MusicRec * theList)
{
    int totalSecs;
    int hours;
    int minutes;
    int seconds;
    MusicRec * current;

    /* initialize the integers to = */
    totalSecs = 0;
    hours     = 0;
    minutes   = 0;
    seconds   = 0;

    /* set current to point to the front of the list */
    current = theList;

    while(current != NULL)
    {  
        /* add up each of the total seconds and move to the next node */
        totalSecs += current->lengthInSeconds;
        current = current->next;
    }
    /* calculate the total hours minutes and seconds */
    hours   = totalSecs / 3600;
    totalSecs = totalSecs - hours * 3600;    
    minutes = totalSecs / 60;
    totalSecs = totalSecs - minutes * 60;
    seconds = totalSecs;

    /* print them */
    if(hours < 10)
    {
        printf("0%d:%d:%d\r\n", hours, minutes, seconds);
    }
    else
    {
        printf("%d:%d:%d\r\n", hours, minutes, seconds);
    }
    
}
void PrintAverageSize(MusicRec * theList)
{
    MusicRec * current;
    double total;
    double average;
    int count;

    current = theList;
    count = 0;
    total = 0;
    average = 0;

    while(current != NULL)
    {
        /* add up the total file sizes and the count */
        total += current->sizeInKB;
        count++;
        current = current->next;
    }
    /* calculate the average and print it */
    average = total / count;
    printf("%.2f\n",average);   
}
MusicRec * CreateList(char * fileName)
{
    MusicRec * head;
    MusicRec * toAdd;
    FILE * file;
    char fileContents[200];
    char * line;
    bool headExists;

    /* open the text file and read it */
    file = fopen(fileName, "r");
    if(file == NULL)
    {
        printf("The file specified does not exist. Try again.\n");
        exit(0);
    }
    /* start without a head */
    headExists = false;
    while(fgets(fileContents, sizeof(fileContents), file) != NULL)
    {
        /* split the text file by new lines */
        line = strtok(fileContents, "\n");
        
        /* if the line does not contain at least 1 letter between commas it is too short */
        if(strlen(fileContents) < 8)
            continue;

        /* if we are parsing the first element, we create the head */
        if(!headExists)
        {
            /* create the node to add */
            toAdd = ParseLine(line);

            /* if all went well and it is set, set it to the head */
            if(toAdd != NULL)
            {
                headExists = true;
                head = toAdd;
            }
        }
        else
        {
            toAdd = ParseLine(line);

            if(toAdd != NULL)
            {    
                if(toAdd->type == 'a')
                {
                    /* add it to the front */
                    head = addToFront(head, toAdd);
                }
                else
                {
                    /* add it to the back */
                    head = addToBack(head, toAdd);
                }
            }
        }   
    }
    /* close the file */
    fclose(file);
    
    return head;
}
MusicRec * ParseLine(char * line)
{
    char * chunkOfLine;
    char * artist;
    char * title;
    char * size;
    char * length;
    char * lineCopy;
    int lengthInt;
    double sizeDecimal;
    int count;
    char * type;
    MusicRec * current;

    /* if its too short, exit */
    if(strlen(line) < 8)
    {
        return NULL;
    }

    /* create a copy to close */
    lineCopy = malloc(sizeof(char)*strlen(line)+1);
    strcpy(lineCopy, line);
    count = 0;

    /* split the line  by commas */
    chunkOfLine = strtok(lineCopy, ",");

    /* make sure there are 4 commas */
    while(chunkOfLine != NULL)
    {
        chunkOfLine = strtok(NULL, ",");
        count++;
    }
    free(lineCopy);
    if(count != 5)
    {

        return NULL;
    }
    
    
    /* set all the values in strings */
    artist = strtok(line, ",");
    title  = strtok(NULL, ",");
    length = strtok(NULL, ",");
    size   = strtok(NULL, ",");
    type   = strtok(NULL,",");

   
   /* if anything is not there, exit the function */ 
    if(artist  == NULL || strlen(artist) == 0 
     || title  == NULL || strlen(title)  == 0 
     || length == NULL || strlen(length) == 0 
     || size   == NULL || strlen(size)   == 0 
     || type   == NULL || strlen(type)   != 1)
    {
        return NULL;
    }

    /* convert the numbers to floats and integers */
    sizeDecimal = atof(size);
    lengthInt   = atoi(length);

    /* create the record and return it */
    current = createRecord(title, artist, sizeDecimal, lengthInt, type[0]);
    return current;

}





