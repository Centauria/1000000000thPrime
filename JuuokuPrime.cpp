// JuuokuPrime.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, char* argv[])
{
	LL result = 0;
	LL currentTotal;
	LL targetPrimeIndex;
	//time_t t;
	LL m;
	bool use_file = false;
	int i;
	for (i = 0; i < argc; i++){
		if (strcmp(argv[i], "-f") == 0){
			use_file = true;
		}
	}
	char* filename = "test.dat";
	LL* prime = NULL;
	if (use_file){
		Initialize_PrimeTable_in_File(filename);
	}
	else{
		prime = new LL[MAX_LEN];
		Initialize_PrimeTable_in_Memory(prime, MAX_LEN);
	}
	char input[100];
	char* test;
	while (gets(input)){
		if (strcmp(input, "t") == 0){
			if (use_file){
				Test_Read_PrimeTable_from_File(filename);
				continue;
			}
		}
		if (strlen(input) > 9){
			printf("Error\n");
			continue;
		}
		test = input;
		while (*test){
			if (*test<'0' || *test>'9'){
				test = NULL;
				break;
			}
			test++;
		}
		if (test == NULL){
			printf("Error\n");
			continue;
		}
		sscanf(input, "%u", &targetPrimeIndex);
		if (targetPrimeIndex > 100000000){
			printf("Error\n");
			continue;
		}
		if (targetPrimeIndex == 0){
			printf("Error\n");
			continue;
		}
		if (targetPrimeIndex == 1){
			result = 2;
			goto show;
		}
		if (targetPrimeIndex < 100){
			result = primedata[targetPrimeIndex - 1];
			goto show;
		}
		if (use_file){
			m = Get_Last_Prime_from_File(filename) + 2;
			//t = clock();
			while (1){
				currentTotal = Get_Length_of_PrimeList_from_File(filename);
				//printf("progress: %u / %u\r", currentTotal + 1, targetPrimeIndex);
				if (currentTotal >= targetPrimeIndex - 1){
					result = Get_nth_Prime_from_File(filename, targetPrimeIndex - 2);
					//putchar('\n');
					break;
				}
				Refresh_PrimeTable_in_File(filename, targetPrimeIndex, m);
			}
		}
		else{
			m = prime[prime[0]] + 2;
			//t = clock();
			while (1){
				currentTotal = prime[0];
				//printf("progress: %u / %u\r", currentTotal + 1, targetPrimeIndex);
				if (currentTotal >= targetPrimeIndex - 1){
					result = prime[targetPrimeIndex - 1];
					//putchar('\n');
					break;
				}
				Refresh_PrimeTable_in_Memory(prime, targetPrimeIndex, m);
			}
		}
		//printf("%d ms\n", clock() - t);
show:	printf("%u\n", result);
	}
	if (!use_file){
		delete prime;
	}
	return 0;
}

