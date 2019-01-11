#include "aes.h"

void g(int *w3, int *gw)
{
	gw[0] = w3[1];
	gw[1] = w3[2];
	gw[2] = w3[3];
	gw[3] = w3[0];

	// TODO: substitution

	// TODO: add round constant
}

aes_err key_expansion(const int ROUND, const int KEY_SIZE, int const *zero_round_key, int (*round_keys)[KEY_SIZE])
{
	const int word = KEY_SIZE / 4;
	int w[ROUND][word];
	int gw[word];

	for(int i = 0 ; i < 4 ; i++)
	{
		for(int j = 0 ; j < word ; j++)
			w[i][j] = zero_round_key[i * word + j];
	}

	g(w[3], gw);

	// TODO: w[4] = w[0] ^ gw[3]
	// TODO: w[5] = w[4] ^ w[1]
	// TODO: w[6] = w[5] ^ w[2]
	// TODO: w[7] = w[6] ^ w[3] ... loop

	return AES_SUCCESS;
}

aes_err encryption(const int ROUND, const int KEY_SIZE, const int BLK_SIZE, char *plaintext, char *key, char *ciphertext)
{
	aes_err error_code = AES_SUCCESS;

	switch(ROUND)
	{
		case 10:
		case 12:
		case 14:
			break;
		default :
			error_code = AES_ROUND_ERR;
			return error_code;
	}

	switch(KEY_SIZE)
	{
		case 16:
		case 24:
		case 32:
			break;
		default :
			error_code = AES_KEY_LEN_ERR;
			return error_code;
	}

	if(!((ROUND == 10 && KEY_SIZE == 16) || (ROUND == 12 && KEY_SIZE == 24) || (ROUND == 14 && KEY_SIZE == 32)))
	{
		error_code = AES_STD_ERR;
		return error_code;
	}

	if(BLK_SIZE != 64)
	{
		error_code = AES_BLK_LEN_ERR;
		return error_code;
	}

	int round_keys[ROUND][KEY_SIZE];
	int zero_round_key[KEY_SIZE];
	int state[4][4];

	for(int i = 0 ; i < 4 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
			state[j][i] = plaintext[i * 4 + j];
	}

	for(int i = 0 ; i < KEY_SIZE ; i++)
		zero_round_key[i] = key[i];

	//** for check zero_round_key **//
	/*printf("Zero round key: ");
	for(int i = 0 ; i < KEY_SIZE ; i++)
		printf("%x", zero_round_key[i]);
	printf("\n");*/
	//******************************//

	error_code = key_expansion(ROUND, KEY_SIZE, zero_round_key, round_keys);
	if(error_code != AES_SUCCESS)
		return error_code;

	// TODO: zero round add round key

	for(int i = 0 ; i < ROUND ; i++)
	{
		// TODO: loop substitute -> shift -> mix(except when final round) -> add rk

		// TODO: ciphertext output
	}

	return error_code;
}
