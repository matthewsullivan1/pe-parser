#include "PEFile.h"
#include <fstream>
#include <iostream>
#include <string>

PEFile::PEFile(const std::filesystem::path& path) {
	if (!std::filesystem::exists(path)) {
		std::cerr << "Path " << path << " does not exist" << std::endl;
		return; 
	}


	std::ifstream file(path, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::cerr << "Failed to open file " << path << std::endl;
		return;
	}

	size_ = file.tellg();
	data_.resize(size_);
	file.seekg(0);

	if (!(file.read(reinterpret_cast<char*>(this->data_.data()), this->size_))) {
		std::cerr << "Failed to read: " << path << std::endl;
		return;
	}

	file.close();


	// Validate DOS first
	if (!validateDos()) { return; }
	const IMAGE_DOS_HEADER* dosHeader;
	


}

std::size_t PEFile::fileSize() const { return size_; }

bool PEFile::parseHeaders() { 


	const IMAGE_DOS_HEADER* dos = dosHeader();
	if (!dos || !validateDos()) {
		return false;
	}

	const IMAGE_NT_HEADERS64* nt = ntHeaders();
	if (!nt || !validateNt()) {
		return false;
	}

	const IMAGE_FILE_HEADER* file = fileHeader();
	if (!file || !validateFileHeader()) { 
		return false; 
	}

	const IMAGE_OPTIONAL_HEADER* optional = optionalHeader();
	if (!optional || !validateOptionalHeader()) {
		return false;
	}





	return true; 
}


void PEFile::print_bytes(const void* data, std::size_t size) {

	const auto* bytes = static_cast<const unsigned char*>(data);


	for (size_t i = 0; i < size; ++i) {
		std::printf("%02X ", bytes[i]);
	}
	std::printf("\n");
}


//*********************************************************************************************************//
// Accessors
//*********************************************************************************************************//
template<typename T> const T* PEFile::view(size_t offset) const {
	// Returns address of (data_.data() + offset) cast to T*
	// Assumes [offset + sizeof(T)] is the base of a valid structure of T and is aligned properly

	if (offset + sizeof(T) > size_) { return nullptr; }

	return reinterpret_cast<const T*>(data_.data() + offset);
}

const IMAGE_DOS_HEADER* PEFile::dosHeader() const {
	return view<const IMAGE_DOS_HEADER>(0);
}

const IMAGE_NT_HEADERS64* PEFile::ntHeaders() const {

	const IMAGE_DOS_HEADER* dos = dosHeader();
	if (!dos) {
		return nullptr;
	}

	return view<const IMAGE_NT_HEADERS64>(dos->e_lfanew);
}

const IMAGE_FILE_HEADER* PEFile::fileHeader() const {
	const IMAGE_NT_HEADERS64* nt = ntHeaders();
	if (!nt) { 
		return nullptr; 
	}

	return &nt->FileHeader;
}

const IMAGE_OPTIONAL_HEADER* PEFile::optionalHeader() const {
	const IMAGE_NT_HEADERS64* nt = ntHeaders();
	if (!nt) {
		return nullptr;
	}

	return &nt->OptionalHeader;
}




//*********************************************************************************************************//
// Validation
//*********************************************************************************************************//

bool PEFile::validateDos() const {
	return (dosHeader()->e_magic == IMAGE_DOS_SIGNATURE);
}

bool PEFile::validateNt() const {
	return (ntHeaders()->Signature == IMAGE_NT_SIGNATURE);
}

bool PEFile::validateFileHeader() const {
	std::cout << "Implement validateFileHeader" << std::endl;
	return true;
}

bool PEFile::validateOptionalHeader() const {
	std::cout << "Implement validateOptionalHeader" << std::endl;
	return true;
}


