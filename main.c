#include "aes.h"

int main(void)
{
	const int AES128_ROUND = 10;
	const int AES192_ROUND = 12;
	const int AES256_ROUND = 14;
	const int AES128_KEY_SIZE = 64;
	const int AES192_KEY_SIZE = 96;
	const int AES256_KEY_SIZE = 128;
	const int AES_BLOCK_SIZE = 64;	// 128 bits only

	int const *AES_ROUND;
	int const *AES_KEY_SIZE;

	char *key128 = "AABB09182736CCDD";
	char *key192 = "AABB09182736CCDDAABB0918";
	char *key256 = "AABB09182736CCDDAABB09182736CCDD";
	char *key;

	// When change the AES mode, change this variable 0 = 128, 1 = 192, 2 = 256
	const int AES_MODE = 0;

	if(AES_MODE == 0)
	{
		AES_ROUND = &AES128_ROUND;
		AES_KEY_SIZE = &AES128_KEY_SIZE;
		key = key128;
	}
	else if(AES_MODE == 1)
	{
		AES_ROUND = &AES192_ROUND;
		AES_KEY_SIZE = &AES192_KEY_SIZE;
		key = key192;
	}
	else if(AES_MODE == 2)
	{
		AES_ROUND = &AES256_ROUND;
		AES_KEY_SIZE = &AES256_KEY_SIZE;
		key = key256;
	}
	else
	{
		printf("Wrong AES standard");
		return 0;
	}

	char *plaintext= "123456ABCD132536";
	char plaintext_c[AES_BLOCK_SIZE / 4];
	char ciphertext[AES_BLOCK_SIZE];
	char ciphertext_c[AES_BLOCK_SIZE / 4];
	char restoretext[AES_BLOCK_SIZE];
	char restoredtext_c[AES_BLOCK_SIZE / 4];

	int round_key[*AES_ROUND][AES_BLOCK_SIZE];

	aes_err error_code = AES_SUCCESS;

	/** for check plain_text, key **/
	//printf("Plaintext:\t%s\n", plaintext);
	//printf("Key:\t\t%s\n", key);
	/*******************************/

	error_code = encryption(*AES_ROUND, *AES_KEY_SIZE, AES_BLOCK_SIZE, plaintext, key, ciphertext);
	if(error_code == AES_ROUND_ERR)
	{
		printf("AES Encryption error occurred: AES support only 10, 12, 14 rounds \n");
		return 0;
	}
	else if(error_code == AES_KEY_LEN_ERR)
	{
		printf("AES Encryption error occurred: AES support only 128, 192, 256 bits key size \n");
		return 0;
	}
	else if(error_code == AES_BLK_LEN_ERR)
	{
		printf("AES Encryption error occurred: AES block size must be 128 bits \n");
		return 0;
	}
	else if(error_code == AES_STD_ERR)
	{
		printf("AES Encryption error occurred: Wrong matched with key size and rounds \n");
		return 0;
	}

	return 0;
}
