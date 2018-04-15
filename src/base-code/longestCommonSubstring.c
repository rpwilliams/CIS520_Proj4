#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_max_substring(char* str1, char* str2, int m, int n);
void print_max_substring(char* biggest);


void main() {
	char* str1 = "3abcde";
	char* str2 = "aaabc";
	printf(get_max_substring(str1, str2, strlen(str1), strlen(str2)), "%s\n");
}

char* get_max_substring(char* str1, char* str2, int m, int n) {
	char *biggest = malloc(m + n + 1);
	
	strcat(biggest, "aaaaaaaa");
	strcat(biggest, "bbbb"); 
	
	return biggest;
} 

void print_max_substring(char* biggest) {

}


