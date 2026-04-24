#include <bits/stdc++.h>
using namespace std;
const int MXL = 1000;
int w, l, n;
struct Key {
	int o[MXL], h[MXL];
	Key(){o[0] = 0;}
	bool operator==(Key k) {
		for(int i=0; i<l; i++) {
			if(o[i] != k.o[i] || h[i] != k.h[i])
				return 0;
		}
		return 1;
	}
};
struct Lock {
	int a[MXL], b[MXL];
	bool top;
	Key genkey() {
		Key k;
		for(int i=0; i<l; i++) {
			k.h[i] = w-a[i]-b[i];
			if(i)
				k.o[i] = (top ? a[i]-a[i-1] : b[i]-b[i-1]);
		}
		return k;
	}
	bool equal(Lock &lock) {
		Key lkey = lock.genkey();
		if(lkey == genkey()) return 1;
		top = !top;
		if(lkey == genkey()) return 1;
		reverse(a, a+l); reverse(b, b+l);
		if(lkey == genkey()) return 1;
		top = !top;
		if(lkey == genkey()) return 1;
		return 0;
	}
};
Lock arr[100];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> w >> l >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<l; j++)
			cin >> arr[i].a[j];
		for(int j=0; j<l; j++)
			cin >> arr[i].b[j];
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		bool has = 0;
		for(int j=0; j<i; j++) {
			if(arr[i].equal(arr[j])) {
				has = 1;
				break;
			}
		}
		if(!has) ans++;
	}
	cout << ans;
}
