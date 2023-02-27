/* *******************************************************************************
 *
 * Description: Example of creating our own version of the strcat() function in C
 * found in the string.h library to concatenate two strings.
 *
 * */

#include <stdio.h>
#include <string.h>

char *_strcat(char *destination, const char *source);

int main() {

    char destination[1024] = "Carlos";
    char source[] = " Agudelo";

    _strcat(destination, source);

    printf("Result: %s\n", destination);
    return 0;
}

char *_strcat(char *destination, const char *source) {

    //
    size_t i = 0, j = 0; //<<--we could use int., size_t will allow for larger non-negative positive int. and therefore will support larger strings.

    //checking if the character in the dest. string is the null terminator, once found begin copying the source string
    while (destination[i] != '\0') {
        i++;
    }

    //copy each char from source to dest. until we reach the null terminator.
    while (source[j] != '\0') {
        
        destination[i] = source[j];
        i++;
        j++;
    }

    destination[i] = '\0'; //<<-- insert  the null terminator as the last char stored in destination to terminate it

    //return a pointer to the destination.
    return destination;
}
