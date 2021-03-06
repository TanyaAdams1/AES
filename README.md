AES-ECB
========
[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu) [![Build Status](https://travis-ci.org/TanyaAdams1/AES.svg?branch=master)](https://travis-ci.org/TanyaAdams1/AES)

This is the C++ implementation of the AES encryption standard, the mode of operation is ECB.

This program is written in response to the homework requirement of the course _Cryptography_.

## Usage
The whole program is written strictly according to the specifications on
[the FIPS Publication 197][FIPS].

[FIPS]: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf

### To use the AES package

To use the package, include the header file

`#include"AES.h"`

and create a cipher by triggering the constructor

`AES cipher(key,length)`

where `key` is the pointer to the address of the first bit of the key, 
and `length` is the length of the key. The signature of the constructor is

`AES(void *key, unsigned length)`

_The length could only be either
16, 24 or 32. Note that all lengths of data in this program is measured by 
the unit "byte"_.

To encrypt a bunch of data, simply use

`auto *encrypted=cipher.encrypt(plain,length)`

where `plain` is the pointer to the first bit of the plaintext and 
`length` is the length of the plaintext. The signature of the function is

`void *encrypt(const void *plain,unsigned length)`

To decrypt, simply use the function `decrypt` instead, the signature is the same as `encrypt`.

### To reproduce the results in the next section

To reproduce the results, you'll have to compile the whole program. The prerequisites are
```
* CMAKE 3.13+
* C++ compiler supporting C++17 standard
```

Navigate to the root directory, and run`cmake .`, then run `make`, and then `./main` (on the Ubuntu OS), you'll see the output.

## The Explanation of the Code

There seems to be nothing much to explain about the code, since nearly every line of code of the AES is written strictly according to the specifications of FIPS. If you feel uncertain about certain parts of the program, it is recommended to refer to the FIPS 197 documents listed above, where everything is explained detailly.

The first thing needs explaining seems to be the implementation of mult, the multiplication on the GF(<img src="https://tex.s2cms.ru/svg/2%5E8" alt="2^8" />). According to the FIPS 197, the 8-bit number multiplication is considered corresponds with the multiplication of polynomials modulo an irreducible polynomial of degree 8. For example, to compute 0x57\*0x83, one do

<img src="https://tex.s2cms.ru/svg/%20%0A%5Cbegin%7Baligned%7D%5Cleft(x%5E%7B6%7D%2Bx%5E%7B4%7D%2Bx%5E%7B2%7D%2Bx%2B1%5Cright)%5Cleft(x%5E%7B7%7D%2Bx%2B1%5Cright)%3D%26%20x%5E%7B13%7D%2Bx%5E%7B11%7D%2Bx%5E%7B9%7D%2Bx%5E%7B8%7D%2Bx%5E%7B7%7D%2B%5C%5C%20%26%20x%5E%7B7%7D%2Bx%5E%7B5%7D%2Bx%5E%7B3%7D%2Bx%5E%7B2%7D%2Bx%2B%5C%5C%20%26%20x%5E%7B6%7D%2Bx%5E%7B4%7D%2Bx%5E%7B2%7D%2Bx%2B1%20%5C%5C%20%26%3Dx%5E%7B13%7D%2Bx%5E%7B11%7D%2Bx%5E%7B9%7D%2Bx%5E%7B8%7D%2Bx%5E%7B6%7D%2Bx%5E%7B5%7D%2Bx%5E%7B3%7D%2B1%20%5Cend%7Baligned%7D%0A%20" alt=" 
\begin{aligned}\left(x^{6}+x^{4}+x^{2}+x+1\right)\left(x^{7}+x+1\right)=&amp; x^{13}+x^{11}+x^{9}+x^{8}+x^{7}+\\ &amp; x^{7}+x^{5}+x^{3}+x^{2}+x+\\ &amp; x^{6}+x^{4}+x^{2}+x+1 \\ &amp;=x^{13}+x^{11}+x^{9}+x^{8}+x^{6}+x^{5}+x^{3}+1 \end{aligned}
 " />
 
 and
 
 <img src="https://tex.s2cms.ru/svg/%20%0A%5Cbegin%7Barray%7D%7Bc%7D%7Bx%5E%7B13%7D%2Bx%5E%7B11%7D%2Bx%5E%7B9%7D%2Bx%5E%7B8%7D%2Bx%5E%7B6%7D%2Bx%5E%7B5%7D%2Bx%5E%7B4%7D%2Bx%5E%7B3%7D%2B1%20%5Coperatorname%7Bmodulo%7D%20%5Cleft(x%5E%7B8%7D%2Bx%5E%7B4%7D%2Bx%5E%7B3%7D%2Bx%2B1%5Cright)%7D%20%5C%5C%20%7B%3D%5Cquad%20x%5E%7B7%7D%2Bx%5E%7B6%7D%2B1%7D%5Cend%7Barray%7D%0A%20" alt=" 
\begin{array}{c}{x^{13}+x^{11}+x^{9}+x^{8}+x^{6}+x^{5}+x^{4}+x^{3}+1 \operatorname{modulo} \left(x^{8}+x^{4}+x^{3}+x+1\right)} \\ {=\quad x^{7}+x^{6}+1}\end{array}
 " />
 
 and therefore 0x57\*0x83=0xc1.
 
 In this program, this multiplication is implemented in the mult function, which calls the mult_x function to do the "shift left and modulo" operation.
 
 The other one needing explanation is the permute_byte function. It has nothing to do with the implementation of AES per se. It is to deal with the small endian nature of the Intel CPU of my computer. The Intel chip stores the lower bits of the number in smaller address. Therefore, if one stores the int 0x01020304 in memory, and would like to disassemble it into 4 chars, they would be 0x04,0x03,0x02,0x01 in an address-increasing order, with is counter-intuitive. Since it is more convenient to write the key and plaintext in the format of int rather than char, I chose to write it as int and use the function to adjust the position of the bytes to avoid such trouble.
 
 As for the "Hello world" output in the beginning, I just didn't want to bother myself by removing the code generated automatically by my IDE.

## Answer to the problem

The code in `main.cpp` is used for calculating the answer for problem 4.4 and 4.5.
### Answer to 4.4: the key schedule
The key schedule for the key `2B7E151628AED2A6ABF7158809CF4F3C` is
* `2b7e1516`
* `28aed2a6`
* `abf71588`
* `09cf4f3c`
* `a0fafe17`
* `88542cb1`
* `23a33939`
* `2a6c7605`
* `f2c295f2`
* `7a96b943`
* `5935807a`
* `7359f67f`
* `3d80477d`
* `4716fe3e`
* `1e237e44`
* `6d7a883b`
* `ef44a541`
* `a8525b7f`
* `b671253b`
* `db0bad00`
* `d4d1c6f8`
* `7c839d87`
* `caf2b8bc`
* `11f915bc`
* `6d88a37a`
* `110b3efd`
* `dbf98641`
* `ca0093fd`
* `4e54f70e`
* `5f5fc9f3`
* `84a64fb2`
* `4ea6dc4f`
* `ead27321`
* `b58dbad2`
* `312bf560`
* `7f8d292f`
* `ac7766f3`
* `19fadc21`
* `28d12941`
* `575c006e`
* `d014f9a8`
* `c9ee2589`
* `e13f0cc8`
* `b6630ca6`

### The encrypted text
The ciphertext for the plaintext `3243F6A8885A308D313198A2E0370734` with the 
key in 4.4 is
`3925841d02dc09fbdc118597196a0b32`

## Approaches to break the AES cipher system
According to the [Wikipedia page](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard), and based on
the results from Google Scholar, no black-box attack to the full AES system is known up till now.

The most promising attack approach seems to be side-channel attack, where the cipher system is no longer treated as a
"black box", but some of its runtime behaviors may be accessed by the adversary.

In [this paper](https://www.ieee-security.org/TC/SP2015/papers-archived/6949a591.pdf), the author presented an approach interesting enough
and has practical significance, which is applied on a virtual machine platform and can break the AES implementation by the widely
used package openssl. The attack is basically a cache attack, where the adversary utilizes the temporal information regarding
cache accessing to gain information about the runtime of the cipher system. Since multiple VMs may share the same cache, this 
attack could be cross-core and cross-VM, which greatly undermines the security of clouds.
