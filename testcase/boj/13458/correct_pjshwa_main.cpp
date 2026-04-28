#include <cstdio>

int main(){
	long long n;
	scanf("%lld", &n);
	long long a[n], b, c;
	long long watchers = 0LL;
	for(auto &x : a){
		scanf("%lld", &x);
	}
	scanf("%lld%lld", &b, &c);
	for(auto &x : a){
		x -= b; 
		if (x <= 0) continue;
		if (x % c) watchers++;
		watchers += (x / c);
	}
	watchers += n;
	printf("%lld", watchers);
}