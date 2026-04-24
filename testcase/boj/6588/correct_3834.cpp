#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <unordered_set>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	vector<int> prime;
	unordered_set<int> primeset;
	for(int i=3; i<=1000000; i+=2) {
		int m = round(sqrt(i));
		bool isprime = true;
		for(int p: prime) {
			if(p > m)
				break;
			if(i % p == 0) {
				isprime = false;
				break;
			}
		}
		if(isprime) {
			prime.push_back(i);
			primeset.insert(i);
		}
	}
	int num;
	while(scanf("%d", &num)) {
		if(num == 0) break;
		for(int p: prime) {
			if(primeset.find(num-p) != primeset.end()) {
				printf("%d = %d + %d\n", num, p, num-p);
				break;
			}
		}
	}
}
