#include "handle.hpp"
#include <iomanip>
#include <sstream>

/*-------------------------------------------------------------*/
// FileReader Class
FileReader::FileReader(const std::string& file) : fileName(file) {}

bool FileReader::readFile() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return true;
}

void FileReader::print() const {
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
}

// Return the lines read from the file
std::vector<std::string> FileReader::getLines() const {
    return lines;
}

/*-------------------------------------------------------------*/
// FileWriter Class
FileWriter::FileWriter(const std::string& file) : fileName(file) {}

bool FileWriter::writeFile(uint8_t * data) {
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return false;
    } else {
        for (int i = 0; i < 16; i++) {
            file << std::hex << std::setw(2) << std::setfill('0') << (int)data[i] << " ";
        }
        file << std::endl;
    }
    file.close();
}

/*-------------------------------------------------------------*/
// HandleData Class
HandleData::HandleData(const std::string& data_input) {
    dataBlock = convertTo128BitBlock(data_input);
}

std::vector<std::string> HandleData::splitTo16ByteChunks(const std::string& string_input) const {
    std::vector<std::string> chunks;
    size_t length = string_input.size();

    for (size_t i = 0; i < length; i += 16) {
        std::string chunk = string_input.substr(i, 16);
        chunks.push_back(chunk);
    }

    return chunks;
}

std::vector<uint8_t> HandleData::convertTo128BitBlock(const std::string& data_input) const {
    std::vector<uint8_t> block(16, 0);

    for (size_t i = 0; i < data_input.size() && i < 16; ++i) {
        block[i] = static_cast<uint8_t>(data_input[i]);
    }

    return block;
}

void HandleData::printHex() const {
    std::cout << "128-bit block in hex: ";
    for (uint8_t byte : dataBlock) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
    }
    std::cout << std::endl;
}

std::vector<uint8_t> HandleData::getDataHex() const {
    std::vector<uint8_t> hexData;

    for (uint8_t byte : dataBlock) {
        hexData.push_back(byte); 
    }

    return hexData;
}
