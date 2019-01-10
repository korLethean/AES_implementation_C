#include "aes.h"

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
		case 64:
		case 96:
		case 128:
			break;
		default :
			error_code = AES_KEY_LEN_ERR;
			return error_code;
	}

	if(!((ROUND == 10 && KEY_SIZE == 64) || (ROUND == 12 && KEY_SIZE == 96) || (ROUND == 14 && KEY_SIZE == 128)))
	{
		error_code = AES_STD_ERR;
		return error_code;
	}


	if(BLK_SIZE != 64)
	{
		error_code = AES_BLK_LEN_ERR;
		return error_code;
	}

	int round_kyes[ROUND][KEY_SIZE];
	int state[4][4];

	for(int i = 0 ; i < 4 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
			state[j][i] = plaintext[i * 4 + j];
	}

	// TODO: zero round add round key

	for(int i = 0 ; i < ROUND ; i++)
	{
		// TODO: loop substitute -> shift -> mix(except when final round) -> add rk

		// TODO: ciphertext output
	}

	return error_code;
}
