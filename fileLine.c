#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024

int main() {

    FILE *file = fopen("file.txt", "r");

    if (file == NULL) {

        printf("Error opening file.\n");
        return 1;
    }
    char **lines; //<<-- lines will point to the array of pointer to chars

    lines = malloc(sizeof(char *) *
                   MORE_LINES); //<<-- allocate space for MORE_LINES amount of pointers to char elements initially

    size_t totalLines = 0;
    size_t totalChar = 0; //<<-- used to keep track of the current num. of chars read on the current line.

    char c; //<<-- used to store each char read from the file.

    // Do-Loop will read each char from the file until  the end of the file or reach an error
    do {
        c = fgetc(file); //<<-- read the next char from the file, store it into c var.

        if (ferror(file)) { //<<-- if an error occurs reading from file: exits mess&status.

            printf("Error reading from file.\n");
            return 1;
        }

        //stop reading if we reach the end of the file
        if (feof(file)) {

            //totalChar is not equal zero a line is being reading. If the last line of the file does not end with a new line
            if (totalChar != 0) {

                //we use realloc to re-allocate the block of memory for the string to be exactly large enough to store it
                //plus one extra for the null terminator that ends a string.
                lines[totalLines] = realloc(lines[totalLines], totalChar + 1);

                lines[totalLines][totalChar] = '\0'; //<<-- end the string by placing null terminators at the end

                totalLines++; //<<-- increment totalLines to acknowledge we have read another line from the file
            }

            break; //<<-- stop the loop and stop the reading of the file.
        }
        if (totalChar == 0) {

            lines[totalLines] = malloc(MORE_CHARS);
            lines[totalLines][totalChar] = c;
            totalChar++; //<<-- increment totalChars as we have just read in another char
        }
        if (c == '\n') {

            lines[totalLines] = realloc(lines[totalLines], totalChar + 1);
            lines[totalLines][totalChar] = '\0';
            totalLines++;
            totalChar = 0;

            if (totalLines % MORE_LINES == 0) {
                size_t newSize = totalLines + MORE_LINES;
                lines = realloc(lines, sizeof(char *) * newSize);
            }
        }
            // If the character is not a newline character, we haven't reached the end of the line, and we check
            // if we have reached the size of the current array of chars. The same as the above,
            // because we increase the size of the array of chars by MORE_CHARS each time, whenever
            // total_chars is set to a multiple of MORE_CHARS we know we have reached the size of the current char array.
        else if (totalChar % MORE_CHARS == 0) {

            // We increase the size of the array by MORE_CHARS and use realloc to reallocate space for this larger block of memory.
            //      //
            size_t newSize = totalChar + MORE_CHARS;
            lines[totalLines] = realloc(lines[totalLines], newSize);
        }

    } while (true);

    // At this point we know exactly how many lines we have read from the file and can re-allocate the block of memory
    // for the array of pointers to chars to be exactly the size required.
    lines = realloc(lines, sizeof(char *) * totalLines);

    //Output each stringline in the array of strings.
    for (size_t i = 0; i < totalLines; i++)
        printf("%s", lines[i]);

    for (size_t i = 0; i < totalLines; i++) //<<-- free the block of memory allocated for each string
        free(lines[i]);

    free(lines); //<<-- free the block of memory allocated for the array of pointers to chars
    fclose(file);

    printf("Hello, World!\n");
    return 0;
}
