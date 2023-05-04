#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_N_BINS 10
#define MAX_GRADE 100

static FILE* f;
static int n_bins = DEFAULT_N_BINS;

void operate(FILE *f, int n_bins);

int main(int argc, char **argv) {
    f = stdin;

    // Parse command line arguments
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i],"-")){
            f = stdin;
        }
        else if(!strcmp(argv[i],"-n_bins")){
             if(i < argc - 1){
                char *check_file = argv[i+1];
                int len = strlen(check_file);
                if((len < 4)||strcmp(check_file+len-4,".txt") != 0){
                    n_bins = atoi(argv[i+1]);
                    i++;
                }
             }
        }
        else{
            f = fopen(argv[i], "r");
            if(!f) {
                fprintf(stderr, "File not found:\"%s\"\n", argv[1]);
                return 1;
            }
        }
    }
   
    int ret;
    operate(f, n_bins);

    if(f != stdin){
        ret = fclose(f);
        if(ret){
            fprintf(stderr, "Error: file failed to close");
            f = NULL;
            return 1;
        }
    }
}

void operate(FILE *f, int n_bins) { 
    int ret_val;
    int grade;
    int line_n = 1;
    int divide_factor = MAX_GRADE/n_bins;
    int *grades_hist = calloc(n_bins,sizeof(int));

    //check if data allocation was succesful
    if(grades_hist == NULL){
        fprintf(stderr,"Error: data allocation failed");
        exit(1);
    }

    // Read input grades and update histogram
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
            fprintf(stderr, "Error: not a legal grade\nLine number:%d\n"
            , line_n);
            continue;
        }
        grades_hist[grade == MAX_GRADE ? (grade-1)/divide_factor :
        (grade)/divide_factor]++;
        line_n++;
    }

    for(int i = 0;i < n_bins;i++){
        fprintf(stdout,"%d-%d\t%d\n", divide_factor*i, (i == n_bins-1) ? 
        divide_factor*(i+1) : divide_factor*(i+1)-1, grades_hist[i]);
    }

    free(grades_hist);
}
