// Entry point

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) 
#include <wchar.h>
#include <windows.h>
HANDLE hOut = 0;
#endif

#define CLOCKS_PER_TENTH_SEC (CLOCKS_PER_SEC / 10)

void delay(int delay) {
	const clock_t start = clock();
	clock_t now;
	do {
		now = clock();
	} while ((now - start) / CLOCKS_PER_TENTH_SEC <= delay);
}

#if defined(_WIN32)
void display(char *data, int length) {
	int i;
	DWORD written = 0;
	char buffer[3] = "";
	for (i = 0; i < length; i++) {
		if (data[i] == '@') {
			buffer[0] = '\033';
			buffer[1] = '[';
			buffer[2] = '\0';
			WriteConsole(hOut, buffer, 2, &written, 0);
		}
		else {
			buffer[0] = data[i];
			buffer[1] = '\0';
			WriteConsole(hOut, buffer, 1, &written, 0);
		}
	}
	return;
}

#else

void display(char *data, int length)
{
	int i;
	for (i = 0, i < length, i++) {
		if (data[i] == '@') {
			putchar('\033');
			putchar('[');
		}
		else
			putchar(data[i]);
	}
	fflush(stdout);
	return;
}
#endif

int main(void)
{
	int i, j;
	char data1[] = "@2J"
		"@1;40f@5;33m()@m"
		"@2;40f/\\"
		"@3;39f/  \\"
		"@4m@4:38f/    \\@0m"
		"@5;38f/    \\"
		"@6;37f/      \\"
		"@7;36f/        \\"
		"@4m$8;35f/          \\@0m"
		"@9;35f/          \\"
		"@10;34f/            \\"
		"@11;33f/              \\"
		"@4m@12;32f/                \\@0m"
		"@13;40f@7m  @0m"
		"@14;40f@7m  @0m"
		"@15;37f@31;7m        @0m"
		"@16;38f@31;7m      @0m"
		"@17;39f@31;7m    @0m"
		"@24;0f"
		;

	char data2[] =
		"@1;40f@33m()@0m"
		"@4;37f@31m*@0m"
		"@4;44f@33m*0m"
		"@8;34f@34m*@0m"
		"@8;47f@32m*@0m"
		"@12;31f@36m*@0m"
		"@12;50f@33m*0m"
		;

		char data3[] =
		"@1;40f@33m  @0m"
		"@4;37f@31m @0m"
		"@4;44f@33m @0m"
		"@8;34f@34m @0m"
		"@8;47f@32m @0m"
		"@12;31f@36m @0m"
		"@12;50f@35m @0m"
		;

#if defined(_WIN32)
	DWORD dwMode = 0;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hOut == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Unable to get std handle\n");
		return GetLastError();
	}

	if (!GetConsoleMode(hOut, &dwMode)) {
		fprintf(stderr, "Unable to get console mode\n");
		return GetLastError();
	}
	if (!SetConsoleMode(hOut, dwMode | (DWORD)0x0004)) {
		fprintf(stderr, "Unable to set console mode %d\n", GetLastError());
		return GetLastError();
	}
#endif
	display(data1, (int)sizeof(data1));
	display(data2, (int)sizeof(data2));
	putchar('\n');

	for (i = 1; i < 50; i++) {
		if (i & 0x01)
			display(data2, (int)sizeof(data2));
		else
			display(data3, (int)sizeof(data3));
		printf("\033[25;60f");
		fflush(stdout);
		delay(2);
		printf("\033[25;1f");
		putchar('\n');
	}

#if defined(_WIN32)
	SetConsoleMode(hOut, dwMode);
#endif
	return 0;
}
