#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
	FILE* fp;
	unsigned char** input, ** output;
	int i, j;
	int new_i, new_j;
	double val = 0;
	double pi = 3.1415926;
	double theta = pi / (180 / 20);

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

	//black background
	for (i = 0; i < 512; i++) {
		for (j = 0; j < 512; j++) {
			output[i][j] = 0;
		}
	}

	//Scaling down and transformation
	for (i = 0; i < 256 ; i++)
	{
		for (j = 0; j < 256; j++)
		{
			new_j = (int)(128 + (i - 128) * sin(-theta) + (j - 128) * cos(theta));
			new_i = (int)(128 + (i - 128) * cos(theta) - (j - 128) * sin(-theta));

			val = input[i*2][j*2];

			output[new_i + 100][new_j + 140] = (unsigned char)val;
		}
	}

	//Image interpolation
	for (i = 1; i < 511; i++) {
		for (j = 1; j < 511; j++) {
			if (output[i][j] == 0 && output[i + 1][j] != 0 && output[i - 1][j] != 0 && output[i][j + 1] != 0 && output[i][j - 1] != 0)
				output[i][j] = 0.25 * (output[i + 1][j] + output[i - 1][j] + output[i][j + 1] + output[i][j - 1]);
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
	for (i = 0; i < 256; i++)
		free(input[i]);
	free(input);

	for (i = 0; i < 256; i++)
		free(output[i]);
	free(output);
}