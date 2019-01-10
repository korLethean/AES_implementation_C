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

int H2B(char value)
{
	if(value == 'a' || value == 'A')
		return 10;
	else if(value == 'b' || value == 'B')
		return 11;
	else if(value == 'c' || value == 'C')
		return 12;
	else if(value == 'd' || value == 'D')
		return 13;
	else if(value == 'e' || value == 'E')
		return 14;
	else if(value == 'f' || value == 'F')
		return 15;
	else
		return (int) value - 48;
}

void hex_string_to_binary_array(const int len, char *string, int *binary)
{
	int value = 0;

	for(int i = 0 ; i < len ; i++)
	{
		value = H2B(string[i]);
		binary[i * 4] = value / 8;
		value %= 8;
		binary[i * 4 + 1] = value / 4;
		value %= 4;
		binary[i * 4 + 2] = value / 2;
		value %= 2;
		binary[i * 4 + 3] = value;
	}
}

void binary_to_hex_string_array(int *binary, int *string)
{
	char temp[5];

	for(int i = 0 ; i < 16 ; i++)
	{
		sprintf(temp, "%d%d%d%d\0", binary[i * 4], binary[i * 4 + 1], binary[i * 4 + 2], binary[i * 4 + 3]);
		string[i] = strtol(temp, NULL, 2);
	}
}
