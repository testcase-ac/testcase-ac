#include <cstdio>
#include <cmath>

int main(){
	int m, n;
	scanf("%d%d", &m, &n);

	char sieve[n+1];

	for(auto &x : sieve){
		x = 1;
	}

	int root_of_n = (int)sqrt(n);

	// 0 and 1 are not primes

	sieve[0] = 0;
	sieve[1] = 0;

	for(int i = 2; i <= root_of_n; i++){
		if(sieve[i]){
			int idx = 2;
			while(idx * i < n+1){
				sieve[idx*i] = 0;
				idx++;
			}
		}
	}

	for(int i = m; i < n+1; i++){
		if(sieve[i]) printf("%d\n", i);
	}

	return 0;
}