#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "GrepHead.h"

int main(int argc, char** argv)
{
	FILE* file;

	char fileName[128] = {' '};
	char line[256] = {' '};
	char fileText[512][256] = {{' '}};
	char findWord[128] = {' '};

	int line_index = 0;
	int show_N_lines = 0;
	int showA = 0;
	int showB = 0;
	int option_val = 0;

	int A = 0;
	int B = 0;
	int c = 0;
	
	if(argc >= 2)
	{	
		memcpy(findWord, argv[1], strlen(argv[1]) + 1);
		while((option_val = getopt(argc, argv, "cwA:B:f:")) != -1)
		{
			switch(option_val)
			{
				case 'A':
					A = 1;
					if(strcmp(optarg, "0") != 0)
					{
						showA = atoi(optarg);
					}
					break;

				case 'B':
					B = 1;
					if(strcmp(optarg, "0") != 0)
					{
						showB = atoi(optarg);
					}
					break;

				case 'c':
					c = 1;
					break;

				case 'f':
					memcpy(fileName, optarg, strlen(optarg) + 1);
					break;
			}
		}
		B = (A == 1) ? 0 : B;
		show_N_lines = (A == 1) ? showA : showB;

		if((file = fopen(fileName, "r")) != NULL)
		{
			while((fgets(line, 256, file) != NULL) && (line_index < 512))
			{
				memcpy(fileText[line_index], line, 256);
				line_index++;
			}
			fclose(file);
		}
		
		else if(stdin != NULL)
		{
			while((fgets(line, 256, stdin) != NULL) && (line_index < 512))
			{
				memcpy(fileText[line_index], line, 256);
				line_index++;
			}
		}
		else
		{
			printf("File or stdin reading error");
			return 1;
		}
		GetResult(findWord, fileText, line_index, c, A, B, show_N_lines);
	}
	else
	{
		printf("To few arguments");
		return 1;
	}


	return 0;
}