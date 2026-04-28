#include <cstdio>

int main(){
	long long modular_results[32];
	int binary_digits[32];

	long long a, b, c;
	scanf("%lld%lld%lld", &a, &b, &c);

	int digit = 0;
	while(b != 0){
		binary_digits[digit] = (int)(b % 2);
		b /= 2;
		digit++;
	}

	modular_results[0] = a % c;
	for(int i = 1; i < digit; i++){
		modular_results[i] = (modular_results[i-1] * modular_results[i-1]) % c;
	}

	long long answer = 1;

	for(int i = 0; i < digit; i++){
		if(binary_digits[i]) {
			answer *= modular_results[i];
			answer %= c;
		}
	}

	printf("%lld\n", answer);
}