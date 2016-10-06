#include "stdafx.h"


#define MAX_LEN_PRIME_BUFFER 1000000000 //1G

typedef unsigned int LL;

extern LL primedata[100];

int Initialize_PrimeTable_in_File(char* filename);

LL Test_Read_PrimeTable_from_File(char* filename);

LL internal_get_length_of_primelist_from_file_pointer(FILE* fp);
LL Get_Length_of_PrimeList_from_File(char* filename);

LL Get_Last_Prime_from_File(char* filename);

LL internal_append_prime_to_file_pointer(FILE* fp, LL prime);
LL Append_prime_to_File(char* filename, LL prime);

LL internal_get_nth_prime_from_file_pointer(FILE* fp, LL index);
LL Get_nth_Prime_from_File(char* filename, LL index);

int Refresh_PrimeTable_in_File(char* filename, LL target_index, LL &min);

int Initialize_PrimeTable_in_Memory(LL* memory, LL len);
int Refresh_PrimeTable_in_Memory(LL* memory, LL len, LL &min);
