#include "stdafx.h"

size_t SLL = sizeof(LL);
LL primedata[100] = {
	99, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, \
	67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, \
	139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, \
	223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, \
	293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, \
	383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, \
	463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541
};

int Initialize_PrimeTable_in_File(char* filename){
	FILE* file = fopen(filename, "wb");
	fwrite(primedata, SLL, 100, file);
	fclose(file);
	return 0;
}

LL Test_Read_PrimeTable_from_File(char* filename){
	FILE* file = fopen(filename, "rb");
	LL i;
	LL res;
	LL len;
	fread(&len, SLL, 1, file);
	for (i = 0; i < len; i++){
		fread(&res, SLL, 1, file);
		printf("%u\t", res);
	}
	printf("\nlength: %u", len);
	putchar('\n');
	fclose(file);
	return res;
}

LL internal_get_length_of_primelist_from_file_pointer(FILE* fp){
	LL len;
	rewind(fp);
	fread(&len, SLL, 1, fp);
	return len;
}

LL Get_Length_of_PrimeList_from_File(char* filename){
	LL len;
	FILE* file = fopen(filename, "rb");
	len = internal_get_length_of_primelist_from_file_pointer(file);
	fclose(file);
	return len;
}

LL internal_get_last_prime_from_file_pointer(FILE* fp){
	LL res;
	LL len;
	rewind(fp);
	fread(&len, SLL, 1, fp);
	fseek(fp, len*SLL, SEEK_SET);
	fread(&res, SLL, 1, fp);
	return res;
}

LL Get_Last_Prime_from_File(char* filename){
	LL res;
	FILE* file = fopen(filename, "rb");
	res = internal_get_last_prime_from_file_pointer(file);
	fclose(file);
	return res;
}

LL internal_append_prime_to_file_pointer(FILE* fp, LL prime){
	LL len;
	rewind(fp);
	fread(&len, SLL, 1, fp);
	rewind(fp);
	len++;
	fwrite(&len, SLL, 1, fp);
	fflush(fp);
	fseek(fp, 0, SEEK_END);
	fwrite(&prime, SLL, 1, fp);
	fflush(fp);
	return len;
}

LL Append_prime_to_File(char* filename, LL prime){
	LL len;
	FILE* file = fopen(filename, "rb+");
	len = internal_append_prime_to_file_pointer(file, prime);
	fclose(file);
	return len;
}

LL internal_get_nth_prime_from_file_pointer(FILE* fp, LL index){
	LL res;
	fseek(fp, (index + 1)*SLL, SEEK_SET);
	fread(&res, SLL, 1, fp);
	return res;
}

LL Get_nth_Prime_from_File(char* filename, LL index){
	LL res;
	FILE* file = fopen(filename, "rb");
	LL len = internal_get_length_of_primelist_from_file_pointer(file);
	if (index < len){
		res = internal_get_nth_prime_from_file_pointer(file, index);
	}
	else{
		res = 1;
	}
	fclose(file);
	return res;
}

int Refresh_PrimeTable_in_File(char* filename, LL target_index, LL &min){
	FILE* file = fopen(filename, "rb+");
	LL i;
	LL j;
	LL p;
	LL q;
	LL len = internal_get_length_of_primelist_from_file_pointer(file);
	LL len_buffer = len < MAX_LEN_PRIME_BUFFER ? len : MAX_LEN_PRIME_BUFFER;
	if (len_buffer + len>target_index){
		len_buffer = 2 * (target_index - len);
	}
	LL max = min + 2 * len_buffer;
	double sqrt_max = sqrt((double)max);
	char* buffer = new char[len_buffer];
	memset(buffer, 1, len_buffer);
	for (i = 0; i < len; i++){
		fread(&p, SLL, 1, file);
		if (p >= sqrt_max){
			break;
		}
		j = min / p / 2;
		j += j;
		j++;
		if (j < p){
			j = p;
		}
		q = j*p;
		if (q < min){
			q += (p + p);
		}
		j = (q - min) / 2;
		while (j < len_buffer){
			buffer[j] = 0;
			j += p;
		}
	}
	for (i = 0; i < len_buffer; i++){
		if (buffer[i]){
			internal_append_prime_to_file_pointer(file, min + i + i);
		}
	}
	min = max;
	delete buffer;
	fclose(file);
	return 0;
}


int Initialize_PrimeTable_in_Memory(LL* memory,LL len){
	memset(memory, 0, SLL*len);
	memcpy(memory, primedata, len < 100 ? SLL*len : SLL * 100);
	return 0;
}

int Refresh_PrimeTable_in_Memory(LL* memory, LL mem_len, LL &min){
	//PrimeQ[11000010011]=True
	LL i;
	LL j;
	LL p;
	LL q;
	LL len = memory[0];
	LL len_buffer = len < MAX_LEN_PRIME_BUFFER ? len : MAX_LEN_PRIME_BUFFER;
	if (len_buffer + len>mem_len){
		len_buffer = 2 * (mem_len - len);
	}
	LL max = min + 2 * len_buffer;
	double sqrt_max = sqrt((double)max);
	char* buffer = new char[len_buffer];
	memset(buffer, 1, len_buffer);
	for (i = 1; i <= len; i++){
		p = memory[i];
		if (p >= sqrt_max){
			break;
		}
		j = min / p / 2;
		j += j;
		j++;
		if (j < p){
			j = p;
		}
		q = j*p;
		if (q < min){
			q += (p + p);
		}
		j = (q - min) / 2;
		while (j < len_buffer){
			buffer[j] = 0;
			j += p;
		}
	}
	for (i = 0; i < len_buffer; i++){
		if (buffer[i]){
			memory[(++memory[0])] = min + i + i;
			if (memory[0] == mem_len - 1){
				break;
			}
		}
	}
	min = max;
	delete buffer;
	return 0;
}
