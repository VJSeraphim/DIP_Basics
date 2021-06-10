#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
	FILE* fp;
	unsigned char** input, ** output;
	int i, j;
	double val;

	//Memory alloc
	input = (unsigned char**)malloc(sizeof(unsigned char*) * 512);
	output = (unsigned char**)malloc(sizeof(unsigned char*) * 512);
	for (i = 0; i < 512; i++)
	{
		input[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);
		output[i] = (unsigned char*)malloc(sizeof(unsigned char) * 512);
	}

	//File read
	fp = fopen("lena.img", "rb");
	for (i = 0; i < 512; i++)
	{
		fread(input[i], sizeof(unsigned char), 512, fp);
	}
	fclose(fp);

	//High-pass filtering in Horizontal Direction
	for (i = 1; i < 511; i++)
	{
		for (j = 1; j < 511; j++)
		{
			val = (input[i - 1][j - 1] + input[i - 1][j] * 2 + input[i - 1][j + 1] +
				input[i + 1][j - 1] * (-1) + input[i + 1][j] * (-2) + input[i + 1][j + 1] * (-1));
			if (val > 255)
				val = 255;
			if (val < 0)
				val = 0;

			output[i][j] = (unsigned char)val;
		}
	}

	//File write
	fp = fopen("P3.img", "wb");

	for (i = 0; i < 512; i++)
	{
		fwrite(output[i], sizeof(unsigned char), 512, fp);
	}
	fclose(fp);

	//Memory free
	for (i = 0; i < 512; i++)
		free(input[i]);
	free(input);

	for (i = 0; i < 512; i++)
		free(output[i]);
	free(output);
}