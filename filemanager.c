#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int bufferSize = 120;
int logBufferSize = 200; 
int pathNameBufferSize = 1000;
int fileNameBufferSize = 200;

char blankSpace = ' ';

char *logFile = "logFile_fh6G4mYl3tXn8HD5aOi825Km420r.txt"; //Log file name changeable

void updateLog(); // Fnunction prototype

/**
 * Checks the status of the file pointed to by fp.
 * Prints an error message when appropriate
 * 
 * @param  fp  file pointer
 * @return     1 when no error, -1 when error encountered
 **/
int fileStatus(FILE *fp)
{
    if (fp == NULL)
    {
        perror("Error");
        return -1;
    }
    else
    {
        return 1;
    }
}

/**
 * Slices a pathname into the directory component and file component.
 * The component returned 
 * 
 * @param  pathname      the pathname of the file. Mostly known as the filename when called from other functions.
 * @param  toReturn      the component of the pathname to return. Either dirName or fileName.
 * @return dirNamePart  :the directory component of the pathname.
 *         fileNamePart :the file component of the pathname.
 **/
char *slicePathname(const char *pathname, const char *toReturn)
{
    //Copy the original pathname into a string
    char copyStr[pathNameBufferSize];
    strcpy(copyStr, pathname);

    /* Create pointers and allocate memory for each of the pathname components */
    char *dirNamePart = malloc(sizeof(char) * pathNameBufferSize);
    char *fileNamePart = malloc(sizeof(char) * fileNameBufferSize);

    int p;
    for (p = strlen(pathname); pathname[p] != '/'; p--)
    {
        // Update p
        // The value of p after this loop executes is the index of the last '/' in the pathname, if present.
    }

    if (p < 0)
    {
        /* When there is no '/' in the path name */
        strcpy(dirNamePart, ".");       // The directory is the current directory, '.'
        strcpy(fileNamePart, pathname); // The file name is the pathname
    }
    else
    {
        /* When '/' is present */

        // Copy the pathname up until the last '/', which is given by index p. Copied into dirNamePart
        strncpy(dirNamePart, pathname, sizeof(char) * p);

        /* Copy sections of the pathname separated by '/' into fileNamePart.
        * The while loop continues copying and overwriting the value of fileNamePart
        * until the last string is copied. This last string is the file name.
        */
        strcpy(fileNamePart, strtok(copyStr, "/\n"));
        while (strstr(dirNamePart, fileNamePart) != NULL)
        {
            strcpy(fileNamePart, strtok(NULL, "/\n"));
        }
    }

    // Based on the toReturn argument, return a component.
    if (strcmp(toReturn, "dirName") == 0)
    {
        return dirNamePart;
    }
    else
    {
        return fileNamePart;
    }
}

/**
 * Checks whether a file exists.
 * 
 * @param  filename  the name of the file to be checked
 * @return           1 if the file exists.
 *                   0 if the file does not exist.
 **/
int fileExists(const char *filename)
{
    char *dirNamePart;
    char *fileNamePart;

    // Separate the components of the filename (pathname).
    fileNamePart = slicePathname(filename, "fileName");
    dirNamePart = slicePathname(filename, "dirName");

    // Open the directory of the file.
    DIR *fileDir;
    fileDir = opendir(dirNamePart);

    // If the directory opens successfully,
    if (fileDir != NULL)
    {
        // Read and store entries in fileItem
        struct dirent *fileItem;
        fileItem = readdir(fileDir);

        while (fileItem != NULL)
        {
            // Compare the name of each entry to the file name.
            if (strcmp(fileItem->d_name, fileNamePart) == 0)
            {
                // If a match is found, the file exists. Return 1.
                // Free the memory allocated by the slicePathname function.
                closedir(fileDir);
                free(dirNamePart);
                free(fileNamePart);
                return 1;
            }
            fileItem = readdir(fileDir);
        }

        // Return 0 if no match is found. The file does not exist.
        closedir(fileDir);
        return 0;
    }
    else
    {
        perror("Error");
        // Free the memory allocated by the slicePathname function.
        free(dirNamePart);
        free(fileNamePart);
        closedir(fileDir);
        return 0;
    }
}

/**
 * Makes a new directory.
 * 
 * @param dirname the name of the directory to be created.
 **/
void makedir(const char *dirname)
{
    // Make a directory with read, write and execute permissions for just the user.
    if (mkdir(dirname, 0700) == 0)
    {
        printf("Directory '%s' created.\n", dirname);
    }
    else
    {
        perror("Error");
    }
}

/**
 * Changes the current working directory.
 * 
 * @param dirname the name of the directory to be changed to.
 **/
void changedir(const char *dirname)
{
    // Attempt to change the directory. Print error message if unsuccessful
    if (chdir(dirname) != 0)
    {
        perror("Error");
    }
}

/**
 * Lists the names of all the items in a directory.
 * 
 * @param dirname the name of the directory to be listed.
 **/
void listDir(const char *dirname)
{
    // Open the directory
    DIR *tDir;
    tDir = opendir(dirname);

    // If directory opened,
    if (tDir != NULL)
    {
        // Read and store the entries in fileItem
        struct dirent *fileItem;
        fileItem = readdir(tDir);

        while (fileItem != NULL)
        {
            // Print the name of each entry.
            printf("-> %s\n", fileItem->d_name);
            fileItem = readdir(tDir);
        }
    }
    else
    {
        perror("Error");
    }
}

/**
 * Converts all the characters of a string to lowercase.
 * 
 * @param  s  the string to be converted.
 * @return s :the lowercase string.
 **/
char *lowerStr(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
    {
        // Convert each character of the string to lowercase.
        s[i] = tolower(s[i]);
    }
    return s;
}

/**
 * Counts the number of digits in an integer.
 * 
 * @param  number   the integer whose digits are to be counted.
 * @return counter :the number of digits.
 **/
int digitCount(int number)
{
    // The maximum length of a number applicable is 20.
    char digitstr[20];

    // Store the number as a string in digitstr.
    sprintf(digitstr, "%d", number);

    // Count the number of digits.
    int counter = strlen(digitstr);
    return counter;
}

/**
 * Counts the number of lines in a file.
 * 
 * @param   filename  the name of the file to be counted.
 * @return  counter  :the number of lines.
 **/
