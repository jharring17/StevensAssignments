#include "std392io.h"
#include <time.h>

#define EXEC(x) \
        if (x == -1) output("", 's', strerror(errno));

#define FILESHORT "text"
#define FILELONGG "longtext"

int main(int argc, char const *argv[]) {

    /* For generating random string
        Needs to include <time.h>
     */
    srand(time(NULL));

    int array[5] = {1,2,-9,12,-3};
    char* string = "Hello!";

    /*****************************
     * The following is to check
     * your output() function.
     ***************************** /


    /* Error: NULL destination */
    EXEC(output("", 'd', NULL))
    EXEC(output("", 's', NULL))
    /* Error: unrecognized format */
    EXEC(output("", 'i', string))
    EXEC(output("", 'X', string))
    EXEC(output("", 'S', string))
    EXEC(output("", 'D', string))
    /* Error: both NULL destination AND unrecognized format */
    EXEC(output("", 'S', NULL))
    EXEC(output("", 'D', NULL))


    /* Print integers to stdout */
    for (size_t i = 0; i < 5; i++) {
        EXEC(output("", 'd', &array[i]))
    }

    /* Print string to stdout */
    EXEC(output("", 's', string))

    /* Write integers to a short text file */
    for (size_t i = 0; i < 5; i ++) {
        EXEC(output(FILESHORT, 'd', &array[i]))
    }

    /* Generate a long random string
        and write to a file
     */
    long int longsize = 1 << 8;
    char* newfile = (char*)malloc(longsize);
    for (size_t i = 0; i < longsize; i++) {
        newfile[i] = '0' + rand()%72;
        if (newfile[i] == 'a') {
            newfile[i+1] = '\n';
            i ++;
        }
    }
    EXEC(output(FILELONGG, 's', newfile))
    free(newfile);
    
    EXEC(clean())


    /************************
     * 
     * The following is to 
     * check your input()
     * function.
     * 
     * **********************/

    char newstr[1024] = {0};
    int  num;


    /* Error: File doesn't exist */
    EXEC(input("nofile.txt", 's', newstr))
    EXEC(input("nofile.txt", 'd', &num))
    /* Error: Unrecognized format */
    EXEC(input("", 'S', newstr))
    EXEC(input("", 'X', newstr))
    EXEC(input("", 'D', &num))
    EXEC(input("", 'i', &num))
    /* Error: File doesn't exist AND unrecognized format */
    EXEC(input("nofile.txt", 'S', newstr))
    EXEC(input("nofile.txt", 'X', newstr))
    EXEC(input("nofile.txt", 'D', &num))
    EXEC(input("nofile.txt", 'i', &num))    


    /* Receive a string from stdin */
    EXEC(input("", 's', newstr))
    /* Print out the string to stdout */
    EXEC(output("", 's', newstr))
    /* Receive an integer from stdin */
    EXEC(input("", 'd', &num))
    EXEC(output("", 'd', &num))

    /* Read a file of strings */
    while (!input(FILESHORT, 's', newstr)) {
        output("", 's', "Line: ");
        output("", 's', newstr);
    }

    /* Read a file of strings */
    while (!input(FILELONGG, 's', newstr)) {
        output("", 's', "Line: ");
        output("", 's', newstr);
    }

    /* Read a file of integers */
    while (!input(FILESHORT, 'd', &num)) {
        output("", 's', "Number: ");
        output("", 'd', &num);
    }

    /* Nothing should happen */
    EXEC(input(FILESHORT, 's', NULL))
    EXEC(input(FILESHORT, 'd', NULL))


    EXEC(clean())
    
    return 0;
}
