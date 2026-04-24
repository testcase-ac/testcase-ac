#include <bits/stdc++.h>
using namespace std;
#define ll long long
bool ok[10];
ll p10[12], ans, A, B, X;

ll cdiv(ll a, ll b) {
	return (a+b-1)/b;
}
int cnt[100000];
bool check(ll n) {
	while(n) {
		if(!ok[n%10]) return 0;
		n /= 10;
	}
	return 1;
}
void brute(ll a, ll b) {
	if(a > b) return;
	for(; a<=b; a++) {
		if(a%X==0 && check(a)) {
			ans++;
		}
	}
}
void f(int p, ll num) {
	if(p == 4) {
		ll rnum = num+p10[5]-1;
		if(A <= num && rnum <= B) {
			ll m = cdiv(num, X) * X - num;
			if(X <= p10[5])
				ans += cnt[m];
			else
				ans += ((m < p10[5]) && check(m));
		} else {
			brute(max(A, num), min(B, rnum));
		}
		return;
	}
	for(int i=0; i<=9; i++) {
		if(ok[i] || (!num && !i))
			f(p-1, num+p10[p]*i);
	}
}
int main() {
	cin >> X >> A >> B;
	string s;
	cin >> s;
	for(char c: s)
		ok[c-'0'] = true;
	p10[0] = 1;
	for(int i=1; i<12; i++)
		p10[i] = p10[i-1]*10;
	
	if(X <= p10[5]) {
		for(int i=0; i<p10[5]; i++) {
			if(check(i) && !(!ok[0] && i < p10[4]))
				cnt[i%X]++;
		}
	}
	if(ok[0] && ok[1] && B == p10[11] && B%X == 0)
		ans++;
	f(10, 0);
	cout << ans;
}