int countLines(const char *filename)
{
    if (fileExists(filename) == 1)
    {
        char fileStr[bufferSize];

        int counter = 0;
        FILE *fp;
        fpos_t pos;

        fp = fopen(filename, "r");

        // If the file is opened successfully,
        if (fileStatus(fp) == 1)
        {
            /* This allows us to check for a blank file: The EOF indicator will already be set */

            fgetpos(fp, &pos);         // Store the position of the 'cursor'
            char nextChar = fgetc(fp); // Get the next character
            fsetpos(fp, &pos);         // Reset the position of the 'cursor'

            // If the next character is not the End-of-File
            if (nextChar != EOF)
            {
                /* Scan the next [bufferSize] bytes and store them in fileStr. Loop until EOF condition is met */
                while (fgets(fileStr, bufferSize, fp) != NULL)
                {
                    if (fileStr[strlen(fileStr) - 1] == '\n')
                    {
                        // If the last character in the string is a newline, increment the counter.
                        counter++;
                    }
                }

                // Increment for the last line which does not end with a newline.
                counter++;


                fclose(fp);
            }
        }

        return counter;
    }
}

/**
 * Creates a new file.
 * 
 * @param  filename  the name of the file to be created.
 * @return create   :the character which denotes whether or not the file was been created.
 *                   Also stores the user input for when the program asks for an overwrite.
 *                   'y' is for yes and 'n' is for no.
 **/
char createFile(const char *filename)
{
    char create;
    FILE *fp;

    if (fileExists(filename) == 0)
    {
        // Create the file if it does not exist
        fp = fopen(filename, "w");
        if (fileStatus(fp) == 1)
        {
            fclose(fp);
            printf("File '%s' created.\n", filename);

            create = 'y'; // Yes, the file has been created
            updateLog(filename, 0, "+ File created.");
        }
    }
    else
    {
        // If the file exists, ask for overwrite
        printf("File '%s' already exists. Overwrite? y/n? ", filename);
        scanf(" %c", &create);

        if (tolower(create) == 'y')
        {
            // If 'y', create the file
            fp = fopen(filename, "w");
            if (fileStatus(fp) == 1)
            {
                fclose(fp);
                printf("File '%s' overwritten.\n", filename);

                updateLog(filename, 0, "- File overwritten.");
            }
        }
        else
        {
            create = 'n';
            printf("File '%s' preserved.\n", filename);
        }
    }

    return create;
}

/**
 * Deletes a file.
 * 
 * @param  filename  the name of the file to be deleted.
 **/
void deleteFile(const char *filename)
{
    if (fileExists(filename) == 0)
    {
        printf("File '%s' does not exist.\n", filename);
    }
    else
    {
        if (remove(filename) == 0)
        {
            printf("File '%s' deleted.\n", filename);

            updateLog(filename, 1, "- File deleted.");
        }
        else
        {
            perror("Error");
        }
    }
}

/**
 * Sends the content of a file to the display.
 * The displayed content is the range of lines from startLine to endLine (inclusive).
 * Includes line numbers.
 * 
 * @param  filename   the name of the file to be displayed.
 * @param  startLine  the start line number of the display range.
 * @param  endLine    the end line number of the display range.
 * @return            0 if an error is encountered.
 *                    1 if the content can be displayed.
 **/
