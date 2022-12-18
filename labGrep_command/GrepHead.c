#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GrepHead.h"

void GetResult(char findWord[128], char fileText[][256], int file_text_size, int A, int B, int c, int show_N_lines)
{
	int appeared = 0;
	int line_appearedId[file_text_size];

	for(int i = 0;i < file_text_size;i++)
	{
		if(strstr(fileText[i], findWord) != NULL)
		{
			line_appearedId[appeared] = i;
			appeared++;
		}
	}

	if(show_N_lines != 0)
	{	
		int start = -1;
		int end = -1;		
		if(A == 1)//print show_N_lines up
		{
			for(int i = 0; i < appeared; i++)
			{	
				int lastId = (i == 0) ? 0 : line_appearedId[i - 1];
				int appearedId = line_appearedId[i];
				end = appearedId;
				start = (appearedId - show_N_lines < 0) ? 0 : appearedId - show_N_lines;
				for(int j = start; j <= end; j++)
				{
					if(j <= lastId)
					{
						continue;
					}
					printf("%s", fileText[j]);
				}
			}
		}
		else if(B == 1)//print show_N_lines down
		{
			for(int i = 0;i < appeared;i++)
			{	
				int appearedId = line_appearedId[i];
				start = appearedId;
				if(line_appearedId[i + 1] <= end)
				{
					continue;
				}
				int shift = (start <= end) ? end - start + 1 : 0;
				end = (appearedId + show_N_lines > file_text_size - 1) ? file_text_size - 1 : appearedId + show_N_lines;
				for(int j = start + shift; j <= end; j++)
				{
					printf("%s", fileText[j]);
				}
			}
		}

	}
	else if(show_N_lines == 0)
	{
		int idx;
		for(int i = 0;i < appeared;i++)
		{
			idx = line_appearedId[i];
			printf("%s", fileText[idx]);
		}
	}
	if(c != 0)
	{
		printf("%s appeared %d times.", findWord, appeared);
	}

}