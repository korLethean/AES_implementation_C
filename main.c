#include "aes.h"

int main(void)
{
	const int AES_ROUND = 10;	// 10, 12, 14
	const int AES_KEY_SIZE = 64;	// 128, 192, 256 bits
	const int AES_BLOCK_SIZE = 64;	// 128 bits only

	int plaintext[AES_BLOCK_SIZE];
	int plaintext_c[AES_BLOCK_SIZE / 4];
	int ciphertext[AES_BLOCK_SIZE];
	int ciphertext_c[AES_BLOCK_SIZE / 4];
	int restoretext[AES_BLOCK_SIZE];
	int restoredtext_c[AES_BLOCK_SIZE / 4];

	int key[AES_KEY_SIZE];
	int round_key[AES_ROUND][AES_BLOCK_SIZE];

	aes_err error_code = AES_SUCCESS;

	hex_string_to_binary_array(AES_BLOCK_SIZE / 4, "123456ABCD132536", plaintext);
	hex_string_to_binary_array(AES_KEY_SIZE / 4, "AABB09182736CCDDAABB09182736CCDD", key);

	/** for check plain_text, key **/
	/*printf("Plaintext:\t");
	for(int i = 0 ; i < AES_BLOCK_SIZE ; i++)
		printf("%d", plaintext[i]);
	printf("\nKey:\t\t");
	for(int i = 0 ; i < AES_KEY_SIZE ; i++)
		printf("%d", key[i]);
	printf("\n");*/
	/*******************************/

	error_code = encryption(AES_ROUND, AES_KEY_SIZE, AES_BLOCK_SIZE, plaintext, key, ciphertext);
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

	return 0;
}