int sendToDisplay(const char *filename, int startLine, int endLine)
{
    if (fileExists(filename) == 0)
    {
        printf("File '%s' does not exist.\n", filename);
        return 0;
    }
    else
    {
        int totalLines = countLines(filename);

        if (startLine < 0 || startLine > endLine || endLine > totalLines)
        {
            printf("Invalid line number for file '%s' (%d lines)\n", filename, totalLines);
            return 0;
        }

        else
        {
            printf("---------------------------\n");

            char fileStr[bufferSize];      // For reading lines with fgets.
            char newFileStr[bufferSize];   // A modified version of fileStr.
            char breakStr[bufferSize - 1]; // For long strings which get broken at the end of a line.
            char nextChar;

            int newLine = 1;   // Is a newline? 1: yes, 0: no
            int multiLine = 0; // Is a multiline?
            int breakLong = 0; // Is a broken word? (excessively longer than the buffer)

            int counter = 1;

            /* Width settings for showing line numbers */
            int sideWidth = 1;
            int preLineWidth = 2;
            char blankSpace = ' ';

            fpos_t pos;

            FILE *fp;
            fp = fopen(filename, "r");

            if (fileStatus(fp) == 1)
            {
                // Call fgets and increment counter until the 'cursor' is at startLine.
                while (counter < startLine)
                {
                    fgets(fileStr, bufferSize, fp);
                    if (fileStr[strlen(fileStr) - 1] == '\n')
                    {
                        // Increment counter at newline.
                        counter++;
                    }
                }

                // For a blank file,
                if (totalLines == 0)
                {
                    printf("\n");
                }
                else
                {
                    /* If the file is not blank */
                    do
                    {
                        sideWidth = digitCount(totalLines);

                        // Get the next [bufferSize] bytes
                        fgets(fileStr, bufferSize, fp);

                        fgetpos(fp, &pos);    // Store the position of the 'cursor'
                        nextChar = fgetc(fp); // Get the next character
                        fsetpos(fp, &pos);    // Reset the position

                        // If the next character is not the EOF
                        if (nextChar != EOF)
                        {
                            // If the last character of the string is a newline and newline is yes
                            if (fileStr[strlen(fileStr) - 1] == '\n' && newLine == 1)
                            {
                                printf("%*d|%*c%s", sideWidth, counter, preLineWidth, blankSpace, fileStr);
                                multiLine = 0;
                                counter++;
                            }
                            // If the last character of the string is a newline
                            // and the first character is a space
                            // and the string is not already on a newline. (Was a multiline)
                            else if (fileStr[strlen(fileStr) - 1] == '\n' && fileStr[0] == ' ')
                            {
                                printf("%*c%s", sideWidth + preLineWidth, blankSpace, fileStr);
                                // The next line will be a newline. Multiline has ended.
                                newLine = 1;
                                multiLine = 0;
                            }
                            // If the last character of the string is a newline
                            // and the first word of the string is a continuation of a word on the previous line. (Broken)
                            // and the string is not already on a newline. (Was a multiline)
                            else if (fileStr[strlen(fileStr) - 1] == '\n' && breakLong == 1)
                            {
                                printf("\n%*c%s", sideWidth + preLineWidth + 1, blankSpace, fileStr);
                                newLine = 1;
                                multiLine = 0;
                                breakLong = 0;
                            }
                            // If the last character of the string is a newline
                            // and it is not broken
                            // and the string is not already on a newline. (Was a multiline)
                            else if (fileStr[strlen(fileStr) - 1] == '\n')
                            {
                                printf("%s", fileStr);
                                newLine = 1;
                                multiLine = 0;
                            }
                            // If the next character after the scanned string is a blank space
                            // And it is on a newline
                            // But the last character is not a newline
                            else if (nextChar == blankSpace && newLine == 1 && multiLine == 0) //changed multi 0 to newl 1. ok put the two conditions together now!
                            {
                                printf("%2d|%*c%s\n", counter, preLineWidth, blankSpace, fileStr);
                                multiLine = 1; // Begin multiline
                                counter++;
                            }
                            // If the next character after the scanned string is a blank space
                            // And it is not on a newline (Was multiline)
                            // And the first character is a blank space
                            else if (nextChar == blankSpace && newLine == 0 && multiLine == 1 && fileStr[0] == ' ')
                            {
                                printf("%*c\b%s\n", sideWidth + preLineWidth + 1, blankSpace, fileStr);
                            }
                            // If the next character after the scanned string is a blank space
                            // And it is not on a newline (Was multiline)
                            else if (nextChar == blankSpace && newLine == 0 && multiLine == 1)
                            {
                                printf("%s\n", fileStr);
                            }
                            // If the next character after the scanned string is not a blankspace
                            // Or is a multiline
                            else if (nextChar != blankSpace || multiLine == 1)
                            {
                                // If the first character of the string is a blankspace and multiline
                                if (fileStr[0] == blankSpace && multiLine == 1)
                                {
                                    printf("%*c", sideWidth + preLineWidth, blankSpace);
                                }

                                int i = strlen(fileStr) - 1;
                                int k = 0;

                                // If the next character after a scanned string is not a blankspace,
                                // At this point in the filtering, it indicates that the last word has to be broken.
                                if (nextChar != blankSpace)
                                {
                                    // Find a space in the scanned string, BEFORE the word to be broken
                                    while (fileStr[i] != blankSpace && i >= 0 && k < bufferSize)
                                    {
                                        // BreakStr stores characters until a space is reached. (Reading backwards)
                                        breakStr[k] = fileStr[i];
                                        fileStr[i] = blankSpace;
                                        k++;
                                        i--;
                                    }
                                }

                                if (i <= 0 && fileStr[i] != blankSpace)
                                {
                                    // For a very long word, which is longer than the buffer. The word itself spans multiple lines.
                                    breakLong = 1;
                                }
                                else
                                {
                                    // If there are no excessively long words
                                    breakLong = 0;

                                    memset(newFileStr, 0, strlen(newFileStr));      // Reset newFileStr from previous use if applicable
                                    strncpy(newFileStr, fileStr, sizeof(char) * i); // Copy fileStr into newFileStr (until the last blank space if applicable)
                                }

                                // On a newline and the last word is shifted to the next line
                                if (multiLine == 0 && breakLong == 0)
                                {
                                    printf("%*d|%*c%s\n", sideWidth, counter, preLineWidth, blankSpace, newFileStr);
                                    counter++;
                                }
                                // On a newline and a word is excessively longer than the buffer
                                else if (newLine == 1 && breakLong == 1) //long continuos word on a new line, multi is 0
                                {
                                    printf("%*d|%*c", sideWidth, counter, preLineWidth, blankSpace);
                                    counter++;
                                }
                                // Not a newline (Is a multiline), and a word is excessively longer than a buffer
                                else if (breakLong == 1) //break long on a multi line
                                {
                                    printf("\n");
                                }
                                else
                                {
                                    printf("%s\n", newFileStr);
                                }

                                /* This section is for displaying words which had to be shifted to the next line
                                *  because the buffer cut them of.
                                *  Such a word is stored in breakStr.
                                *  They need to be reversed because the characters were read from the end of a string backwards.
                                **/
                                if (nextChar != blankSpace)
                                {
                                    // If the word is not longer than the buffer.
                                    if (breakLong == 0)
                                    {
                                        printf("%*c", sideWidth + preLineWidth + 1, blankSpace);
                                        // Reverse print the characters of the string.
                                        while (k != 0)
                                        {
                                            printf("%c", breakStr[k - 1]);
                                            k--;
                                        }
                                    }
                                    // If the word is excessively longer than the buffer.
                                    else
                                    {
                                        // Junk characters are sometimes printed at the end of the excessively long string.
                                        // This section ensures that there is no difference between the breakStr and the buffered fileStr
                                        int strErr = strlen(breakStr) - strlen(fileStr);
                                        while (strErr > 0)
                                        {
                                            // Junk replaced with blanks. Never more than 2 junk chars are produced.
                                            breakStr[strlen(breakStr) - strErr] = blankSpace;
                                            strErr--;
                                        } // find out where such error occurs.
                                        // ah!! I think i might have solved it by implementing the previous memset(...) so no more trailing blanks in filestr?
                                        

                                        if (newLine == 0)
                                        {
                                            printf("%*c", sideWidth + preLineWidth + 1, blankSpace);
                                        }

                                        // Reverse print the characters of the string.
                                        while (k != 0)
                                        {
                                            printf("%c", breakStr[k - 1]);
                                            k--;
                                        }
                                    }
                                }

                                multiLine = 1;
                                newLine = 0;
                            }
                            else
                            {
                                printf("%*d|%*c%s\n", sideWidth, counter, preLineWidth, blankSpace, fileStr);
                                multiLine = 0;
                                newLine = 1;
                                counter++;
                            }
                        }

                        // If the next character is the end of file
                        if (nextChar == EOF)
                        {
                            // Last word in file is excessively longer than the buffer
                            if (breakLong == 1)
                            {
                                printf("\n%*c", sideWidth + preLineWidth + 1, blankSpace);
                            }

                            // Last sentence is on a newline
                            if (newLine == 1)
                            {
                                printf("%*d|%*c%s", sideWidth, counter, preLineWidth, blankSpace, fileStr);
                                counter++; // Increment counter
                            }
                            else
                            {
                                // Multiline
                                printf("%s", fileStr);
                            }

                            // Last character is a newline. \n is the only character on the line.
                            // Counter was incremented on the previous step, so no need here.
                            if (fileStr[strlen(fileStr) - 1] == '\n')
                            {
                                printf("%*d|\n", sideWidth, counter);
                            }
                            else
                            {
                                printf("\n");
                            }
                            break;
                        }

                    } while (counter <= endLine || fileStr[strlen(fileStr) - 1] != '\n');

                    /*  fileStr[strlen(fileStr) - 1] != '\n' is needed when the EOF indicator is set.
                    /   The last step eventually goes through the EOF conditions which have break statements
                    **/
                }
                fclose(fp);
                printf("---------------------------\n");
                return 1;
            }
        }
    }
}

