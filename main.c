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
	#ifdef _WIN32
		mkdir("out");
		mkdir("out/0004013000003502");
	#else
		mkdir("out", 0777);
		mkdir("out/0004013000003502", 0777);
	#endif	
	FILE *file = fopen("out/0004013000003502/code.ips", "wb+");
	char *header = "PATCH";
	fwrite(header, 5, 1, file);
	fputc(00, file);
	fputc(0xA1, file);//addr
	fputc(0x94, file);//addr
	fputc(0x00, file);
	fputc(0xC3, file);//size
	fwrite(&pat, sizeof(pat), 1, file);
	fputc(0x50, file);
	fputc(0x3C, file);
	fputc(0xFF, file);
	fwrite(&pat, sizeof(pat), 1, file);
	char *end = "EOF";
	fwrite(end, 3, 1, file);
	fclose(file);
	return 0;
}