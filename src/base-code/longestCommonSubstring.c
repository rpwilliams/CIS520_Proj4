#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ENTRIES = 50; // Should be higher
#define ENTRY_LINE_SIZE = 2003;

// char wiki_entry[NUM_ENTRIES][ENTRY_LINE_SIZE];
// char wiki_array[ARRAY_SIZE][STRING_SIZE];
// char substrings[ARRAY_SIZE];

void max_substring(char* str1, char* str2, int m, int n);
char *strrev(char *str);
void read_file();

void main() {
	// char* str1 = "fkfokoabcccccc";
	// char* str2 = "abccccccokojfifeiwh";
	// char* str1 = "thisabcabacabcabcabcisatest";
	// char* str2 = "testing123testing123abcabacabcabcabc";
	// max_substring(str1, str2, strlen(str1), strlen(str2));
	read_file();
}

void read_file() {
	FILE *fp;
	char str1[1000];
	char str2[1000];
	// fp = fopen("/homes/dan/625/wiki_dump.txt", "r");
	fp = fopen("test.txt", "r");

	if(fp == NULL) {
		perror("Failed: ");
		return;
	}

	fgets(str1, 1000, fp);
	fgets(str2, 1000, fp);
	max_substring(str1, str2, strlen(str1), strlen(str2));

	fgets(str1, 1000, fp);
	fgets(str2, 1000, fp);
	max_substring(str1, str2, strlen(str1), strlen(str2));
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
void max_substring(char* str1, char* str2, int m, int n) {
	// char temp2[10];
	// char temp3[10];
	// temp2[0] = str1[0];
	// temp3[0] = str2[0];
	// printf("str1[0]: %c\n", temp2[0]);
	// printf("str2[0]: %c\n", temp2[0]);

	char biggest[1000]; // The biggest/most common substring
	memset(biggest, '\0', 100);
	int table[m+1][n+1]; // 2D array to calculate biggest/most common substring
	
	int row, col = 0;
	int biggest_row, biggest_col = 0; // Index of the LAST letter of the biggest substring we've found
	int max_len = 0; // The length of the biggest substring we've found

	/* Populate the table */
	for(row = 0; row <= m; row++) {
		for(col = 0; col <= n; col++) {
			/* Initialize table[1..m][0] and table[0][1..n] to 0 */
			if(row == 0 || col == 0) {
				table[row][col] = 1;
			}
			/* If the letters of the two strings are the same, add 1 to the left diagonal  
			   value and set it to the current position */
			else if(str1[row] == str2[col]) {
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
		return;
	}

	/* Starting at the bottom right of the biggest substring in the table, build biggest substring */
	while(table[biggest_row][biggest_col] != 0) {
		/* Convert the letter to a string, since strcat requires a string */
		char temp[100];
		memset(temp, '\0', 100);
		temp[0] = str1[biggest_row];
		printf("str1[biggest_row]: %c\n", str1[biggest_row]);	
		/* Concatonate the string */
		strcat(biggest, temp);
		
		/* Move to the next letter (top left) in the backwards substring */
		biggest_row--;
		biggest_col--;
	}
	strcat(biggest, "\0");

	/* Print and reverse the biggest substring */
	printf("Max Substring: %s\n", strrev(biggest));
	printf("***************\n");
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


