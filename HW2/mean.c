#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_GRADE 100

void operate(FILE *f);

int main(int argc, char **argv) {
    FILE *f;

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

    if(!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    operate(f);
}

    void operate(FILE *f) { 
        int grade;
        int ret_val;
        double avg = 0;
        int line_n = 0;

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
                fprintf(stderr, "Error: not a legal grade\nLine number:%d", line_n);
                continue;
            }
            avg += grade;
            line_n++;
        }
        fprintf(stdout,"%.2lf\n", avg/line_n);
    }