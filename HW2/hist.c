#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_N_BINS 10
#define MAX_GRADE 100

void operate(FILE *f, int n_bins);

int main(int argc, char **argv) {
    FILE *f;
    int n_bins = DEFAULT_N_BINS;

    if( argc == 1 || !strcmp("-",argv[1]) ) {
        f = stdin;
    }
    else if(argc == 2) {
        f = fopen(argv[1], "r");
    }
    else if (argc == 3){
        f = fopen(argv[1], "r");
        n_bins = atoi(argv[2]);
    }
    else {
        fprintf(stderr, "Too much arguments");
        return 1;
    }

    if(!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    operate(f, n_bins);
}

    void operate(FILE *f, int n_bins) { 
        int ret_val;
        int grade;
        int line_n = 0;
        int divide_factor = MAX_GRADE/n_bins;
        int *grades_hist = malloc(sizeof(int)*n_bins);
        
        for(int i = 0;i < n_bins;i++){
            grades_hist[i] = 0;
        }

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
            grades_hist[grade == MAX_GRADE ? (grade-1)/divide_factor : (grade)/divide_factor]++;
            line_n++;
        }

        for(int i = 0;i < n_bins;i++){
            fprintf(stdout,"%d-%d\t%d\n", divide_factor*i, (i == n_bins-1) ? divide_factor*(i+1) :
            divide_factor*(i+1)-1, grades_hist[i]);
        }
    }