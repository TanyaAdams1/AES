#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
//
// Created by bill on 19-3-31.
//

#include <cstring>
#include "AES.h"

const unsigned char S[16][16] = {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
        0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
        0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
        0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
        0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
        0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
        0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
        0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
        0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
        0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
        0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
        0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
        0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
        0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
        0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
        0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
        0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const unsigned char inv_S[16][16] = {
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
        0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
        0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
        0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
        0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
        0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
        0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
        0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
        0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
        0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
        0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
        0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
        0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
        0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
        0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
        0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
        0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,};

unsigned char mult_x(unsigned a) {
    a &= 0xff;
    a <<= 1;
    if (a & 0x100)
        a ^= 0x11b;
    return a;
}

unsigned char mult(unsigned a, unsigned b) {
    unsigned res = 0;
    while (b != 0) {
        if (b & 1)
            res ^= a;
        b >>= 1;
        a = mult_x(a);
    }
    return res;
}

void mix_columns(unsigned char (*s)[4]) {
    unsigned char t[4];
    for (int c = 0; c < 4; c++) {
        for (int j = 0; j < 4; j++) {
            t[j] = s[j][c];
        }
        s[0][c] = mult(0x02, t[0]) ^ mult(0x03, t[1]) ^ t[2] ^ t[3];
        s[1][c] = t[0] ^ mult(0x02, t[1]) ^ mult(0x03, t[2]) ^ t[3];
        s[2][c] = t[0] ^ t[1] ^ mult(0x02, t[2]) ^ mult(0x03, t[3]);
        s[3][c] = mult(0x03, t[0]) ^ t[1] ^ t[2] ^ mult(0x02, t[3]);
    }
}

void add_round_key(unsigned char(*s)[4], unsigned char *key) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; ++j) {
            s[3 - j][i] ^= key[i * 4 + j];
        }
}

void shift_rows(unsigned char (*state)[4]) {
    unsigned char _state[4][4];
    memcpy(_state, state, 16 * sizeof(unsigned char));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = _state[i][(j + i) % 4];
        }
    }
}

void sub_bytes(unsigned char (*state)[4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            unsigned char tmp = state[i][j];
            state[i][j] = S[tmp / 16][tmp % 16];
        }
    }
}

unsigned sub_word(unsigned i) {
    auto *temp = new unsigned char[4];
    memcpy(temp, &i, sizeof(i));
    for (int j = 0; j < 4; ++j) {
        temp[j] = S[temp[j] / 16][temp[j] % 16];
    }
    unsigned ans = 0;
    memcpy(&ans, temp, sizeof(ans));
    delete[] temp;
    return ans;
}

unsigned rot_word(unsigned i) {
    auto *temp = new unsigned char[4];
    memcpy(temp, &i, sizeof(i));
    for (int j = 0; j < 4; ++j) {
        temp[j] = ((unsigned char *) (&i))[(j + 3) % 4];
    }
    unsigned ans = 0;
    memcpy(&ans, temp, sizeof(ans));
    delete[] temp;
    return ans;
}

unsigned rcon(unsigned i) {
    unsigned temp = 0x01;
    for (int j = 0; j < i - 1; ++j) {
        temp = mult_x(temp);
    }
    return temp << 24;
}

void *AES::expand_key() {
    unsigned len;
    if (round == 10)
        len = 16;
    else if (round == 12)
        len = 24;
    else
        len = 32;
    unsigned temp, *expanded = new unsigned[4 * (round + 1)];
    unsigned Nk = len / 4, i = 0;
    memcpy(expanded, key, 4 * Nk * sizeof(unsigned char));
    i = Nk;
    while (i < 4 * (round + 1)) {
        temp = expanded[i - 1];
        if (i % Nk == 0) {
            temp = sub_word(rot_word(temp)) ^ rcon(i / Nk);
        } else if (Nk > 6 && i % Nk == 4) {
            temp = sub_word(temp);
        }
        expanded[i] = expanded[i - Nk] ^ temp;
        i++;
    }
    return expanded;
}

void *AES::decrypt_block(unsigned char *cipher) {

    return nullptr;
}

void *AES::encrypt_block(unsigned char *plain) {
    unsigned char state[4][4];
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
            state[3 - i][j] = plain[j * 4 + i];
        }
    }
    add_round_key(state, reinterpret_cast<unsigned char *>(key_expanded));
    for (int i = 0; i < round - 1; ++i) {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, reinterpret_cast<unsigned char *>(key_expanded + 4 * (i + 1)));
    }
    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, reinterpret_cast<unsigned char *>(key_expanded + 4 * round));
    auto *cipher = new unsigned char[16];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cipher[j * 4 + i] = state[i][j];
        }
    }
    return cipher;
}

void *AES::decrypt(unsigned char *cipher, unsigned length) {
    return nullptr;
}

void *AES::encrypt(unsigned char *plain, unsigned length) {
    auto *cipher = new unsigned char[length + 16 - (length % 16)];
    for (int i = 0; i < length / 16 + 1; ++i) {
        void *cipher_block = encrypt_block(plain + i * 16);
        memcpy(cipher + i * 16, cipher_block, 16 * sizeof(unsigned char));
    }
    return cipher;
}

int AES::getRound() const {
    return round;
}

unsigned int *AES::getKey() const {
    return key;
}

unsigned int *AES::getKeyExpanded() const {
    return key_expanded;
}

#pragma clang diagnostic pop