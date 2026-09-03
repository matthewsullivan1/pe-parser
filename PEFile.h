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
	template<typename T> const T* view(std::size_t offset) const;
	const IMAGE_DOS_HEADER* dosHeader() const; //return pointer to DOS header
	const IMAGE_NT_HEADERS64* ntHeaders() const; // return pointer to NT headers
	const IMAGE_FILE_HEADER* fileHeader() const; // return pointer to File header (pointed to by NT header)
	const IMAGE_OPTIONAL_HEADER* optionalHeader() const; // return pointer to Optional header (pointer to by NT header)
	bool parseHeaders();

	void print_bytes(const void* data, std::size_t size);

private:
	std::vector<uint8_t> data_;
	std::size_t size_;			

	
	bool validateDos() const; // validate DOS header (e_magic)
	bool validateNt() const; // validate NT headers (signature)
	bool validateFileHeader() const;
	bool validateOptionalHeader() const;
	
};