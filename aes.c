#include "aes.h"

const int S_BOX_TABLE[256] =
	{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
	};

const int INV_S_BOX_TABLE[256] =
	{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,
	};

// 14th value never used
const int ROUND_CONSTANT[14] =
	{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x00};

const int MIX_COLUMN_BYTES[4][4] =
	{{0x02, 0x03, 0x01, 0x01},
	{0x01, 0x02, 0x03, 0x01},
	{0x01, 0x01, 0x02, 0x03},
	{0x03, 0x01, 0x01, 0x02}
	};

const int INV_MIX_COLUMN_BYTES[4][4] =
	{{0x0e, 0x0b, 0x0d, 0x09},
	{0x09, 0x0e, 0x0b, 0x0d},
	{0x0d, 0x09, 0x0e, 0x0b},
	{0x0b, 0x0d, 0x09, 0x0e}
	};

void g(const int WORD, const int ROUND, int *w3, int *gw)
{
	gw[0] = w3[1];
	gw[1] = w3[2];
	gw[2] = w3[3];
	gw[3] = w3[0];

	for(int i = 0 ; i < WORD ; i++)
		gw[i] = S_BOX_TABLE[gw[i]];

	gw[0] ^= ROUND_CONSTANT[ROUND];
}

// TODO: decrytion error fix needed
void xtime(const int bytes, int state, int *temp)
{
	*temp = state;

	if(bytes == 1)
		return;
	else if(bytes == 2)
		*temp <<= 1;
	else if(bytes == 3)
	{
		*temp <<= 1;
		*temp ^= state;
	}

	if(state & 0x80)
		*temp ^= 0x1b;

	*temp &= 0xFF;
}

void copy(int (*state)[4], int *ciphertext)
{
	for(int row = 0 ; row < 4 ; row++)
	{
		for(int col = 0 ; col < 4 ; col++)
			ciphertext[row * 4 + col] = state[col][row];
	}
}

aes_err key_expansion(const int ROUND, const int KEY_SIZE, int const *zero_round_key, int (*round_keys)[KEY_SIZE])
{
	const int word = KEY_SIZE / 4;
	int w[4][word];
	int gw[word];

	if(!((word == 4) || (word == 6) || (word == 8)))
		return AES_KEY_LEN_ERR;

	for(int col = 0 ; col < 4 ; col++)
	{
		for(int row = 0 ; row < word ; row++)
			w[col][row] = zero_round_key[col * word + row];
	}

	g(word, 0, w[3], gw);

	for(int r_col = 0 ; r_col < ROUND ; r_col++)
	{
		for(int w_col = 0 ; w_col < 4 ; w_col++)
		{
			for(int w_row = 0 ; w_row < word ; w_row++)
			{
				if(!w_col)
					round_keys[r_col][w_col * 4 + w_row] = w[0][w_row] ^ gw[w_row];
				else
					round_keys[r_col][w_col * 4 + w_row] = round_keys[r_col][w_col * 4 + w_row - word] ^ w[w_col][w_row];
				w[w_col][w_row] = round_keys[r_col][w_col * word + w_row];
			}
		}

		g(word, r_col + 1, w[3], gw);
	}

	return AES_SUCCESS;
}

aes_err add_round_key(const int KEY_SIZE, int (*state)[4], int *round_key)
{
	int word = KEY_SIZE / 4;

	if(!((word == 4) || (word == 6) || (word == 8)))
		return AES_KEY_LEN_ERR;

	for(int row = 0 ; row < 4 ; row++)
	{
		for(int col = 0 ; col < word ; col++)
			state[col][row] = state[col][row] ^ round_key[row * word + col];
	}

	return AES_SUCCESS;
}

aes_err shift_rows(const int SHIFT, int *state)
{
	if(SHIFT > 3)
		return AES_SHIFT_ERR;

	for(int i = 0 ; i < SHIFT ; i++)
	{
		int temp = state[0];
		for(int j = 0 ; j < 3 ; j++)
			state[j] = state[j + 1];
		state[3] = temp;
	}

	return AES_SUCCESS;
}

aes_err inv_shift_rows(const int SHIFT, int *state)
{
	if(SHIFT > 3)
		return AES_SHIFT_ERR;

	for(int i = 0 ; i < SHIFT ; i++)
	{
		int temp = state[3];
		for(int j = 3 ; j > 0 ; j--)
			state[j] = state[j - 1];
		state[0] = temp;
	}

	return AES_SUCCESS;
}

aes_err mix_columns(int (*state)[4], int const (*TABLE)[4])
{
	int state_origin[4][4];

	for(int col = 0 ; col < 4 ; col++)
	{
		for(int row = 0 ; row < 4 ; row++)
			state_origin[col][row] = state[col][row];
	}

	for(int m_col = 0 ; m_col < 4 ; m_col++)
	{
		for(int s_row = 0 ; s_row < 4 ; s_row++)
		{
			int temp[4];
			for(int m_row = 0 ; m_row < 4 ; m_row++)
				xtime(TABLE[m_col][m_row], state_origin[m_row][s_row], &temp[m_row]);
			state[m_col][s_row] = temp[0] ^ temp[1] ^ temp[2] ^ temp[3];
		}
	}

	return AES_SUCCESS;
}

