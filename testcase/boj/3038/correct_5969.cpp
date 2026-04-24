#include <bits/stdc++.h>
using namespace std;

int ans[1<<15], temp[1<<15], n;
void cpy(int i, int j, int h, int H, bool left) {
	if(h == H) return;
	if(left == (h == H-1))
		temp[j] = ans[i]*2+1;
	else
		temp[j] = ans[i]*2;
	cpy(i*2, j*2, h+1, H, left);
	cpy(i*2+1, j*2+1, h+1, H, left);
}
void print(int i) {
	if(i >= (1<<n)) return;
	cout << ans[i] << ' ';
	print(2*i);
	print(2*i+1);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	ans[1] = 1;
	for(int i=1; i<n; i++) {
		cpy(1, 2, 0, i, true);
		cpy(1, 3, 0, i, false);
		temp[1] = 1;
		memcpy(ans, temp, sizeof temp);
	}
	print(1);
}
