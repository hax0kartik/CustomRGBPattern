
/* The MIT License

   Copyright (c) 2011 by Attractive Chaos <attractor@live.co.uk>

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

// This file implements an improved algorithm of Guenter Stertenbrink's suexco.c
// (http://magictour.free.fr/suexco.txt).

#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#define addr 0x10A194
#define addr2 0x10A1F8

typedef struct{
	uint8_t r[32];
	uint8_t g[32];
	uint8_t b[32];
}led;

int main()
{
	uint32_t rgb = 0;
	printf("Type in the hex rgb and press Enter:\n");
	scanf("%X", &rgb);
	FILE *file = fopen("patch.s", "wb+");
	fprintf(file, ".arm.little\n\n.open \"code.bin\", \"out/0004013000003502/code.bin\", 0x100000\n\n.thumb\n.org 0x%X\n\n", addr);
	led pat;
	memset(&pat.r[0], 0, 32); 
	memset(&pat.g[0], 0, 32); 
	memset(&pat.b[0], 0, 32); 
	int i = 1;
	do
	{
		memset(&pat.r[i], (rgb >> 16) & 0xFF, 5); 
		memset(&pat.g[i], (rgb >> 8) & 0xFF, 5); 
		memset(&pat.b[i], (rgb >> 0) & 0xFF, 5);
		i+=10;
	}	
	while(i!=31);
	pat.r[30] = (rgb >> 16) & 0xFF;
	pat.g[30] = (rgb >> 8) & 0xFF;
	pat.b[30] = (rgb >> 0) & 0xFF;
	
	/*
	for(int i = 1; i != 32; i++)
	{
		pat.r[i] = 0xFF - round;
		if(i <  16)
		round -= 17;
		else
		round += 17;	
	} 
	*/
	
	
	fprintf(file, "patch:\n");
	fprintf(file, "//pat red\n");
	for(int i = 0; i!=32; i+=1)
		fprintf(file, "		dcb 0x%X\n", pat.r[i]);
	fprintf(file, "//pat green\n");
	for(int i = 0; i!=32; i+=1)
		fprintf(file, "		dcb 0x%X\n", pat.g[i]);
	fprintf(file, "//pat blue\n");
	for(int i = 0; i!=32; i+=1)
		fprintf(file, "		dcb 0x%X\n", pat.b[i]);
	fprintf(file, "\n.org 0x%X\n", addr2);
	fprintf(file, "patch1:\n");
	fprintf(file, "//pat red\n");
	for(int i = 0; i!=32; i+=1)
		fprintf(file, "		dcb 0x%X\n", pat.r[i]);
	fprintf(file, "//pat green\n");
	for(int i = 0; i!=32; i+=1)
		fprintf(file, "		dcb 0x%X\n", pat.g[i]);
	fprintf(file, "//pat blue\n");
	for(int i = 0; i!=32; i+=1)
		fprintf(file, "		dcb 0x%X\n", pat.b[i]);
	fprintf(file, ".close");
	fclose(file);
	mkdir("out");
	mkdir("out/0004013000003502");
	system("armips.exe patch.s");
	return 0;
}