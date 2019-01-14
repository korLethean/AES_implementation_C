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
#define AES_SHIFT_ERR	0x05

const int S_BOX_TABLE[256];

const int ROUND_CONSTANT[14];

void g(const int WORD, const int ROUND, int *w3, int *gw);

aes_err key_expansion(const int ROUND, const int KEY_SIZE, int const *zero_round_key, int (*round_keys)[KEY_SIZE]);

aes_err add_round_key(const int KEY_SIZE, int (*state)[4], int *round_key);

aes_err shift_rows(const int SHIFT, int *state);

//TODO: parameter needed
aes_err mix_columns();

aes_err encryption(const int ROUND, const int KEY_SIZE, const int BLK_SIZE, char *plaintext, char *key, char *ciphertext);

//TODO: parameter needed
aes_err decryption();

#endif /* AES_H_ */