/**
 * Displays the contents of a file in a range (inclusive).
 * Makes a call to the sendToDisplay function.
 * 
 * @param  filename   the name of the file to be displayed.
 * @param  startLine  the start line number of the display range.
 * @param  endLine    the end line number of the display range.
 **/
void showLineRange(const char *filename, int startLine, int endLine)
{
    if (sendToDisplay(filename, startLine, endLine) == 1)
    {
        printf("File '%s' lines %d-%d displayed (%d lines).\n", filename, startLine, endLine, endLine - startLine + 1);
    }
}

/**
 * Displays a single line of a file.
 * 
 * @param  filename    the name of the file to be displayed.
 * @param  lineNumber  the line number of the line to be displayed.
 **/
void showLine(const char *filename, int lineNumber)
{
    if (sendToDisplay(filename, lineNumber, lineNumber) == 1)
    {
        printf("File '%s' line %d displayed.\n", filename, lineNumber);
    }
}

/**
 * Displays all the contents of a file.
 * 
 * @param  filename  the name of the file to be displayed.
 **/
void showFile(const char *filename)
{
    int totalLines = countLines(filename);
    if (sendToDisplay(filename, 0, totalLines) == 1)
    {
        printf("File '%s' displayed (%d lines).\n", filename, totalLines);
    }
}

/**
 * Displays the total number of lines in a file.
 * Makes a call the the countLines fucntion.
 * 
 * @param  filename  the name of the file to be counted.
 **/
void showLineCount(const char *filename)
{
    if (fileExists(filename) == 0)
    {
        printf("File '%s' does not exist.\n", filename);
    }
    else
    {
        printf("%d lines in file '%s'.\n", countLines(filename), filename);
    }
}

/**
 * Displays the change log of a single file.
 * 
 * @param  filename  the name of the file whose log is to be displayed.
 **/
void showSingleLog(const char *filename)
{
    if (fileExists(logFile) == 0)
    {
        printf("No changes have been logged yet.\nCertain file operations can update the log.\n");
    }
    else
    {
        FILE *fp;
        fp = fopen(logFile, "r");

        if (fileStatus(fp) == 1)
        {
            fpos_t pos;

            char bufferStr[logBufferSize]; // Holds the result of fgets
            char fnameStr[logBufferSize];  // The name of the file to be searched for in the log

            int startLine;
            int endLine;

            int counter = 1;

            // Store filename and the appropriate format of log entries in fnameStr.
            sprintf(fnameStr, "'%s' log:\n", filename);

            // Retrieve each line in the log file
            while (fgets(bufferStr, logBufferSize, fp) != NULL)
            {
                // Compare each line to fnameStr
                if (strcmp(bufferStr, fnameStr) == 0)
                {
                    // If a match is found, the start line is the log title of the file
                    startLine = counter;
                    break;
                }
                if (bufferStr[strlen(bufferStr) - 1] == '\n' && feof(fp) == 0)
                {
                    // Increment counter when a newline is reached
                    counter++;
                }
            }

            // Retrieve each line in the log file (after startLine)
            while (fgets(bufferStr, logBufferSize, fp) != NULL)
            {
                fgetpos(fp, &pos);         // Store the position of the cursor
                char nextChar = fgetc(fp); // Get the next character
                fsetpos(fp, &pos);         // Reset the position of the cursor

                if (bufferStr[strlen(bufferStr) - 1] == '\n' && feof(fp) == 0)
                {
                    // if a newline is reached and the EOF indicator is not set, increment counter
                    counter++;
                }
                if (nextChar == '\n')
                {
                    // if nextchar is a newline, the line is the endline for the log of filename
                    // This follows the format of the log file. Where two consecutive '\n' characters
                    // Indicate the end of the log for a file.
                    endLine = counter;
                    break;
                }
            }

            // If the EOF indicator is set, it means the cursor reached the EOF,
            // Without finding a match for fnameStr
            if (feof(fp) != 0)
            {
                printf("Log for file '%s' does not exist.\n", filename);
            }
            else
            {
                // Display only the log for filename
                showLineRange(logFile, startLine, endLine);
            }

            fclose(fp);
        }
    }
}

/**
 * Displays the full change log of all the files in the current working directory.
 * 
 **/
void showFullLog()
{
    if (fileExists(logFile) == 0)
    {
        printf("No changes have been logged yet.\nCertain file operations can update the log.\n");
    }
    else
    {
        bufferSize = logBufferSize;
        showFile(logFile);
    }
}

/**
 * Copies the contents of one file to another.
 * 
 * @param  origFile  the name of the file to be copied from.
 * @param  newFile   the name of the file to copy into.
 **/
