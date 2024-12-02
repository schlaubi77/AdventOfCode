#include <stdio.h>
#include <inttypes.h>

#define LINE_COUNT 1000

uint64_t parseLine(char* line) {
	uint32_t firstNumber = 0;
	uint32_t secondNumber = 0;
	char finishedFirst = 0;

	for (size_t i = 0; line[i] != '\r' && line[i] != '\n'; i++) {
		char c = line[i];
		if (c == ' ') {
			finishedFirst = 1;
		}
		else if (finishedFirst) {
			secondNumber = secondNumber * 10 + c - '0';
		}
		else {
			firstNumber = firstNumber * 10 + c - '0';
		}
	}
	return ((uint64_t)firstNumber << 32) + secondNumber;
}

void sort(uint32_t* array, size_t length) {
	for (size_t i = 1; i < length; i++) {
		for (size_t j = i; j > 0 && array[j - 1] > array[j]; j--) {
			uint32_t tmp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = tmp;
		}
	}
}

int main() {
	FILE* file;
	file = fopen("input.txt", "r");

	char line[100];

	uint32_t firstNumbers[LINE_COUNT];
	uint32_t secondNumbers[LINE_COUNT];

	for (size_t i = 0; i < LINE_COUNT; i++) {
		fgets(line, 100, file);
		uint64_t parsed = parseLine(line);
		firstNumbers[i] = (uint32_t)(parsed >> 32);
		secondNumbers[i] = (uint32_t)(parsed & 0xFFFFFFFF);
	}
	sort(firstNumbers, LINE_COUNT);
	sort(secondNumbers, LINE_COUNT);

	uint32_t sum = 0;

	for (size_t i = 0; i < LINE_COUNT; i++) {
		for (size_t j = 0; j < LINE_COUNT; j++) {
			if (firstNumbers[i] == secondNumbers[j]) {
				sum += firstNumbers[i];
			}
		}
	}
	printf("Result: %d\n", sum);
}