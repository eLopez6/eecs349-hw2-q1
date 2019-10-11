#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SINGLE_OBJECT 1

int fileContainsString(FILE *file, const char *string) 
{
	char line[strlen(string)];
        
    do {    	
    	if (fgets(line, strlen(string), file) != NULL) {				
			if (strncmp(string, line, (strlen(line))) == 0) {
				return 1;
			}
		}
		else {
			perror("Error reading from file");
		}

	} while(line != NULL);
    
	return -1;
}

int main (void)
{
	const char *filename = "C:\\PE-1.txt";
	const char *contents = "I want to learn the PE file format!";
	
	if (access(filename, F_OK) != -1) {
		FILE *file;
		if ((file = fopen(filename, "r")) != NULL) {
			if (fileContainsString(file, contents) == 1) {
				printf("%s\n", contents);
				fclose(file);
				return 0;
			}
			else {
				fclose(file);
				if ((file = fopen(filename, "a+")) != NULL) {
					fwrite(contents, strlen(contents), SINGLE_OBJECT, file);
					fclose(file);
					return 0;
				}
				else {
					perror("Failed to open the file for appending");
					return -1;
				}
				
				return -1;
			}
		}
		else {
			perror("Failed to open the file for reading.");
			return -1;
		}
	}
	else {
		// file does not exist
		FILE *file;
		if ((file = fopen(filename, "w")) != NULL) {
			fwrite(contents, strlen(contents), SINGLE_OBJECT, file);
			fclose(file);
			return 0;
		}
		else {
			perror("Failed to open the file for writing.");
			return -1;
		}
	}
}
