#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void max_substring(char* str1, char* str2, int m, int n);
char *strrev(char *str);

void main() {
	// char* str1 = "fkfokoabcccccc";
	// char* str2 = "abccccccokojfifeiwh";
	char* str1 = "thisabcabacabcabcabcisatest";
	char* str2 = "testing123testing123abcabacabcabcabc";
	max_substring(str1, str2, strlen(str1), strlen(str2));
}

/* Find and prints the biggest AND most common substring between 2 str1 and str2.
   Code inspired by https://www.geeksforgeeks.org/longest-common-substring/ */
void max_substring(char* str1, char* str2, int m, int n) {
	char biggest[100]; // The biggest/most common substring
	int table[m+1][n+1]; // 2D array to calculate biggest/most common substring
	
	int row, col = 0;
	int biggest_row, biggest_col = 0; // Index of the LAST letter of the biggest substring we've found
	int max_len = 0; // The length of the biggest substring we've found

	/* Populate the table */
	for(row = 0; row <= m; row++) {
		for(col = 0; col <= n; col++) {
			/* Initialize table[1..m][0] and table[0][1..n] to 0 */
			if(row == 0 || col == 0) {
				table[row][col] = 0;
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

	/* Starting at the bottom right of the biggest substring in the table, build biggest substring */
	while(table[biggest_row][biggest_col] != 0) {
		/* Convert the letter to a string, since strcat requires a string */
		char temp[10];
		temp[0] = str1[biggest_row];	
		strcat(biggest, temp);
		
		/* Move to the next letter (top left) in the backwards substring */
		biggest_row--;
		biggest_col--;
	}

	/* Print and reverse the biggest substring */
	printf("%s", strrev(biggest));
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


