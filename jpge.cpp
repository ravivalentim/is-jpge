#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage " << argv[0] << " ./<file-name>\n";
		return -1;
	}

	char* fileName{ argv[1] };

	std::fstream file{ fileName, std::ios_base::in | std::ios_base::binary };
	if (!file.is_open()) {
		std::perror("fopen");
		std::cerr << "Sorry, could open the file (" << fileName << ")\n";
		return -1;
	}

	const unsigned int MAGIC_NUM_BYTES{ 3 };
	char magicNumbers[MAGIC_NUM_BYTES]{ 0 };
	char expectedMagicNumbers[MAGIC_NUM_BYTES]{ 0xFF, 0xD8, 0xFF };

	if (!file.read(&magicNumbers[0], MAGIC_NUM_BYTES)) {
		std::cerr << "Couldn't read the first 3 bytes\n";
		return -1;
	}

	std::cout << "Magic numbers are: ";
	for (int i = 0; i < MAGIC_NUM_BYTES; i++)
		std::cout << std::hex << "0x" << (int)magicNumbers[i] << ' ';
	std::cout << '\n';

	if (!memcmp(magicNumbers, expectedMagicNumbers, MAGIC_NUM_BYTES))
		std::cout << "Yes, it's a JPGE file\n";
	else
		std::cout << "No, it's not a JPGE file\n";

	return 0;
}