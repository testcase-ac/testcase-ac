// https://www.acmicpc.net/source/35083661
// by djs100201

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
#include<string>
#include<cstring>
#include<stack>
#include<map>
#include<set>
#include<deque>
#include<functional>
#include<unordered_map>
#include<list>
#include<cstdlib>
#include<ctime>
#include<cassert>
#include<bitset>
//#define double long double
//T.erase(unique(T.begin(),T.end()),T.end());
//written by djs100201
#define all(v) v.begin(),v.end()
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ = 1e6 + 100, inf = 1e12 + 1, mod = 1e9 + 7, sqrtN = 320;
ll dy[4] = { -1,0,1,0 }, dx[4] = { 0,1,0,-1 };
ll n, m, k, tc = 1, a, b, c, sum, x, y, z, w, base, ans;
ll gcd(ll x, ll y) {
	if (!y)return x;
	return gcd(y, x % y);
}
ll A[n_];
void solve(){
	for (int i = 1; i < n_; i++)
		for (int j = i + i; j < n_; j += i)A[j] += i;
	cin >> n;
	while (n--) {
		cin >> a;
		if (A[a] > a)cout << "abundant";
		else if (A[a] < a)cout << "deficient";
		else cout << "perfect";
		cout << '\n';
	}

}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//cin >> tc;
	while (tc--)solve();
}
