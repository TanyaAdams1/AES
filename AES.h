//
// Created by bill on 19-3-31.
//

#ifndef AES_AES_H
#define AES_AES_H


class AES {
public:
    explicit AES(void *key, int len) {
        this->key = static_cast<unsigned int *>(key);
        switch (len) {
            case 16:
                round = 10;
                break;
            case 24:
                round = 12;
                break;
            case 32:
                round = 14;
                break;
            default:
                break;
        }
        key_expanded = static_cast<unsigned int *>(expand_key());
    }

    void *decrypt(const void *cipher, unsigned int length);

    int getRound() const;

    unsigned int *getKey() const;

    unsigned int *getKeyExpanded() const;

    void *encrypt(const void *plain, unsigned int length);

private:
    int round{};
    unsigned *key, *key_expanded;

    void *expand_key();

    void *encrypt_block(const unsigned char *plain);

    void *decrypt_block(const unsigned char *cipher);
};


#endif //AES_AES_H
