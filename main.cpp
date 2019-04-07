#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#include <bits/stdc++.h>
#include "AES.h"

using namespace std;


unsigned permute_bytes(unsigned i) {
    return (i & 0xff000000) >> 24 | (i & 0x00ff0000) >> 8 | (i & 0x0000ff00) << 8 | (i & 0x000000ff) << 24;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    unsigned key[] = {
            0x2b7e1516,
            0x28aed2a6,
            0xabf71588,
            0x09cf4f3c
    };
    for (unsigned int &i : key) {
        i = permute_bytes(i);
    }
    AES cipher(key, 16);
    for (int i = 0; i < cipher.getRound() + 1; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << "* `" << hex << setw(8) << setfill('0') << permute_bytes(cipher.getKeyExpanded()[i * 4 + j]) << "`"
                 << endl;
        }
    }
    unsigned plain[] = {
            0x3243F6A8,
            0x885A308D,
            0x313198A2,
            0xE0370734
    };
    for (unsigned int &i : plain) {
        i = permute_bytes(i);
    }
    auto *encrypted = static_cast<unsigned int *>(cipher.encrypt(reinterpret_cast<unsigned char *>(plain), 16));
    for (int k = 0; k < 4; ++k) {
        cout << hex << setw(8) << setfill('0') << permute_bytes(encrypted[k]);
    }
    cout << endl;
    auto *decrypted = static_cast<unsigned int *>(cipher.decrypt(reinterpret_cast<unsigned char *>(encrypted), 16));
    for (int k = 0; k < 4; ++k) {
        cout << hex << setw(8) << setfill('0') << permute_bytes(decrypted[k]);
    }
    return 0;
}

#pragma clang diagnostic pop