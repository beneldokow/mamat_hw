#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_GRADE 100

void operate(FILE *f);

int main(int argc, char **argv) {
    FILE *f;
    int ret;

    // Check the number of arguments
    if( argc == 1 || !strcmp("-",argv[1]) ) {
        // If no arguments or the first argument is "-", read from standard input
        f = stdin;
    }
    else if(argc == 2) {
        // If one argument is provided, open the file with that name for reading
        f = fopen(argv[1], "r");
    }
    else {
        // If more than one argument is provided, print an error message and exit
        fprintf(stderr, "Too much arguments");
        return 1;
    }

    // Check if the file could be opened
    if(!f) {
        fprintf(stderr, "File not found:\"%s\"\n", argv[1]);
        return 1;
    }

    operate(f);

    // Close the file if it's not standard input
    if(f != stdin){
        ret = fclose(f);
        if(ret){
            // Print an error message if the file couldn't be closed
            printf("Error: file failed to close");
            f = NULL;
            return 1;
        }
    }
}

void operate(FILE *f) { 
    int grade;
    int ret_val;
    double avg = 0;
    int count = 0;
    int line_n = 1;

    // Read the grades from the file one by one
    while(1) {
        ret_val = fscanf(f, "%d", &grade);
        if(ret_val == EOF) {
            // Stop reading if end-of-file is reached
            break;
        }
        else if(ret_val != 1) {
            // Print an error message if the input is not a number
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        }
        else if(grade > MAX_GRADE || grade < 0) {
            // Print an error message if the grade is out of range and skip
            fprintf(stderr, "Error: not a legal grade\nLine number:%d\n",
            line_n);
            continue;
        }
        // Add the valid grade to the sum and count the number of grades
        avg += grade;
        count++;
        line_n++;
    }
    // Compute and print the mean of the valid grades
    fprintf(stdout,"%.2lf\n", avg/count);
}