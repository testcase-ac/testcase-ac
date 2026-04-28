#include <cstdio>
#include <cmath>
#include <vector>

int main(void){
	long long n;
	scanf("%lld", &n);
	if(n == 2LL) return 0; // floating point exception
	long long sq_n = (long long)sqrt((double)n);
	for(long long i = 2LL; i <= sq_n; i++){
		long long temp = n;
		std::vector<long long> num_vec;
		while(temp != 0LL){
			num_vec.push_back(temp % i);
			temp /= i;
		}
		bool isPalindrome = true;
		long long k = num_vec.size();
		for(long long j = 0LL; j < k / 2; j++){
			if(num_vec[j] != num_vec[k-j-1]){
				isPalindrome = false;
				break;
			}
		}
		if(isPalindrome) printf("%lld\n", i); // brute force while base is lower than square root
	}
	long long idx = sq_n; // when base > square root, there are only two digits
	while(n / idx - 1LL <= sq_n) idx--;
	while(idx >= 1LL){ // idx is the digit, when n forms a palindrome at base n / idx - 1, it is divisible by that digit
		if(!(n % idx)) printf("%lld\n", n / idx - 1LL);
		idx--;
	}
}