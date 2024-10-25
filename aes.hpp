#ifndef AES_HPP
#define AES_HPP

#include "main.hpp"

class AES {
public:
    AES(); 
    AES(uint8_t *); 

    void print(uint8_t);
    void print(uint8_t *);
    void printLine(uint8_t *);
    void printBox(uint8_t *);

    void printData();
    void printKey();
    void printRoundKey(int);

    void generateRoundKeys();
    void initRoundKeys();

    void runEncryptionRound();

    void encrypt();
    void verboseEncrypt();
    void verboseEncryptNoReset();

    uint8_t * getData();

    void setData(uint8_t *);
    void setKey(uint8_t *);
    void setRoundKey(int, uint8_t *);
    void setRound(int);

    void keyAdd();
    void subBytes();
    void shiftRows();
    void mixColumns();

    uint8_t sBox(uint8_t);
    uint8_t Rcon(uint8_t);

private:
    int round;
    uint8_t data[16]; 
    uint8_t key[16];   
    std::vector<std::vector<uint8_t>> roundKey;  

    const uint16_t reduce = 0b100011011;
    const uint16_t mag = 0b100000000;
};

#endif
