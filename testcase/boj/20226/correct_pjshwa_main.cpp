 // https://www.acmicpc.net/source/24240358
 // by koosaga
 
 #include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 300005;
const int mod = 1e9 + 7;

namespace miller_rabin{
    lint mul(lint x, lint y, lint mod){ return (__int128) x * y % mod; }
	lint ipow(lint x, lint y, lint p){
		lint ret = 1, piv = x % p;
		while(y){
			if(y&1) ret = mul(ret, piv, p);
			piv = mul(piv, piv, p);
			y >>= 1;
		}
		return ret;
	}
	bool miller_rabin(lint x, lint a){
		if(x % a == 0) return 0;
		lint d = x - 1;
		while(1){
			lint tmp = ipow(a, d, x);
			if(d&1) return (tmp != 1 && tmp != x-1);
			else if(tmp == x-1) return 0;
			d >>= 1;
		}
	}
	bool isprime(lint x){
		for(auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
			if(x == i) return 1;
			if(x > 40 && miller_rabin(x, i)) return 0;
		}
		if(x <= 40) return 0;
		return 1;
	}
}

namespace pollard_rho{
	lint f(lint x, lint n, lint c){
		return (c + miller_rabin::mul(x, x, n)) % n;
	}
	void rec(lint n, vector<lint> &v){
		if(n == 1) return;
		if(n % 2 == 0){
			v.push_back(2);
			rec(n/2, v);
			return;
		}
		if(miller_rabin::isprime(n)){
			v.push_back(n);
			return;
		}
		lint a, b, c;
		while(1){
			a = rand() % (n-2) + 2;
			b = a;
			c = rand() % 20 + 1;
			do{
				a = f(a, n, c);
				b = f(f(b, n, c), n, c);
			}while(gcd(abs(a-b), n) == 1);
			if(a != b) break;
		}
		lint x = gcd(abs(a-b), n);
		rec(x, v);
		rec(n/x, v);
	}
	vector<lint> factorize(lint n){
		vector<lint> ret;
		rec(n, ret);
		sort(ret.begin(), ret.end());
		return ret;
	}
};

int n, m, k, a[MAXN];
vector<int> gph[MAXN];
lint dp[32][MAXN];

void solve(){
	lint n;
	cin >> n;
    if(n == 0) exit(0);
	auto qq = pollard_rho::factorize(n);
	vector<lint> yaksu = {1};
	for(auto &j : qq){
		auto nyaksu = yaksu;
		for(auto &k : yaksu) nyaksu.push_back(j * k);
		sort(all(nyaksu));
		nyaksu.resize(unique(all(nyaksu)) - nyaksu.begin());
		yaksu = nyaksu;
	}
	lint ret = 1e18;
	for(auto &x : yaksu){
		if(x * x * x > n) break;
		int breaks = (int)sqrt(n / x);
		auto ptr = upper_bound(all(yaksu), (int)sqrt(n / x));
		while(ptr != yaksu.begin()){
			ptr--;
			lint y = *ptr;
			if(y < x) break;
			if((n / x) % y == 0){
				ret = min(ret, x + y + n/(x*y));
				break;
			}
		}
	}
	cout << ret << endl;
}


int main(){
while(1){
		solve();
	}
}
