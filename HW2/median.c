#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_GRADE 100

void operate(FILE *f, int grades_num);

int main(int argc, char **argv) {
    FILE *f;
    int grades_num = 0;

    if( argc == 1 || !strcmp("-",argv[1]) ) {
        f = stdin;
    }
    else if(argc == 2) {
        f = fopen(argv[1], "r");
                exit(1);
    }
    else {
        fprintf(stderr, "Too much arguments");
        return 1;
    }

    if(!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    operate(f, grades_num);
}

    void operate(FILE *f, int grades_num) { 
        int grade;
        int ret_val;
        int line_n = 0;
        int *grades_hist = malloc(sizeof(int)*MAX_GRADE);

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
                fprintf(stderr, "Error: not a legal grade\nLine number:%d\n", line_n);
            }
            grades_hist[grade == MAX_GRADE ? grade-1 : grade]++;
            line_n ++;
        }


        for(int i = 0;i < (line_n+1)/2; i+=grades_hist[i])

        fprintf(stdout,"%d\n", i);
    }