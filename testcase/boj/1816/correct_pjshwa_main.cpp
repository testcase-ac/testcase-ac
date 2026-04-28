#include <cstdio>

const int MAX_SIZE = 1000001;

int main(){
	char numberboard[MAX_SIZE] = {0};
	long long int *primeslist = new long long int[100000];
	int primeindex = 0;
	for(int i = 2; i < MAX_SIZE; i++){
		if(numberboard[i] == 0) primeslist[primeindex++] = (long long int)i;
		for(int j = i; j < MAX_SIZE; j += i) numberboard[j] = 1;
	}
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		long long int key;
		scanf("%lld", &key);
		bool isAppropriatePass = true;

		for(int j = 0; j < primeindex; j++){
			if(key % primeslist[j] == 0LL){
				isAppropriatePass = false;
				break;
			}
		}
		printf("%s\n", isAppropriatePass?"YES":"NO");
	}
	

}