void copyFile(const char *origFile, const char *newFile)
{
    if (origFile == newFile)
    {
        printf("Unable to copy '%s' to '%s'.\n", origFile, origFile);
    }
    else
    {
        if (fileExists(origFile) == 0)
        {
            printf("File '%s' does not exist.\n", origFile);
        }
        else
        {
            // Attempt to create newFile. Prompts to overwrite where applicable
            char opt = createFile(newFile);

            // If newFile created
            if (opt == 'y')
            {
                FILE *origfp;
                FILE *newfp;

                origfp = fopen(origFile, "r");
                newfp = fopen(newFile, "w");

                if (fileStatus(origfp) == 1 && fileStatus(newfp) == 1)
                {
                    char fileStr[bufferSize];

                    // Read each line in origFile
                    while (fgets(fileStr, bufferSize, origfp) != NULL)
                    {
                        // Write each line in newFile
                        fputs(fileStr, newfp);
                    }

                    fclose(origfp);
                    fclose(newfp);

                    printf("Copy complete.\n");

                    /* This section of code allows the names of both files to be included in both logs */
                    char logFormatStr[logBufferSize];
                    char logFormatStr2[logBufferSize];

                    // Store the file names and the appropriate formats.
                    sprintf(logFormatStr, "+ File copied to '%s'.", newFile);
                    sprintf(logFormatStr2, "+ File copied from '%s'.", origFile);

                    // Update the logs.
                    updateLog(origFile, 0, logFormatStr);
                    updateLog(newFile, 0, logFormatStr2);
                }
            }
        }
    }
}

/**
 * Adds a line to the end of a file.
 * 
 * @param  filename  the name of the file to be appended to.
 * @param  appendstr the string of text to append to the file.
 **/
void appendLine(const char *filename, const char *appendstr)
{
    int append = 1; // 1: append, 0: no append

    if (fileExists(filename) == 0)
    {
        // Option to create the file if it does not exist
        char opt;
        printf("File '%s' does not exist. Create '%s'? y/n? ", filename, filename);
        scanf(" %c", &opt);

        if (tolower(opt) == 'y')
        {
            createFile(filename);
            append = 1;
        }
        else
        {
            printf("Append operation cancelled.\n");
            append = 0;
        }
    }

    if (append == 1)
    {
        int totalLines = countLines(filename);
        FILE *fp;
        fp = fopen(filename, "a+");

        if (fileStatus(fp) == 1)
        {
            char endc;

            if (totalLines > 0)
            {
                // Get the last character of the file
                fseek(fp, -1, SEEK_END);
                endc = fgetc(fp);

                // If the file does not end on a newline
                if (endc != '\n')
                {
                    // Write a newline, so append starts on a newline
                    fputs("\n", fp);
                }
            }

            // Append the appendstr to the end of the file.
            fputs(appendstr, fp);
            fclose(fp);
            printf("Data has been appended to File '%s'.\n", filename);

            updateLog(filename, 0, "+ Line appended to file.");
        }
    }
}

/**
 * Deletes a range (inclusive) of lines from a file.
 * 
 * @param  filename   the name of the file to delete lines in.
 * @param  startLine  the start line number in the deletion range.
 * @param  endLine    the end line number in the deletion range.
 * @return            0 if the deletion cannot be done.
 *                    1 if the deletion can be done.
 **/
int lineDeletion(const char *filename, int startLine, int endLine)
{
    if (fileExists(filename) == 0)
    {
        printf("File '%s' does not exist.\n", filename);
        return 0;
    }
    else
    {
        int totalLines = countLines(filename);
        if (startLine < 1 || startLine > endLine || endLine > totalLines)
        {
            printf("Invalid deletion line number for file '%s' (%d lines)\n", filename, totalLines);
            return 0;
        }
        else
        {
            FILE *fp;
            FILE *tempfp;

            if (totalLines == 1)
            {
                fp = fopen(filename, "w");
                if (fileStatus(fp) == 1)
                {
                    fclose(fp);
                    printf("Deleted all lines (1 line) in '%s'\n", filename);

                    updateLog(filename, 0, "- Deleted line 1.");
                    return 1;
                }
            }

            else
            {
                fp = fopen(filename, "r"); // Open the target file
                tempfp = tmpfile();        // This creates a temporary file.

                if (fileStatus(fp) == 1 && fileStatus(tempfp) == 1)
                {
                    char fileStr[bufferSize];

                    int counter = 1;

                    // Scan file up to startLine in the range
                    while (counter < startLine)
                    {
                        fgets(fileStr, bufferSize, fp);

                        /*
                        * If the endline is the last line of the file:
                        * Replace the '\n' at the end of the line before startLine with ' ' (blank)
                        * This ensures that there is no trailing new line when the file is truncated. 
                        */
                        if (endLine == totalLines && counter == startLine - 1)
                        {
                            fileStr[strlen(fileStr) - 1] = ' '; // Replace '\n' with ' ' at the end of line
                            counter++;
                        }

                        // Add each line to the temporary file, up to the startLine.
                        fputs(fileStr, tempfp);

                        if (fileStr[strlen(fileStr) - 1] == '\n')
                        {
                            counter++;
                        }
                    }

                    // If the startLine is not the last line
                    if (startLine != totalLines)
                    {
                        // This scans the lines between the startLine and endLine
                        while (counter <= endLine)
                        {
                            fgets(fileStr, bufferSize, fp);

                            if ((fileStr[strlen(fileStr) - 1] == '\n') && feof(fp) == 0)
                            {
                                counter++;
                            }
                            if (feof(fp) != 0)
                            {
                                // endLine is the last line, end scan
                                break;
                            }
                        }

                        // This scans the remaining lines from the endLine to the last line.
                        while (counter <= totalLines)
                        {
                            if (fgets(fileStr, bufferSize, fp) != NULL)
                            {
                                // Add each line to the temp file
                                fputs(fileStr, tempfp);
                            }

                            if (fileStr[strlen(fileStr) - 1] == '\n' && feof(fp) == 0)
                            {
                                counter++;
                            }
                            if (feof(fp) != 0)
                            {
                                // EOF reached
                                break;
                            }
                        }
                    }

                    fseek(tempfp, 0, SEEK_SET);
                    fflush(tempfp);

                    freopen(filename, "w", fp); // Reopen the target file as a blank file

                    if (fileStatus(fp) == 1)
                    {
                        // Write the contents of the temp file into the target file
                        while (fgets(fileStr, bufferSize, tempfp) != NULL)
                        {
                            fputs(fileStr, fp);
                        }

                        fclose(fp);
                        fclose(tempfp);
                        return 1;
                    }
                }
            }
        }
    }
}

/**
 * Deletes a range (inclusive) of lines from a file.
 * Calls the function lineDeletion.
 * 
 * @param  filename   the name of the file to delete lines in.
 * @param  startLine  the start line number in the deletion range.
 * @param  endLine    the end line number in the deletion range.
 **/
