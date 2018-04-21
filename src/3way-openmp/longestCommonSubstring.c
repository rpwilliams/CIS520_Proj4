#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_ENTRIES 100 // Should be 1000000
#define ENTRY_LINE_SIZE 2003
#define NUM_THREADS 4
#define LINE_LENGTH 1000 //should be 2003, increasing to this size causes a segmentation fualt due to size of table.
char entries[NUM_ENTRIES][LINE_LENGTH];

// char wiki_entry[NUM_ENTRIES][ENTRY_LINE_SIZE];
// char wiki_array[ARRAY_SIZE][STRING_SIZE];
// char substrings[ARRAY_SIZE];


void max_substring(int myID);
char *strrev(char *str);
void read_file();


void main() {
	// char* str1 = "fkfokoabcccccc";
	// char* str2 = "abccccccokojfifeiwh";
	// char* str1 = "thisabcabacabcabcabcisatest";
	// char* str2 = "testing123testing123abcabacabcabcabc";
	// max_substring(str1, str2, strlen(str1), strlen(str2));
	read_file();
	
	int i;
	for(i = 0; i < NUM_THREADS; i++){
		max_substring(i);
	}
	
}

void read_file() {
	FILE *fp;
	char str1[LINE_LENGTH];
	fp = fopen("/homes/dan/625/wiki_dump.txt", "r");
	//fp = fopen("test.txt", "r");

	if(fp == NULL) {
		perror("Failed: ");
		return;
	}
	
	int i = 0;
	while(fgets(str1, LINE_LENGTH, fp) != NULL && i < NUM_ENTRIES){
		strcpy(entries[i], str1);
		i++;
	}

	// while(fgets(str1, 1000, fp) != NULL) {
	// 	printf("Str1: %s\nStr2: %s\n ", str1, str2);
	// 	max_substring(str1, str2, strlen(str1), strlen(str2));
	// }
	// while(fgets(line, WIKI_STRING_SIZE, fp) != NULL) {
	// 	// printf("Str1: %s\nStr2: %s\n ", str1, str2);
	// 	// max_substring(str1, str2, strlen(str1), strlen(str2));
	// }

	fclose(fp);
}

/* Find and prints the biggest AND most common substring between 2 str1 and str2.
   Code inspired by https://www.geeksforgeeks.org/longest-common-substring/ */
void max_substring(int myID) {
	// char temp2[10];
	// char temp3[10];
	// temp2[0] = str1[0];
	// temp3[0] = str2[0];
	// printf("str1[0]: %c\n", temp2[0]);
	// printf("str2[0]: %c\n", temp2[0]);
	
	int startPos = myID * (NUM_ENTRIES / NUM_THREADS);
	int endPos = startPos + (NUM_ENTRIES / NUM_THREADS);
	//int startPos = 0;
	//int endPos = NUM_ENTRIES;
	
	char str1[LINE_LENGTH];
	char str2[LINE_LENGTH];
	int m, n, i;
	char biggest[LINE_LENGTH]; // The biggest/most common substring
	char temp[LINE_LENGTH];
	
	int row, col;
	int biggest_row, biggest_col; // Index of the LAST letter of the biggest substring we've found
	int max_len; // The length of the biggest substring we've found
	int table[LINE_LENGTH+1][LINE_LENGTH+1]; // 2D array to calculate biggest/most common substring

	
	 #pragma omp for private(str1,str2,startPos,endPos,m,n,i,biggest,temp,row,col,biggest_row,biggest_col,table) 
	for(i = startPos; i < endPos && i < NUM_ENTRIES - 1; i++)
	{
		strcpy(str1, entries[i]);
		strcpy(str2, entries[i+1]);
		
		m = strlen(str1);
		n = strlen(str2);
		
		int table[m+1][n+1]; // 2D array to calculate biggest/most common substring
		max_len = 0;
		row =  0; 
		col = 0;
		biggest_row = 0;
		biggest_col = 0;
		
		/* Populate the table */
		for(row = 0; row < m; row++) {
			for(col = 0; col < n; col++) {
				/* Initialize table[1..m][0] and table[0][1..n] to 1 */
				if(row == 0 || col == 0) {
					table[row][col] = 1;
				}
				/* If the letters of the two strings are the same, add 1 to the left diagonal  
				   value and set it to the current position */
				else if(str1[row] == str2[col] && str1[row] != '\n'){
					table[row][col] = table[row-1][col-1] + 1;
					
					/* If the current position is bigger than the biggest substring
					   we've found so far, update our variables so that we can find
					   it later on. */
					if(table[row][col] > max_len) {
						max_len = table[row][col];
						biggest_row = row;
						biggest_col = col;
					}
				}
				/* If the letters are not the same, the substring length is 0 */
				else {
					table[row][col] = 0;				
				}
			}
		}

		if(max_len == 0) {
			printf("No common substring.");
		}
		else{
			memset(biggest, '\0', LINE_LENGTH);
			/* Starting at the bottom right of the biggest substring in the table, build biggest substring */
			while(table[biggest_row][biggest_col] != 0) {
				/* Convert the letter to a string, since strcat requires a string */				
				memset(temp, '\0', LINE_LENGTH);
				
				temp[0] = str1[biggest_row];
				//printf("str1[%d]: %c\n", biggest_row, str1[biggest_row]);	
				/* Concatonate the string */
				strcat(biggest, temp);
				
				/* Move to the next letter (top left) in the backwards substring */
				biggest_row--;
				biggest_col--;
			}
			strcat(biggest, "\0");

			/* Print and reverse the biggest substring */
			printf("%d-%d:, %s\n", i, i+1, strrev(biggest));
			printf("***************\n");
		}
	}
} 

/* Reverse a string
   From https://stackoverflow.com/questions/8534274/is-the-strrev-function-not-available-in-linux */
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}


