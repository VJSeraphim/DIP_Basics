#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
	FILE* fp;
	unsigned char** input, ** output;
	int i, j;
	double val = 0;

	//Memory alloc
	input = (unsigned char**)malloc(sizeof(unsigned char*) * 1024);
	output = (unsigned char**)malloc(sizeof(unsigned char*) * 1024);
	for (i = 0; i < 1024; i++)
	{
		input[i] = (unsigned char*)malloc(sizeof(unsigned char) * 1024);
		output[i] = (unsigned char*)malloc(sizeof(unsigned char) * 1024);
	}

	//File read
	fp = fopen("lena.img", "rb");
	for (i = 0; i < 512; i++)
	{
		fread(input[i], sizeof(unsigned char), 512, fp);
	}
	fclose(fp);

	//Scaling up
	for (i = 0; i < 1024 ; i++)
	{
		for (j = 0; j < 1024; j++)
		{
			val = input[int(i/2)][int(j/2)];

			output[i][j] = val;
		}
	}

	//File write
	fp = fopen("P3.img", "wb");

	for (i = 0; i < 1024; i++)
	{
		fwrite(output[i], sizeof(unsigned char), 1024, fp);
	}
	fclose(fp);

	//Memory free
	for (i = 0; i < 1024; i++)
		free(input[i]);
	free(input);

	for (i = 0; i < 1024; i++)
		free(output[i]);
	free(output);
}