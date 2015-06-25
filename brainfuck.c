#include <stdio.h>
#define MAX 2048

const char *version = "@@ VSBI - 0.0.1 @@\n";

unsigned char data[MAX] = {0};
unsigned int dp = 0;

int interpret(char *file_name);

int main(int argc, char *argv[])
{
	printf("%s", version);
	if(argc == 1)
		printf("Usage: %s <<FILE_NAME>>\n", argv[0]);
	else
		if(interpret(argv[1]))
			return 1;
	return 0;
}

int interpret(char *file_name)
{
	FILE *file = fopen(file_name, "r");
	char c;
	long start, end;
	
	if(file == NULL)
	{
		fprintf(stderr, "ERROR - Cannot open input file: %s\n", file_name);
		return 1;
	}

	while(c != EOF && dp < MAX-1)
	{
		c = fgetc(file);
		switch(c)
		{
			case '>': dp++; break;
			case '<': dp--; break;
			case '+': data[dp]++; break;
			case '-': data[dp]--; break;
			case '.': putchar(data[dp]); break;
			case ',':
				c = getchar();
				data[dp] = c != EOF ? c : 0;
			break;
			case '[':
				if(!data[dp])
					fseek(file, end, SEEK_SET);
				else
					start = ftell(file);
			break;
			case ']':
				if(data[dp])
					fseek(file, start, SEEK_SET);
				else
					end = ftell(file)+1;
			break;
		}

	}
	fclose(file);
	return 0;
}