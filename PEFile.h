#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <windows.h>
#include <filesystem>

class PEFile {
public:
	explicit PEFile(const std::filesystem::path& path);

	std::size_t fileSize() const;

	const IMAGE_DOS_HEADER& dosHeader() const; //return reference to DOS header

	void print_bytes(const void* data, std::size_t size);



private:
	std::vector<uint8_t> data_; // .data() set in constructor
	std::size_t size_;			// Set in constructor

	const IMAGE_DOS_HEADER* dosHeader_ = nullptr;
	const IMAGE_NT_HEADERS64* ntHeaders_ = nullptr; 

	bool parseHeaders();
	
};