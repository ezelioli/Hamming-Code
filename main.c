#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>

void color(int color)                  // 0x0 nero, 1 blu, 2 verde, 3 azzurro, 4 rosso, 5 viola, 6 giallo, 7 normale, 8 grigio, 9 blu elettrico, da 10 in poi evidenziature
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);     // trovata su internet

	SetConsoleTextAttribute(hConsole, color);
}

void load1() {  //funzione che simula il caricamento del programma all'apertura
	int r, q;
	color(0x4);
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t    Hamming Code\n\n\t\t\t\t\t           ");
	color(0x6);
	for (r = 1; r <= 15; r++) {
		for (q = 0; q <= 100000000; q++);
		printf("%c", 0xb1);

	}
	color(0x7);
	printf("\n\n");
}

int init(int **word, int *mode) {
	int k = 0, n = 0;
	while (*mode != 1 && *mode != 2 && *mode != 0)
	{
		system("CLS");
		printf("\n\n\n\n\n\n\n\n\n\t\tInert 1 for encode, 2 for decode, 0 to exit: ");
		scanf("%d", mode);
	}
	switch (*mode) {
	case 0:
		return 0;
	case 1:
		printf("\n\n\t\tInsert the word to be encoded (it must end whit -1): ");
		break;
	case 2:
		printf("\n\n\t\tInsert the word to be decoded (it must end whit -1): ");
		break;
	}
	while (1)
	{
		scanf("%d", &k);
		if (k == -1)
			break;
		if (k != 0 && k != 1)
		{
			color(0x4);
			printf("\n\t\tWord not valid!");
			color(0x7);
			*mode = -1;
			_getch();
			return init(word, mode);
		}
		*word = realloc(*word, (n + 1) * sizeof(int));
		(*word)[n++] = k;
	}
	return n;
}

int findR(int n) {
	int R = 0;
	while (pow(2.0, (double)R) - R < n + 1)
		R++;
	return R;
}

int countOnes(int pos, int *word, int m) 
{
	int j = 1, count = 0;
	for (int i = pos + 1; i < m; ++i)
	{
		if (j == pos + 1)
		{
			i += pos;
			j = 0;
			continue;
		}
		if (word[i] == 1)
			count++;
		++j;
	}
	return count;
}

bool isPowerOf2(int i)
{
	int p = 1;
	while (p <= i)
	{
		if (p == i)
			return true;
		p *= 2;
	}
	return false;
}

void encode(int *word, int n)
{
	int R = findR(n);
	int m = n + R;
	int *encodedWord = (int *)malloc(m * sizeof(int));
	for (int i = 0, j = 0; i < m; ++i)
		if (!isPowerOf2(i + 1))
			encodedWord[i] = word[j++];
	for (int i = 0; i < m; ++i)
	{
		if (isPowerOf2(i + 1))
		{
			encodedWord[i] = countOnes(i, encodedWord, m) % 2;
		}
	}

	printf("\n\n\t\tThe encoded word is: ");
	for (int i = 0; i < m; ++i)
	{
		if(isPowerOf2(i + 1))
			color(0x4);
		printf("%d ", encodedWord[i]);
		if(isPowerOf2(i + 1))
			color(0x7);
	}
}

void decode(int *word, int n) {
	int err = 0;
	int k = 0;
	for (int i = 0; i < n; ++i)
	{
		if (isPowerOf2(i + 1))
		{
			if((countOnes(i, word, n) % 2) != word[i])
				err += (int) pow(2.0, (double)k);
			k += 1;
		}
	}
	if (err > 0 && err <= n)
		word[err - 1] = !word[err - 1];
	printf("\n\n\t\tThe original word is: ");
	for (int i = 0; i < n; ++i)
	{
		if (!isPowerOf2(i + 1))
			printf("%d ", word[i]);
	}
	if (err == 0)
	{
		color(0x2);
		printf("\n\n\t\tThe word was actually correct!");
	}
	else
	{
		color(0x4);
		printf("\n\n\t\tError detected and corrected!");
	}
	color(0x7);
}

int main(void) {
	int *word = NULL;
	int mode, n;
	load1();
	while (1) {
		mode = -1;
		n = init(&word, &mode);
		switch (mode) {
		case 0:
			return;
		case 1:
			encode(word, n);
			break;
		case 2:
			decode(word, n);
			break;
		}
		_getch();
	}
	return 0;
}