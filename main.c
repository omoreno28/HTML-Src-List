/*
 ============================================================================
 Name        : OMorenoHtmlSrcList.c
 Author      : Orion Moreno
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function declarations
void count(char source[], int size);
void tags(char source[], int size);
void urls(char source[], int size);
void frequencies(char source[], int size);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	//Gets the URL of the HTML document to analyze
	printf("URL:\n");
	char url[BUFSIZ], htmlStr[BUFSIZ], buffer[BUFSIZ], usrInput;
	char curl[BUFSIZ] = "curl -s ";
	int size;
	fgets(url, BUFSIZ, stdin);
	int length = strlen(url) - 1;
	url[length] = '\0';
	strcat(curl, url);
	//Reads the HTML document into a string
	FILE *fp = popen(curl, "r");
	while (!feof(fp)) {
		char temp[BUFSIZ];
		fgets(temp, BUFSIZ, fp);
		strcat(htmlStr, temp);
	}
	size = strlen(htmlStr);
	pclose(fp);

	//Loop for command prompt
	do {
		printf("Ready\n");
		fgets(buffer, BUFSIZ, stdin);
		usrInput = buffer[0];
		switch (usrInput) {
		case 'c':
			count(htmlStr, size);
			break;
		case 't':
			tags(htmlStr, size);
			break;
		case 'u':
			urls(htmlStr, size);
			break;
		case 'f':
			frequencies(htmlStr, size);
			break;
		}
	} while (usrInput != 'q');
	printf("Complete\n");
	return EXIT_SUCCESS;
}

//Function definitions
void count(char source[], int size) {
	char search[BUFSIZ] = "src=\"";
	int count = 0;
	char *pSrc = strstr(source, search);
	while (pSrc != NULL) {
		//Checking for various types of whitespace
		if ((*(pSrc - 1) == ' ') || (*(pSrc - 1) == '\n')
				|| (*(pSrc - 1) == '\t')) {
			count++;
		}
		pSrc++;
		pSrc = strstr(pSrc, search);
	}
	printf("%d\n", count);
}
void tags(char source[], int size) {
	char search[BUFSIZ] = "src=\"";
	char *pSrc = strstr(source, search);
	while (pSrc != NULL) {
		char *tagStart = pSrc;
		char tag[BUFSIZ] = "";
		//Checking for various types of whitespace before src
		if ((*(pSrc - 1) == ' ') || (*(pSrc - 1) == '\n')
				|| (*(pSrc - 1) == '\t')) {
			//Sets tagStart to point to the first occurrence of < after src
			while (*tagStart != '<') {
				tagStart--;
			}
			char *tagEnd = tagStart;
			//Sets tagEnd to the end of the tag
			while ((*tagEnd != ' ') && (*tagEnd != '\n') && (*tagEnd != '\t')
					&& (*tagEnd != '\r') && (*tagEnd != '\f')) {
				tagEnd++;
			}
			tagEnd--;
			strncpy(tag, tagStart + 1, tagEnd - tagStart);
			printf("%s\n", tag);
		}
		pSrc++;
		pSrc = strstr(pSrc, search);
	}
}
void urls(char source[], int size) {
	char search[BUFSIZ] = "src=\"";
	char *pSrc = strstr(source, search);
	while (pSrc != NULL) {
		char url[BUFSIZ] = "";
		char *urlStart = pSrc;
		//Checking for various types of whitespace
		if ((*(pSrc - 1) == ' ') || (*(pSrc - 1) == '\n')
				|| (*(pSrc - 1) == '\t')) {
			//Increments urlStart pointer till it finds the first " character
			while (*urlStart != '\"') {
				urlStart++;
			}
			urlStart++;
			char *urlEnd = urlStart;
			//Increments the urlEnd pointer till it finds the last " character
			while (*urlEnd != '\"') {
				urlEnd++;
			}
			strncpy(url, urlStart, urlEnd - urlStart);
			printf("%s\n", url);
		}
		pSrc++;
		pSrc = strstr(pSrc, search);
	}
}
void frequencies(char source[], int size) {
	//TODO: Same code to get each tag
	//We need to have a character array that holds all the
	//valid tags in the html file (can use concat maybe)
	//Write something similar to the count function, that searches through the
	//string of tags for the count of each unique tag
	//Write something that prints each unique tag, followed by a space, and then
	//the count of occurrences
	char search[BUFSIZ] = "src=\"";
	char *pSrc = strstr(source, search);
	char strTags[BUFSIZ] = "";
	char strTagsToPrint[BUFSIZ] = "";
	while (pSrc != NULL) {
		char *tagStart = pSrc;
		char tag[BUFSIZ] = "";
		//Checking for various types of whitespace before src
		if ((*(pSrc - 1) == ' ') || (*(pSrc - 1) == '\n')
				|| (*(pSrc - 1) == '\t')) {
			//Sets tagStart to point to the first occurrence of < after src
			while (*tagStart != '<') {
				tagStart--;
			}
			char *tagEnd = tagStart;
			//Sets tagEnd to the end of the tag
			while ((*tagEnd != ' ') && (*tagEnd != '\n') && (*tagEnd != '\t')
					&& (*tagEnd != '\r') && (*tagEnd != '\f')) {
				tagEnd++;
			}
			tagEnd--;
			strncpy(tag, tagStart + 1, tagEnd - tagStart);
			tag[strlen(tag)] = '/';
			//String that keeps track of unique tag occurrences
			if (strstr(strTagsToPrint, tag) == NULL) {
				strncat(strTagsToPrint, tag, strlen(tag));
			}
			//We need the strTags string to be complete before we can search for count
			strncat(strTags, tag, strlen(tag));
		}
		pSrc++;
		pSrc = strstr(pSrc, search);
	}
	//Function that prints each unique count, and their frequencies
	char *tagStart = strTagsToPrint;
	char *tagEnd;
	while (*tagStart != '\0') {
		char tagSearch[BUFSIZ] = "";
		//Gives us our unique tag to search for
		tagEnd = tagStart;
		while (*tagEnd != '/') {
			tagEnd++;
		}
		strncpy(tagSearch, tagStart, tagEnd - tagStart);
		//Finds the frequency of this unique tag, and prints
		char *pTag = strstr(strTags, tagSearch);
		int count = 0;
		while(pTag != NULL){
			count++;
			pTag++;
			pTag = strstr(pTag, tagSearch);
		}
		printf("%s\t%d\n", tagSearch, count);
		tagStart = tagEnd + 1;
	}
}
