#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_GRADE 100 // Define the maximum grade

void operate(FILE *f);

int main(int argc, char **argv) {
    FILE *f;
    int ret;

    // Check for correct command line arguments
    if( argc == 1 || !strcmp("-",argv[1]) ) { 
        f = stdin; // Read from standard input
    }
    else if(argc == 2) {
        f = fopen(argv[1], "r"); 
    }
    else {
        fprintf(stderr, "Too much arguments"); // Print error message for too many arguments
        return 1; // Exit with failure status
    }

    if(!f) {
        fprintf(stderr, "File not found:\"%s\"\n", argv[1]); // Print error message for file not found
        return 1; // Exit with failure status
    }

    operate(f); 
    // Close the file if it is not standard input
    if(f != stdin){
        ret = fclose(f);
        if(ret){
            printf("Error: file failed to close"); // Print error message if file failed to close
            f = NULL;
            return 1; // Exit with failure status
        }
    }
}

void operate(FILE *f) { 
    int max = 0; 
    int ret_val;
    int grade;
    int line_n = 1; 

    while(1) {
        ret_val = fscanf(f, "%d", &grade); // Read a grade from the file
        if(ret_val == EOF) { 
            break;
        }
        else if(ret_val != 1) { // If not a number, print error and exit
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        }
        else if(grade > MAX_GRADE || grade < 0) { // If illegal grade, print error and continue to next line
            fprintf(stderr, "Error: not a legal grade\nLine number:%d\n"
            , line_n);
            continue;
        }
        
        max = max < grade ? grade : max; // Update max grade if necessary
        line_n++; 
    }
    fprintf(stdout,"%d\n", max); // Print the max grade to standard output
}
