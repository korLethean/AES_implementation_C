#ifndef AES_H_
#define AES_H_

#if defined(_MSC_VER) && _MSC_VER < 1600
/* Under Visual Studio 2010 */
typedef unsigned int aes_drr;
#else
/* C99 Compatible */
#include <stdint.h>
typedef uint32_t aes_err;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AES_SUCCESS	0x00
#define AES_BLK_LEN_ERR 0x01
#define AES_KEY_LEN_ERR	0x02
#define AES_ROUND_ERR	0x03
#define AES_STD_ERR	0x04

const int S_BOX_TABLE[256];

void g(int *w3, int *gw);

//TODO: parameter needed
aes_err key_expansion(const int ROUND, const int KEY_SIZE, int const *zero_round_key, int (*round_keys)[KEY_SIZE]);

//TODO: parameter needed
aes_err add_round_key();

//TODO: parameter needed
aes_err substitute_bytes();

//TODO: parameter needed
aes_err shift_rows();

//TODO: parameter needed
aes_err mix_columns();

aes_err encryption(const int ROUND, const int KEY_SIZE, const int BLK_SIZE, char *plaintext, char *key, char *ciphertext);

//TODO: parameter needed
aes_err decryption();

int H2B(char value);

void hex_string_to_binary_array(const int len, char *string, int *binary);

void binary_to_hex_string_array(int *binary, int *string);

#endif /* AES_H_ */
