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

	dosHeader_ = reinterpret_cast<IMAGE_DOS_HEADER*>(data_.data()); // .data() is effectively the address of the DOS header, reinterpret cast just casts that address as if its pointing to an IMAGE_DOS_HEADER structure (which it is)
	// Most of the DOS header is not needed, the first two bytes are MZ / 0x5A4D (e_magic), and at +0x3C, is a four byte offset to the PE header (IMAGE_NT_HEADERS64)
	if(dosHeader_->e_magic != 0x5A4D) {
		std::cerr << "Invalid e_magic " << std::endl;
	}
	else {
		print_bytes(&dosHeader_->e_magic, sizeof(dosHeader_->e_magic));
	}

	ntHeaders_ = reinterpret_cast<IMAGE_NT_HEADERS64*>(data_.data() + dosHeader_->e_lfanew);
	print_bytes(&ntHeaders_->Signature, sizeof(ntHeaders_->Signature));










}

std::size_t PEFile::fileSize() const { return this->size_; }

bool PEFile::parseHeaders() { return true; }



void PEFile::print_bytes(const void* data, std::size_t size) {

	const auto* bytes = static_cast<const unsigned char*>(data);


	for (size_t i = 0; i < size; ++i) {
		std::printf("%02X ", bytes[i]);
	}
	std::printf("\n");
}
