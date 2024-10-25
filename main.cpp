#include "main.hpp"
#include "handle.hpp"
#include "aes.hpp"

int main() {
    FileReader file("input/input5.txt");  
    if (!file.readFile()) {  
        std::cerr << "Failed to read the file." << std::endl;
        return 1;  
    }

    file.print();  

    std::string key = "Key-MaHoaAES-128";

    HandleData handleKey(key);
    std::vector<uint8_t> keyHex = handleKey.getDataHex();
    std::cout << "Key in hex: ";
    for (const auto& key : keyHex) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)key << " ";
    }
    std::cout << std::endl;
    // uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 
    //                  0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    
    FileWriter writer("output/output5.txt"); 

    for (const auto& line : file.getLines()) {
        HandleData handledData(line);  
        std::vector<std::string> chunks = handledData.splitTo16ByteChunks(line);  

        for (const auto& chunk : chunks) {
            std::cout << "Processing chunk: " << chunk << " (Length: " << (int)chunk.size() << " bytes)" << std::endl;
            std::vector<uint8_t> blocks = handledData.convertTo128BitBlock(chunk); 
            
            std::cout << "128-bit block in hex: ";
            for (const auto& block : blocks) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)block << " ";
            }
            std::cout << std::endl;

            AES aes; 
            aes.setData(blocks.data());
            std::cout << "Data: " << std::endl;
            aes.printData();
            aes.setKey(keyHex.data());
            // std::cout << "Key: " << std::endl;
            // aes.printKey();
            // std::cout << std::endl;
            aes.encrypt();
            std::cout << "Encrypted data: " << std::endl;
            aes.printData();
            std::cout << std::endl; 
            writer.writeFile(aes.getData());
        }
        std::cout << std::endl;  
    }

    return 0;  // End program
}