aes_err encryption(const int ROUND, const int KEY_SIZE, const int BLK_SIZE, char *plaintext, char *key, int *ciphertext)
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

	if(!((BLK_SIZE == 16) || (strlen(plaintext) == BLK_SIZE)))
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

	//** for check state **//
	/*printf("State: ");
	for(int i = 0 ; i < 4 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
			printf("%02x ", state[j][i]);
	}
	printf("\n");*/
	//*********************//

	for(int i = 0 ; i < KEY_SIZE ; i++)
		zero_round_key[i] = key[i];

	error_code = key_expansion(ROUND, KEY_SIZE, zero_round_key, round_keys);
	if(error_code != AES_SUCCESS)
		return error_code;

	//** for check zero_round_key **//
	/*printf("Zero round key: ");
	for(int i = 0 ; i < KEY_SIZE ; i++)
		printf("%02x ", zero_round_key[i]);
	printf("\n");*/
	//******************************//

	//** for check round_key **//
	/*for(int i = 0 ; i < ROUND ; i++)
	{
		printf("Round Key %d: ", i + 1);
		for(int j = 0 ; j < KEY_SIZE ; j++)
			printf("%02x ", round_keys[i][j]);
		printf("\n");
	}*/
	//*************************//

	error_code = add_round_key(KEY_SIZE, state, zero_round_key);
	if(error_code != AES_SUCCESS)
		return error_code;

	//** for check after add round_key **//
	/*printf("after add zero round key: ");
	for(int i = 0 ; i < 4 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
			printf("%02x ", state[j][i]);
	}
	printf("\n");*/
	//***********************************//

	for(int i = 0 ; i < ROUND ; i++)
	{
		for(int row = 0 ; row < 4 ; row++)
		{
			for(int col = 0 ; col < 4 ; col++)
				state[col][row] = S_BOX_TABLE[state[col][row]];
		}

		for(int col = 1 ; col < 4 ; col++)
		{
			error_code = shift_rows(col, state[col]);
			if(error_code != AES_SUCCESS)
				return error_code;
		}

		if(i < ROUND - 1)
		{
			error_code = mix_columns(state, MIX_COLUMN_BYTES);
			if(error_code != AES_SUCCESS)
				return error_code;
		}

		error_code = add_round_key(KEY_SIZE, state, round_keys[i]);

		//** for check round result **//
		/*printf("Round %d:\t", i + 1);
		for(int j = 0 ; j < 4 ; j++)
		{
			for(int k = 0 ; k < 4 ; k++)
				printf("%02x ", state[k][j]);
		}
		printf("\n");*/
		//****************************//
	}

	copy(state, ciphertext);

	return error_code;
}

aes_err decryption(const int ROUND, const int KEY_SIZE, const int BLK_SIZE, int *ciphertext, char *key, int *restoretext)
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

	if(BLK_SIZE != 16)
	{
		error_code = AES_BLK_LEN_ERR;
		return error_code;
	}

	int round_keys[ROUND][KEY_SIZE];
	int zero_round_key[KEY_SIZE];
	int state[4][4];

	int *inv_zero_round_key;
	int *inv_round_keys[ROUND];

	for(int i = 0 ; i < 4 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
			state[j][i] = ciphertext[i * 4 + j];
	}

	//** for check state **//
	/*printf("State: ");
	for(int i = 0 ; i < 4 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
			printf("%02x ", state[j][i]);
	}
	printf("\n");*/
	//*********************//

	for(int i = 0 ; i < KEY_SIZE ; i++)
		zero_round_key[i] = key[i];

	error_code = key_expansion(ROUND, KEY_SIZE, zero_round_key, round_keys);
	if(error_code != AES_SUCCESS)
		return error_code;

	inv_zero_round_key = round_keys[ROUND - 1];
	inv_round_keys[ROUND - 1] = zero_round_key;

	for(int i = 0 ; i < ROUND - 1 ; i++)
		inv_round_keys[i] = round_keys[ROUND - 2 - i];

	//** for check zero_round_key **//
	/*printf("Zero round key: ");
	for(int i = 0 ; i < KEY_SIZE ; i++)
		printf("%02x ", inv_zero_round_key[i]);
	printf("\n");*/
	//******************************//

	//** for check round_key **//
	/*for(int i = 0 ; i < ROUND ; i++)
	{
		printf("Round Key %d: ", i + 1);
		for(int j = 0 ; j < KEY_SIZE ; j++)
			printf("%02x ", inv_round_keys[i][j]);
		printf("\n");
	}*/
	//*************************//

	error_code = add_round_key(KEY_SIZE, state, inv_zero_round_key);
	if(error_code != AES_SUCCESS)
		return error_code;

	for(int i = 0 ; i < ROUND ; i++)
	{
		for(int col = 1 ; col < 4 ; col++)
		{
			error_code = inv_shift_rows(col, state[col]);
			if(error_code != AES_SUCCESS)
				return error_code;
		}

		for(int row = 0 ; row < 4 ; row++)
		{
			for(int col = 0 ; col < 4 ; col++)
				state[col][row] = INV_S_BOX_TABLE[state[col][row]];
		}

		error_code = add_round_key(KEY_SIZE, state, inv_round_keys[i]);
		if(error_code != AES_SUCCESS)
			return error_code;

		if(i < ROUND - 1)
		{
			error_code = mix_columns(state, INV_MIX_COLUMN_BYTES);
			if(error_code != AES_SUCCESS)
				return error_code;
		}

		//** for check round result **//
		/*printf("Round %d:\t", i + 1);
		for(int j = 0 ; j < 4 ; j++)
		{
			for(int k = 0 ; k < 4 ; k++)
				printf("%02x ", state[k][j]);
		}
		printf("\n");*/
		//****************************//
	}

	copy(state, restoretext);

	return error_code;
}
