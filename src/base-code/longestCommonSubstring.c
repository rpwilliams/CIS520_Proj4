#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void max_substring(char* str1, char* str2, int m, int n);
void print_max_substring(char* biggest, int start);


void main() {
	char* str1 = "3abcde";
	char* str2 = "aaabc";
	max_substring(str1, str2, strlen(str1), strlen(str2));
	// printf(max_substring(str1, str2, strlen(str1), strlen(str2)), "%s\n");
}

/* Returns the biggest of a and b */
int max(int a, int b) {
	if(a >= b) {
		return a;
	}
	return b;
}

void max_substring(char* str1, char* str2, int m, int n) {
	/* Allocate space for the biggest substring */
	int MAX_SUBSTRING_SIZE = max(m, n) + 1;
	char biggest[1000];
	int table[m+1][n+1];
	
	int longest_i = 0;
	int longest_j = 0;
	int i, j = 0;
	int len = 0;
	/* Populate the table */
	for(i = 0; i <= m; i++) {
		for(j = 0; j <= n; j++) {
			/* If the letters are the same, add 1 to the left diagonal  
			   value and set it to the current position */
			if(str1[i] == str2[j]) {
				table[i][j] = table[i-1][j-1] + 1;
				
				if(max(table[i][j], table[longest_i][longest_j]) == table[i][j]) {
					len = table[i][j] + 1;
					longest_i = i;
					longest_j = j;
				}
			}
			/* If the letters are not the same, the substring length is 0 */
			else {
				table[i][j] = 0;				
			}
		}
	}

	/* Iterate through the table to build biggest substring */
	i = longest_i;
	j = longest_j;
	biggest[len] = '\0';
	len--;
	while(table[i][j] != 0) {
		biggest[len] = str1[i];
		len--;
		i--;
		j--;
	}

	print_max_substring(biggest, len + 1);
	// printf("%s", biggest);

} 

void print_max_substring(char biggest[], int start) {
	int i;
	for(i = start; i < strlen(biggest); i++) {
		printf("%c", biggest[i]);
	}
}


