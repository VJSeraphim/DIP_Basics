#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
	FILE* fp;
	unsigned char** input, ** output;
	int i, j;
	int pixels = 512 * 512;
	unsigned long histogram[256];
	unsigned long hist_sum[256];
	unsigned long sum = 0;
	double scale = 255.0 / pixels;

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

	//histogram , cumulative histogram declaration
	for (i = 0; i < 256; i++) {
		histogram[i] = 0;
	}

	for (i = 0; i < 512; i++) {
		for (j = 0; j < 512; j++) {
			histogram[input[i][j]]++;
		}
	}

	for (i = 0; i < 256; i++) {
		sum += histogram[i];
		hist_sum[i] = (int)((sum * scale) + 0.5);
	}

	for (i = 0; i < 512; i++) {
		for (j = 0; j < 512; j++) {
			output[i][j] = hist_sum[input[i][j]];
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