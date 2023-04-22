#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_GRADE 100

void operate(FILE *f);

int main(int argc, char **argv) {
    FILE *f;
    int ret;

    // If no arguments or the first argument is "-", read from standard input
    if( argc == 1 || !strcmp("-",argv[1]) ) {
        f = stdin;
    }
    else if(argc == 2) {
        // Open the file if a file name is provided
        f = fopen(argv[1], "r");
    }
    else {
        // Print an error message if too many arguments are provided
        fprintf(stderr, "Too much arguments");
        return 1;
    }

    // Print an error message if the file cannot be opened
    if(!f) {
        fprintf(stderr, "File not found:\"%s\"\n", argv[1]);
        return 1;
    }

    operate(f);

    // Close the file if it was opened
    if(f != stdin){
        ret = fclose(f);
        // Print an error message if the file couldn't be closed
        if(ret){
            printf("Error: file failed to close");
            f = NULL;
            return 1;
        }
    }
}

void operate(FILE *f) { 
    int min = MAX_GRADE;
    int ret_val;
    int grade;
    int line_n = 1;

    // Read the grades from the file one by one
    while(1) {
        ret_val = fscanf(f, "%d", &grade);
        if(ret_val == EOF) {
            break;
        }
        else if(ret_val != 1) {
            // Print an error message if a grade cannot be read
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        }
        else if(grade > MAX_GRADE || grade < 0) {
            // Print an error message if an invalid grade is encountered and skip
            fprintf(stderr, "Error: not a legal grade\nLine number:%d\n",
            line_n);
            continue;
        }
        
        // Update the minimum grade if necessary
        min = min > grade ? grade : min;
        line_n++; 
    }

    // Print the minimum grade to standard output
    fprintf(stdout,"%d\n", min);
}