// https://justicehui.github.io/koi/2019/09/19/BOJ2582/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
ll arr[33];

int main(){
	mt19937 rd = mt19937((unsigned)chrono::steady_clock::now().time_since_epoch().count());
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	uniform_int_distribution<int> ran(0, n-1);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			char c; cin >> c;
			arr[i] <<= 1;
			if(c == 'H') arr[i] |= 1;
		}
	}

	int ans = n*n;
	int a = 0, b = 0;
	int prv = n*n;
	double t = 1.0, k = 2.5;
	for(int i=0; i<10101; i++){
		b = a ^ (1 << ran(rd));
		int now = 0;
		for(int j=0; j<n; j++){
			int t = __builtin_popcount(arr[j] ^ b);
			now += min(t, n-t);
		}
		double nowP = exp((prv - now) / (k * t));
		if(nowP > (double)ran(rd) / (n-1)){
			a = b; prv = now;
		}
		ans = min(ans, prv);
		k *= 0.9999;
	}
	cout << ans;
}