void deleteLineRange(const char *filename, int startLine, int endLine)
{
    if (lineDeletion(filename, startLine, endLine) == 1)
    {
        printf("Deleted lines %d-%d in file '%s'\n", startLine, endLine, filename);

        char logFormatStr[logBufferSize];

        // Store operation log with the line numbers involved
        sprintf(logFormatStr, "- Deleted lines %d-%d.", startLine, endLine);

        updateLog(filename, 0, logFormatStr);
    }
}

/**
 * Deletes all lines from the given line number and downwards (inclusive). 
 * 
 * @param  filename    the name of the file to truncate.
 * @param  lineNumber  the number of the line to begin deletion.
 **/
void truncateFile(const char *filename, int lineNumber)
{
    if (lineDeletion(filename, lineNumber, countLines(filename)) == 1)
    {
        printf("Truncated file '%s' at line %d\n", filename, lineNumber);

        char logFormatStr[logBufferSize];

        // Store operation log with the line number involved
        sprintf(logFormatStr, "- Truncated file at line %d.", lineNumber);

        updateLog(filename, 0, logFormatStr);
    }
}

/**
 * Deletes a single line from a file/
 * 
 * @param  filename   the name of the file to delete a line in.
 * @param  lineNumber the number of the line to be deleted.
 **/
void deleteLine(const char *filename, int lineNumber)
{
    if (lineDeletion(filename, lineNumber, lineNumber) == 1)
    {
        printf("Deleted line %d in file '%s'\n", lineNumber, filename);

        char logFormatStr[logBufferSize];

        // Store operation log with the line number involved
        sprintf(logFormatStr, "- Deleted Line %d.", lineNumber);

        updateLog(filename, 0, logFormatStr);
    }
}

/**
 * Deletes all content in a file.
 * 
 * @param  filename  the name of the file to be cleared.
 **/
void clearFile(const char *filename)
{
    if (lineDeletion(filename, 1, countLines(filename)) == 1)
    {
        printf("File '%s' cleared.\n", filename);

        updateLog(filename, 0, "- Cleared File.");
    }
}

/**
 * Puts a string of text at the line number given.
 * The lines after the specified line number are pushed down.
 * 
 * @param  filename    the name of the file to be inserted into.
 * @param  lineNumber  the number of the line to insert at.
 * @param  insertStr   the string of text to insert.
 **/
void insertLine(const char *filename, int lineNumber, const char *insertStr)
{
    if (fileExists(filename) == 0)
    {
        printf("File '%s' does not exist.\n", filename);
    }
    else
    {
        int totalLines = countLines(filename);

        if (lineNumber == 0)
        {
            lineNumber = 1;
        }

        if (lineNumber < 0 || (lineNumber > totalLines && totalLines == 0 && lineNumber != 1))
        {
            printf("Invalid insertion line number for file '%s' (%d lines)\n", filename, totalLines);
        }
        else
        {
            char fileStr[bufferSize];
            int counter = 1;

            FILE *fp;
            FILE *tempfp;

            fp = fopen(filename, "r+"); // Open target file for reading and writing
            tempfp = tmpfile();         // Create temporary file

            if (fileStatus(fp) == 1 && fileStatus(tempfp) == 1)
            {
                // Scan each line from the first to the startLine, in the target file
                while (counter < lineNumber)
                {
                    fgets(fileStr, bufferSize, fp);

                    // Write each line to the temp file
                    fputs(fileStr, tempfp);

                    if (fileStr[strlen(fileStr) - 1] == '\n')
                    {
                        counter++;
                    }
                }

                // Write the insertStr at the target line number, in tempFile
                if (counter == lineNumber)
                {
                    fputs(insertStr, tempfp);
                    fputs("\n", tempfp); // For the next line
                }

                // Continue scanning the target file till the EOF
                while (counter <= countLines(filename))
                {
                    if (fgets(fileStr, bufferSize, fp) != NULL)
                    {
                        // Write each line to the temp file
                        fputs(fileStr, tempfp);
                    }

                    if (fileStr[strlen(fileStr) - 1] == '\n')
                    {
                        counter++;
                    }
                    if (feof(fp) != 0)
                    {
                        // End operation at EOF
                        break;
                    }
                }

                fseek(tempfp, 0, SEEK_SET);
                fflush(tempfp);

                freopen(filename, "w", fp); // Reopen target file as blank file

                if (fileStatus(fp) == 1)
                {
                    // Write content from temp file into target file. Contains the inserted string
                    while (fgets(fileStr, bufferSize, tempfp) != NULL)
                    {
                        fputs(fileStr, fp);
                    }
                    fclose(fp);

                    // Special case: Do not create an insert log update in the log file for the log file itself
                    // The updateLog function makes use of the insertLine function
                    if (filename != logFile)
                    {
                        printf("Inserted line at line number %d in '%s'\n", lineNumber, filename);

                        char logFormatStr[logBufferSize];

                        // Update log with line number involved
                        sprintf(logFormatStr, "+ Line inserted at line %d.", lineNumber);

                        updateLog(filename, 0, logFormatStr);
                    }
                }

                fclose(tempfp);
            }
        }
    }
}

/**
 * Inserts changes to files in the current directory into the log file.
 * Keeps track of any changes made to the files.
 * 
 * @param  filename     the name of the file to be updated in the log file.
 * @param  fileDeleted  either a 0 or 1. 0 denotes that the file to be be logged exists.
 *                      1 denotes that the file has been deleted. This happens when the deleteFile
 *                      function has been called.
 * @param  logStr       the string of text which describes the change which occured in the file.
 **/
