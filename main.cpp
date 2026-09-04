#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdint>
#include <fstream>
#include <filesystem>

#include "PEFile.h"

using namespace std;

int main(int argc, char* argv[]) {

	filesystem::path path;

	if (argc < 2) {
		path = "C:\\Windows\\System32\\calc.exe";
	}
	else {
		path = argv[1];
	}

	PEFile pe(path);

	if (!pe.parseHeaders()) {
		return 1;
	}

	return 0;
}
