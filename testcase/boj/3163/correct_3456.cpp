#include <bits/stdc++.h>
using namespace std;
int n, l, k;
struct Ant {
	int pos, id, fall;
	int time() {
		return id > 0 ? l - pos : pos;
	}
};
const int MX = 1e5;
Ant arr[MX], parr[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		cin >> n >> l >> k;
		for(int i=0; i<n; i++)
			cin >> arr[i].pos >> arr[i].id;
		memcpy(parr, arr, sizeof arr);
		sort(arr, arr+n, [](Ant &a, Ant &b){return a.time() < b.time();});
		int lcnt = 0, rcnt = n-1;
		for(int i=0; i<n; i++) {
			if(arr[i].id < 0) arr[i].fall = parr[lcnt++].id;
			else arr[i].fall = parr[rcnt--].id;
			if(i && arr[i].time() == arr[i-1].time() && arr[i].fall < arr[i-1].fall)
				swap(arr[i], arr[i-1]);
		}
		cout << arr[k-1].fall << '\n';
	}
}