void updateLog(const char *filename, int fileDeleted, const char *logStr)
{
    if (fileExists(filename) == 0 && fileDeleted == 0)
    {
        printf("Error updating log for file '%s'\n", filename);
    }
    else
    {
        FILE *fp;

        /*
        * Various strings needed in case the file to be logged is in another directory. 
        * A new log file will be created in another directory if an operation is performed 
        * on one of its files from another directory.
        */

        char *dirName = slicePathname(filename, "dirName");   // Directory component of file
        char *fileName = slicePathname(filename, "fileName"); // File name
        strcat(dirName, "/");                                 // Add '/' to the end of dir component
        char *logPath = strcat(dirName, logFile);             // Set logPath to "directoryOfTargetfile/logFile"

        // If the log file already exists, open it for reading and writing
        // Else create a new log file in the directory
        if (fileExists(logPath) == 1)
        {
            fp = fopen(logPath, "r+");
        }
        else
        {
            fp = fopen(logPath, "w+");
        }

        if (fileStatus(fp) == 1)
        {
            int newFileLog = 1; // Is this the first change log for a particular file?
                                // 1: yes, 0: no

            char fileStr[logBufferSize];  // Stores the name of the target file
            char fnameStr[logBufferSize]; // Stores the name of the target file, but in log format

            sprintf(fnameStr, "'%s' log:\n", fileName); // A Log format line is
                                                        // 'FileName' log:\n

            int counter = 1;

            // Scan each line in the log file
            while (fgets(fileStr, logBufferSize, fp) != NULL)
            {
                // Compare each line to the formatted target file name string
                if (strcmp(fileStr, fnameStr) == 0)
                {
                    // If a match is found, an entry for the file already exists
                    counter++;
                    newFileLog = 0;
                    // End scan
                    break;
                }

                if (fileStr[strlen(fileStr) - 1] == '\n' && feof(fp) == 0)
                {
                    counter++;
                }
            }

            /* Time info */

            time_t rawtime;
            struct tm *timeinfo;
            char logTime[50];

            time(&rawtime);
            timeinfo = localtime(&rawtime);

            strftime(logTime, 50, "%H:%M:%S %d/%m/%Y", timeinfo);

            char logFormatStr[logBufferSize]; // Stores the log formatted form of individual file operations
                                              // [4 spaces]+(or -) OPERATION \n\n\n

            // If the operation to be appended was not file deletion, process logStr and obtain number of lines
            if (fileDeleted == 0)
            {
                sprintf(logFormatStr, "%*c%*s Total lines -> %*d%*s", 4, blankSpace, -35, logStr, -5, countLines(fileName), 21, logTime);
            }
            // Else, file does not exist anymore and total lines is 0
            else
            {
                sprintf(logFormatStr, "%*c%*s Total Lines -> 0%*c%*s", 4, blankSpace, -35, logStr, -4, blankSpace, 21, logTime);
            }

            // If entry for a file already exists in the log file,
            if (newFileLog == 0)
            {
                fpos_t pos;

                // Scan each line in the logged operations for the file entry
                while (fgets(fileStr, logBufferSize, fp) != NULL)
                {
                    fgetpos(fp, &pos);         // Store current cursor position
                    char nextChar = fgetc(fp); // Read and store next character
                    fsetpos(fp, &pos);         // Reset cursor position

                    // If the next line is a newline
                    if (fileStr[strlen(fileStr) - 1] == '\n' && feof(fp) == 0)
                    {
                        counter++; // Increment counter
                    }

                    // If the next line is a newline, and the next line is also a newline,
                    // This means that the most recently logged operation for the file has been reached
                    // Insert the new operation to be logged
                    if (fileStr[strlen(fileStr) - 1] == '\n' && feof(fp) == 0 && nextChar == '\n')
                    {
                        insertLine(logPath, counter, logFormatStr);
                        break;
                    }
                }
            }
            // Else if the file entry is new,
            else
            {
                // Add file entry to the log file
                fprintf(fp, "'%s' log:\n", fileName);

                // Add the operation to be logged, in the log format
                fprintf(fp, "%s\n\n\n", logFormatStr);
            }

            fclose(fp);
        }
    }
}

/**
 * Provides the interface for the user to interact with the functions.
 * Makes use of a while loop which runs until the user explicitly ends the program.
 * 
 * @return  0 to denote that the program has ended.
 **/
