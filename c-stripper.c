#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_PATH_LEN 200
#define MAX_NAME_LEN 100
#define MAX_FILE_SIZE 200000
#define BUFFER_SIZE 5000

char in_path[MAX_PATH_LEN] = "./";
char out_path[MAX_PATH_LEN] = "./";
char in_name[MAX_NAME_LEN];
char out_name[MAX_NAME_LEN];
char in_file [MAX_FILE_SIZE];
char buffer_in[BUFFER_SIZE];
char buffer_out[BUFFER_SIZE];

int main(void){
	
/*                   
create a target input and output files using I/O
*/
	int c;
	int i=0,j=0;

	//IO for target file
	printf("\n###   enter the name of the file you want to debug   ###\n");

	while((c=getchar()) != '\n' && c!= EOF &&  i< MAX_NAME_LEN-1){
		in_name[i++] = c;	
	}
	
	//check path length + name doesnt overflow
	if (i<MAX_PATH_LEN - 3){
		strcat(in_path, in_name);
	}

	//print the path
	printf("input path is: %s\n", in_path);


	//IO for new file
	printf("\n###   enter a new name for the new file   ###\n");

	while((c=getchar()) && j < MAX_NAME_LEN - 1) {

		if (j == 0 && i < (MAX_NAME_LEN - 10) && ( c == '\n' || c == EOF)){   // quick return with default name
			while(in_name[j] != '.'){
				out_name[j] = in_name[j];
				j++;
			}
			strcat(out_name, "_stripped.c"); //note -> there currently is no protection against wrong file types or endings
			break;
		} 
		
		if(c != '\n' && c != EOF){
			out_name[j++] = c;
		} else {
			break;
		}	
	}
	
	if(j < (MAX_PATH_LEN-3)){
		strcat(out_path, out_name);
	}

	printf("ouput path is: %s\n", out_path);


/*
begin streaming in a file chunk.
*/
	
	//establish descriptor and check that path is correct
	FILE *fp = fopen(in_path, "r");
	FILE *fp3 = NULL;
	if(!fp){
		perror("no file found at path\n");
		return 1;
	}
	
	int cross_buff_comm = 0;
	int first_write = 0;

	while(fp){

		memset(buffer_out, 0, BUFFER_SIZE);

		int curr = 0 ;
		int scanned = 0;
		int look;

		fgets(buffer_in, BUFFER_SIZE, fp);

		//check for file termination
		if(feof(fp))
			break;

		//scan buffer to remove comments
		while(buffer_in[curr] != '\n'){
			
			//check if there was a comment that persists across buffers
			if(!cross_buff_comm){
				if (buffer_in[curr] != '/' || (buffer_in[curr] == '/' && !(buffer_in[curr+1] == '/' || buffer_in[curr+1] == '*'))){
					buffer_out[scanned++] = buffer_in[curr++];
					continue;
				}
		
				//if not long comment found terminate buffer scan	
				if (buffer_in[curr+1] == '*'){
					look = 2;
				} else {
					 break;
				}

				//lookahead for long comment terminator	
				
				int end_found = 0;

				while(buffer_in[curr + look] != '\n'){
					if ( buffer_in[curr + look] != '*' || (buffer_in[curr + look] == '*' && buffer_in[curr + look + 1] != '/') ){
						look++;
						continue;
					}
					end_found++;
					curr = curr + look + 2;
					break;

				}

				//if end of long comment wasnt found in buffer, set flag break early
				if(!end_found){
					cross_buff_comm = 1;
					break;
				}
			}

			//if we are in a cross buffer comment do this:
			
			else if(cross_buff_comm){
				if (buffer_in[curr] != '*' || (buffer_in[curr] == '*' && buffer_in[curr + 1] != '/')) {
					curr++;
					continue;
				}

				//if we find the end of the long comment
				if(buffer_in[curr] == '*' && buffer_in[curr+1] == '/'){
					curr = curr + 2;
					cross_buff_comm = 0;
				}
		
			}

		}

		//affix endline and temporarily affix null terminator for pinting purposes
		buffer_out[scanned++] = '\n';
		buffer_out[scanned] = '\0';

		//check for line emptyness
		int isEmpty = 1;
		int l = 0;

		while (buffer_out[l] != '\0'){
			if(buffer_out[l] == '\t' || buffer_out[l] == ' ' || buffer_out[l] == '\n') {
				l++;
				continue;		
			}
			isEmpty = 0;
			break;
		}

		//first write creates or overwrites. subsequents writes append. writes only transpire if the buffer isnt empty
		if (!isEmpty){
			if(!first_write){
				FILE *fp2 = fopen(out_path, "w");
				fputs(buffer_out, fp2);
				fclose(fp2);
				fp3 = fopen(out_path, "a");
				first_write = 1;
				continue;
			}

			fputs(buffer_out, fp3);
		}
	}
		
	printf("successfully opened file\n");
	printf("closing file ...\n");

	fclose(fp);
	fclose(fp3);
	
	return 0;

}
