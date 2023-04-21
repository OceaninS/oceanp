#include <iostream>

int printString(char* string) {
	for (size_t index = 0; string[index] != '\0'; index++) {
		std::cout << string[index];
	}
	std::cout << std::endl;
	return 0;
}