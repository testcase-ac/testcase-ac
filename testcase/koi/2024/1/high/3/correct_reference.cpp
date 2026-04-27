#include <iostream>
#include <stack>

using namespace std;
using ll = long long;

const int N = 250005;
int n, q, a[N], d[N], s[N], p[N];
ll s2[N], c[N];
stack<int> stk;
ll f(int l, int r){
	if(l > r) return 0;
	return (s2[r] - s2[l - 1]) + (ll)(r + 1) * (s[r] - s[l - 1]);
}
int main(){
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i < n; i++){
		int v = a[i + 1];
		while(a[i] > v){
			v *= 2;
			d[i]++;
		}
		while(a[i] <= v / 2){
			v /= 2;
			d[i]--;
		}
		s[i] = s[i - 1] + d[i];
		s2[i] = s2[i - 1] - (ll)i * d[i];
	}
	p[n] = n;
	for(int i = n - 1; i >= 0; i--){
		while(stk.size() && s[stk.top()] >= s[i]) stk.pop();
		if(stk.size()){
			p[i] = stk.top();
			c[i] = f(i + 1, p[i] - 1);
		}
		else p[i] = n;
		stk.push(i);
	}
	for(int l, r, i = 1; i <= q; i++){
		cin >> l >> r;
		int pos = l - 1;
		ll ans = 0;
		while(p[pos] <= r - 1){
			ans += c[pos];
			pos = p[pos];
		}
		ans += f(pos + 1, r - 1);
		cout << ans << "\n";
	}
	return 0;
}