int userInteraction()
{
    printf("CS132 File Manager -u2015484 Program\n************************************\nType 'help' to view the full list of commands available\n");

    // Run until user quits
    while (1)
    {
        /* Obtain and set the prompt */
        char abscwd[pathNameBufferSize];

        getcwd(abscwd, pathNameBufferSize - 1); // Get the current working directory

        // Find the last occurrence of '/'. Store the return value (remaining string after the last '/')
        // This is the current directory name
        char *cdir = strrchr(abscwd, '/');

        // Print the prompt
        printf("%s > ", cdir); // backsp to write over > which comes after a confirm overwrite message because enter is pressed and newline is inserted so loop is continued, ie funcop is null cond

        char uInput[150];
        char *functionOption;

        fgets(uInput, 150, stdin); // Obtain user input

        // Copy the first substring of the user input separated by a ' ' or \n
        functionOption = strtok(uInput, " \n");

        /**
         * The implementation of strtok() is such that it breaks the users input into specific formats 
         * For example, the first word of the input might be a command name, second might be a file name and so on
         * The code below works with this idea by comparing the user input to a set of options
         */

        if (functionOption == NULL)
        {
            printf("\n");
            continue;
        }
        else
        {
            lowerStr(functionOption); // Convert functionOption to lowercase

            // If the first word is "copy"
            if (strcmp(functionOption, "copy") == 0)
            {
                char *srcFile = strtok(NULL, " \n");  // Store second word
                char *destFile = strtok(NULL, " \n"); // Store third word
                if (srcFile != NULL && destFile != NULL)
                {
                    copyFile(srcFile, destFile); // Perform copy operation
                }
            }
            // If the first word is "create"
            else if (strcmp(functionOption, "create") == 0)
            {
                char *filename = strtok(NULL, " \n"); // Store the second word
                if (filename != NULL)
                {
                    createFile(filename); // Perform create operation
                }
            }
            else if (strcmp(functionOption, "append") == 0)
            {
                char *filename = strtok(NULL, " \n");
                char *appendstr = strtok(NULL, "\n"); // Store contents of the third word onwards until '\n'

                if (filename != NULL && appendstr != NULL)
                {
                    appendLine(filename, appendstr);
                }
            }
            else if (strcmp(functionOption, "insert") == 0)
            {
                char *filename = strtok(NULL, " \n");
                char *lineNumberStr = strtok(NULL, " \n");
                char *insertstr = strtok(NULL, "\n"); // Store contents of the third word onwards until '\n'

                if (filename != NULL && lineNumberStr != NULL && insertstr != NULL)
                {
                    long lineNumber = strtol(lineNumberStr, NULL, 10); // Convert string to number
                    insertLine(filename, lineNumber, insertstr);
                }
            }
            // If the first word is "delete"
            else if (strcmp(functionOption, "delete") == 0)
            {
                char *delType = strtok(NULL, " \n"); // Store the second word

                if (delType != NULL)
                {
                    lowerStr(delType);
                    // If the second word is "lines"
                    if (strcmp(delType, "lines") == 0)
                    {
                        char *startLineStr = strtok(NULL, " -\n"); // Store third word (startline)
                        char *endLineStr = strtok(NULL, " -\n");   // Store fourth word (endLine)
                        char *filename = strtok(NULL, " \n");      // Store fifth word (filename)

                        if (filename != NULL && startLineStr != NULL && endLineStr != NULL)
                        {
                            // Convert strings to numbers
                            long startLine = strtol(startLineStr, NULL, 10);
                            long endLine = strtol(endLineStr, NULL, 10);
                            deleteLineRange(filename, startLine, endLine);
                        }
                    }
                    // Else if the second word is "line"
                    else if (strcmp(delType, "line") == 0)
                    {
                        char *lineNumberStr = strtok(NULL, " \n"); // Store third word (line number)
                        char *filename = strtok(NULL, " \n");      // Store third word (filename)

                        if (filename != NULL && lineNumberStr != NULL)
                        {
                            long lineNumber = strtol(lineNumberStr, NULL, 10); // Convert string to numbers
                            deleteLine(filename, lineNumber);
                        }
                    }
                }
            }
            else if (strcmp(functionOption, "remove") == 0)
            {
                char *filename = strtok(NULL, " \n");

                if (filename != NULL)
                {
                    deleteFile(filename);
                }
            }
            else if (strcmp(functionOption, "clear") == 0)
            {
                char *filename = strtok(NULL, " \n");

                if (filename != NULL)
                {
                    clearFile(filename);
                }
            }
            else if (strcmp(functionOption, "truncate") == 0)
            {
                char *lineNumberStr = strtok(NULL, " \n");
                char *filename = strtok(NULL, " \n");

                if (filename != NULL && lineNumberStr != NULL)
                {
                    long lineNumber = strtol(lineNumberStr, NULL, 10); // Convert string to numbers
                    truncateFile(filename, lineNumber);
                }
            }
            else if (strcmp(functionOption, "show") == 0)
            {
                char *showType = strtok(NULL, " \n");

                if (showType != NULL)
                {
                    lowerStr(showType);
                    if (strcmp(showType, "full") == 0)
                    {
                        char *filename = strtok(NULL, " \n");

                        if (filename != NULL)
                        {
                            showFile(filename);
                        }
                    }
                    else if (strcmp(showType, "line") == 0)
                    {
                        char *lineNumberStr = strtok(NULL, " \n");
                        char *filename = strtok(NULL, " \n");

                        if (filename != NULL && lineNumberStr != NULL)
                        {
                            long lineNumber = strtol(lineNumberStr, NULL, 10); // Convert string to numbers
                            showLine(filename, lineNumber);
                        }
                    }
                    else if (strcmp(showType, "lines") == 0)
                    {
                        char *startLineStr = strtok(NULL, " -\n");
                        char *endLineStr = strtok(NULL, " -\n");
                        char *filename = strtok(NULL, " \n");

                        if (filename != NULL && startLineStr != NULL && endLineStr != NULL)
                        {
                            // Convert string to numbers
                            long startLine = strtol(startLineStr, NULL, 10);
                            long endLine = strtol(endLineStr, NULL, 10);
                            showLineRange(filename, startLine, endLine);
                        }
                    }
                    else if (strcmp(showType, "log") == 0)
                    {
                        char *logType = strtok(NULL, " \n");
                        if (logType != NULL)
                        {
                            lowerStr(logType);
                            if (strcmp(logType, "all") == 0)
                            {
                                showFullLog();
                            }
                            else if(strcmp(logType, "file") == 0)
                            {
                                char *toLog = strtok(NULL, " \n");
                                if(toLog != NULL){
                                    showSingleLog(toLog);
                                }
                            }
                        }
                    }
                }
            }
            else if (strcmp(functionOption, "count") == 0)
            {
                char *linesStr = strtok(NULL, " \n");
                char *filename = strtok(NULL, " \n");

                if (linesStr != NULL && filename != NULL)
                {
                    lowerStr(linesStr);
                    if (strcmp(linesStr, "lines") == 0)
                    {
                        showLineCount(filename);
                    }
                }
            }
            else if (strcmp(functionOption, "mkdir") == 0)
            {
                char *filename = strtok(NULL, " \n");

                if (filename != NULL)
                {
                    makedir(filename);
                }
            }
            else if (strcmp(functionOption, "cd") == 0)
            {
                char *filename = strtok(NULL, " \n");

                if (filename != NULL)
                {
                    changedir(filename);
                }
            }
            else if (strcmp(functionOption, "ls") == 0)
            {
                char *filename = strtok(NULL, " \n");

                if (filename != NULL)
                {
                    listDir(filename);
                }
                else
                {
                    listDir(".");
                }
            }
            else if (strcmp(functionOption, "help") == 0)
            {
                printf("-- Commands --\n");
                printf("1* create FILE\n");
                printf("2* copy SRC DEST\n");
                printf("3* remove FILE\n");
                printf("\n");
                printf("4* show full FILE\n");
                printf("5* show line LINE FILE\n");
                printf("6* show lines START-END FILE\n");
                printf("\n");
                printf("7* show log file FILE\n");
                printf("8* show log all\n");
                printf("\n");
                printf("9* append FILE TEXT\n");
                printf("10* insert FILE LINE TEXT\n");
                printf("\n");
                printf("11* delete line LINE FILE\n");
                printf("12* delete lines START-END FILE\n");
                printf("13* truncate LINE FILE\n");
                printf("14* clear FILE\n");
                printf("\n");
                printf("15* count lines FILE\n");
                printf("\n");
                printf("16* mkdir DIR\n");
                printf("17* cd DIR\n");
                printf("18* ls DIR or ls\n");
                printf("\n");
                printf("19* exit\n");
                printf("-- Commands --\n");
            }
            else if (strcmp(functionOption, "exit") == 0)
            {
                /* EXIT */
                strtok(NULL, " \n");
                break;
            }
        }
    }
    return 0;
}

int main()
{
    userInteraction();
}