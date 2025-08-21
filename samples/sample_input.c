#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//set macros for largest array sizes
#define ARRSIZE 1000

//define function prototypes
/*
function that will be used for line length with call the other two. steps:
	1. get input and store line temporarily.
	2. clean up whitespace and then store the longest line.
	3. copy the longest line into a target location
*/

int get_longest_input(char destination_arr[], int array_size);
void copy_array(char output_arr[], char input_arr[]);

int main(void){
	
	//initialize line array
	char line[ARRSIZE];

	//prompt user:
	printf("\ninput lines:\n");

	//call line sift function
	int max_size = get_longest_input(line, ARRSIZE);
	
	printf("longest line length: %d\n", max_size);
	printf("%s\n", line);
		
	return 0;
}

void copy_array(char oa[], char ia[]){	
	int i=0;
	while((oa[i] = ia[i]) != '\0'){
		i++;
	}
}

int get_longest_input(char out[], int size){
	
	//declare variables
	int c;
	int i=0, max=0, cur_len=0;
	char temp[size];
	char cleaned[size];
	char final[size];

	while((c=getchar()) != EOF && max < size-1){
		if (c != '\n'){
			temp[i] = c;
			i++;
			continue;
		}

		// find end of line and clean up the sentence
		if (c == '\n'){
			int jj = 0;
			for (int j = 0; j<=i; j++){
				if (temp[j] == ' ' && cleaned[jj-1] != ' '){
					cleaned[jj] = temp[j];
					jj++;
				} else if (isalpha(temp[j])){
					cleaned[jj] = temp[j];
					jj++;
				}
			}
			
			//if we start with newline, we just add it back
			cleaned[cur_len = jj] = '\n';
			cur_len++;
		}

		// check if line is longest and store
		if (cur_len > max){
			max = cur_len;
			for(int j = 0; j<cur_len; j++){
				final[j] = cleaned[j];
			}
			final[cur_len] = '\0';
		}

		i = 0;
	}

	//copy the final longest array]
	copy_array(out, final);

	//return length of longest array
	return max;
}
