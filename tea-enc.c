#include <stdint.h>
#include <stdio.h>
#include <string.h>

void encrypt (uint32_t v[2], uint32_t k[4]);

int main(int argc,char **argv) {
	FILE* plain = fopen(argv[1], "r");
	FILE* cipher = fopen("ciphertext.bmp", "w");

	char password[100] = {0};
	strcpy(password, argv[2]);

	if (plain != NULL && cipher != NULL) {
		while (!feof(plain)) {
			unsigned int msg[2];
			msg[0] = msg[1] = 0;

			if (fread(msg, 1, 8, plain) == 0) {
                break;
            }

			encrypt(msg, (unsigned int*)password);
			fwrite(msg, 1, 8, cipher);
		}
	}

	return 0;
}

void encrypt (uint32_t v[2], uint32_t k[4])
{
	uint32_t v0 = v[0], v1 = v[1], sum = 0, i;  
	uint32_t delta = 0x9E3779B9;                     
	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3]; 

	for (i = 0; i < 32; i++) {                       
		sum += delta;
		v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
	}     

	v[0] = v0; 
    v[1] = v1;
}
