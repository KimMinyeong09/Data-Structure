#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pat[MAX_SIZE], string[MAX_SIZE];

typedef struct {
    char p;
    int f;
}term;

term fail[MAX_SIZE];

int Length(char *str) {
    return strlen(str);
}

void failure(char *str) {
    int i = 1, check = 0;

    fail[0].f = -1;

    while (i < Length(str)) {
        if (str[check] == str[i]) { 
            fail[i++].f = check++; 
        }
        else if (check > 0) { 
            check = fail[check - 1].f + 1;
        }
        else { 
            fail[i++].f = -1;
        }
    }
    for (i = 0; i < Length(str); i++)
        fail[i].p = str[i];
}

int pmatch(char* string, char* pat)
{
    int i = 0, j = 0;
    int lens = Length(string);
    int lenp = Length(pat);

    while (i < lens && j < lenp)
    {
        if (string[i] == pat[j])
        {   i++;
            j++;
        }
        else if (j == 0) i++;
        else j = fail[j - 1].f + 1;
    }

    return ((j == lenp) ? (i - lenp) : -1);
}

int main() {
    int i;
	FILE* input = fopen("input.txt", "r");

	fscanf(input, "%s", string);
	fscanf(input, "%s", pat);

    printf("input.txt\n");
    printf("<string>\n");
	printf("%s\n", string);
    printf("<pat>\n");
	printf("%s\n", pat);
    printf("\n");

    printf("Failure Function:\n");
    failure(pat);
    printf("%-5c", 'j');
    for (i = 0; i < Length(pat); i++)
        printf(" %3d", i);
    printf("\n");
    printf("%-5s", "pat");
    for (i = 0; i < Length(pat); i++)
        printf(" %3c", fail[i].p);
    printf("\n");
    printf("%-5c", 'f');
    for (i = 0; i < Length(pat); i++)
        printf(" %3d", fail[i].f);
    printf("\n");

    printf("The pattern %s is found at the position %d\n", pat, pmatch(string, pat));

	fclose(input);


	return 0;
}