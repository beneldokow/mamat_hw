#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void operate(FILE *f, int grades_num);

int main(int argc, char **argv) {
    FILE *f;
    int grades_num = 0;

    if( argc == 1 || !strcmp("-",argv[1]) ) {
        f = stdin;
    }
    else if(argc == 2) {
        fprintf(stderr, "Error: not enough args\n");
                exit(1);
    }
    else if(argc == 3){
        f = fopen(argv[1], "r");
        grades_num = atoi(argv[2]);
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
        int median_num;
        int line_n = 0;
        int median_grade;

        median_num = (grades_num + 1)/2;

        while(1) {
            ret_val = fscanf(f, "%d-%d\t%d", &median_grade, &grade, &grade);
            if(ret_val == EOF) {
                break;
            }
           /* else if(ret_val != 3) {
                fprintf(stderr, "Error: not a number\n");
                exit(1);
            }*/
            line_n += grade;
            if(line_n >= median_num) {
                break;
            }
        }

        fprintf(stdout,"%d\n", median_grade);
    }