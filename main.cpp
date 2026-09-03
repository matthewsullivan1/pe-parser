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

	//cout << pe.fileSize() << endl; 



	return 0;
}









/*

	After MS-DOS stub, at file offset 0x3c, is the fill offset to the PE signature
	[base + 0x3c] -> PE signature

	PE signature contains PE\0\0 (four bytes)

*/