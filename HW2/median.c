#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_GRADE 100

void operate(FILE *f);

int main(int argc, char **argv) {
    FILE *f;
    int grades_num = 0;
    int ret;

    // If no arguments or the first argument is "-", read from standard input
    if( argc == 1 || !strcmp("-",argv[1]) ) {
        f = stdin;
    }
    else if(argc == 2) {
        f = fopen(argv[1], "r");
    }
    else {
        fprintf(stderr, "Too much arguments");
        return 1;
    }

    // Check if the input file was successfully opened
    if(!f) {
        fprintf(stderr, "File not found:\"%s\"\n", argv[1]);
        return 1;
    }

    operate(f);

    // Close the input file if necessary
    if(f != stdin){
        ret = fclose(f);
        if(ret){
            printf("Error: file failed to close");
            f = NULL;
            return 1;
        }
    }
}

void operate(FILE *f) { 
    int grade;
    int ret_val;
    int count = 0;
    int line_n = 1;
    int *grades_hist = calloc(MAX_GRADE,sizeof(int));

    // Check if the memory allocation for the grades histogram was successful
    if(grades_hist == NULL){
        fprintf(stderr,"Error: data allocation failed");
        exit(1);
    }

    // Read the grades data from the input source and update the grades histogram
    while(1) {
        ret_val = fscanf(f, "%d", &grade);
        if(ret_val == EOF) {
            break;
        }
        else if(ret_val != 1) {
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        }
        else if(grade > MAX_GRADE || grade < 0) {
            fprintf(stderr, "Error: not a legal grade\nLine number:%d\n",
            line_n);
            continue;
        }
        grades_hist[grade == MAX_GRADE ? grade-1 : grade]++;
        line_n++; count++;
    }

    // get the median grade from the grades histogram
    int sum = 0;
    int median;
    for(int i = 0;i < MAX_GRADE; i++)
    {
        sum+=grades_hist[i];
        if(sum >= (count+1)/2){
            median = i;
            break;
        }
    }

    fprintf(stdout,"%d\n", median);
    free(grades_hist);
}