#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MX = 1e6+3;
ll R, C, k;
int acc[MX], arr[MX];
bool g(int c, int i) {return c&(1<<i);}
int f(int r, int c) {
	int ans = 0, zcnt = 0;
	for(int i=0; i<20; i++)
		zcnt += !g(c,i);
	for(int i=19; i>=0; i--) {
		zcnt -= !g(c,i);
		if(g(r,i)) {
			ans += 1<<zcnt;
			if(g(c,i)) break;
		}
	}
	return ans;
}
int main() {
	cin >> R >> C >> k;
	int sum = 0, st = 0, l = 0, r = -1;
	bool dir = 0;
	while(1) {
		if(sum == min(R,C)) st++;
		if(sum == max(R,C)) st++;
		if(!st) r++;
		else if(st == 1) {
			if(R < C) l++, r++;
		}
		else l++;
		if(k <= (r-l+1)) break;
		acc[l]++, acc[r+1]--;
		k -= (r-l+1);
		dir ^= 1;
		sum++;
	}
	int cur = 0;
	for(int i=0; i<MX; i++) {
		cur += acc[i];
		arr[i] = cur;
	}
	for(int i=dir?r:l;k; dir?i--:i++) {
		arr[i]++;
		k--;
	}
	ll ans = arr[0];
	for(int c=1;arr[c]; c++) {
		ans += f(arr[c], c);
	}
	cout << ans;
}
