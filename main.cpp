#include <bits/stdc++.h>
#include "AES.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    unsigned key[] = {
            0x2b7e1516,
            0x28aed2a6,
            0xabf71588,
            0x09cf4f3c
    };
    AES cipher(key, 4);
    for (int i = 0; i < cipher.getRound() + 1; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << hex << setw(8) << setfill('0') << cipher.getKeyExpanded()[i * 4 + j] << endl;
            fflush(stdout);
        }
    }
    /*
     * The key schedule:
     * 2b7e151628aed2a6abf7158809cfcf43
     * 5505626a7dabb0ccd65ca544df936a07
     * 2d7e151650d5a5da8689009e591a6a99
     * 5905626a09d0c7b08f59c72ed643adb7
     * 357e15163caed2a6b3f7158865b4b83f
     * 6905626a55abb0cce65ca54483e81d7b
     * 557e151600d5a5dae689009e65611de5
     * a905626aa9d0c7b04f59c72e2a38dacb
     * ce7e151667aed2a628f7158802cfcf43
     * 8405626ae3abb0cccb5ca544c9936a07
     */
    unsigned plain[] = {
            0x3243F6A8,
            0x885A308D,
            0x313198A2,
            0xE0370734
    };
    auto *encrypted = static_cast<unsigned int *>(cipher.encrypt(reinterpret_cast<unsigned char *>(plain), 16));
    for (int k = 0; k < 4; ++k) {
        cout << hex << setw(8) << setfill('0') << encrypted[k];
    }
    return 0;
}