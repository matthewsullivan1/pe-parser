#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdint>
#include <fstream>
#include <filesystem>

#include "PEFile.h"

using namespace std;

int main() {
	filesystem::path path = "C:\\Windows\\System32\\calc.exe";
	PEFile pe(path);

	if (!pe.parseHeaders()) {
		return 1;
	}



	return 0;
}
