#ifndef READFILE_HPP
#define READFILE_HPP

#include "main.hpp"

// Đọc dữ liệu từ file .txt
class FileReader {
public:
    // Constructor nhận tên file và lưu vào biến fileName
    FileReader(const std::string& file);
    
    // Hàm đọc nội dung file
    bool readFile();
    
    // Hàm in nội dung file
    void print() const;
    
    // Hàm lấy nội dung file dưới dạng std::vector<std::string>
    std::vector<std::string> getLines() const;

private:
    // Tên file
    std::string fileName;
    
    // Lưu từng dòng trong file
    std::vector<std::string> lines;  // Thay đổi kiểu thành std::string
};

/*--------------------------------------------------------------------------------------*/

// Ghi dữ liệu ra file .txt
class FileWriter {
public:
    // Constructor nhận tên file
    FileWriter(const std::string& file);
    
    // Ghi dữ liệu dưới dạng mảng byte vào file
    bool writeFile(uint8_t * data);

private:
    std::string fileName;  // Tên file
};

/*--------------------------------------------------------------------------------------*/


class HandleData {
public:
    HandleData(const std::string& data_input);

    // Chia chuỗi thành các chuỗi 16 byte
    std::vector<std::string> splitTo16ByteChunks(const std::string& string_input) const;
    
    // Chuyển đổi dữ liệu thành 128-bit block
    std::vector<uint8_t> convertTo128BitBlock(const std::string& data_input) const;
    
    // In mảng byte dưới dạng hex
    void printHex() const;

    // Trả về dữ liệu block
    std::vector<uint8_t> getDataHex() const;

private:
    std::vector<uint8_t> dataBlock;  // Mảng lưu trữ dữ liệu 128-bit
};

#endif
