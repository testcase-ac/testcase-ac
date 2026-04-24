#include <bits/stdc++.h>
using namespace std;
struct Pt {
	int l, r, i;
};
Pt arr[10000], arr2[10000];
bool ok[10000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i].l >> arr[i].r;
		arr[i].r++;
		arr[i].i = i;
	}
	sort(arr, arr+n, [](Pt a, Pt b){return a.l < b.l;});
	memcpy(arr2, arr, sizeof arr);
	sort(arr2, arr2+n, [](Pt a, Pt b){return a.r < b.r;});
	int i = 0, j = 0, nxt = arr[0].l;
	set<int> st;
	while(1) {
		while(i < n && arr[i].l == nxt) {
			st.insert(arr[i++].i);
		}
		while(j < n && arr2[j].r == nxt) {
			st.erase(arr2[j++].i);
		}
		if(j == n) break;
		nxt = arr2[j].r;
		if(i < n && arr[i].l < nxt)
			nxt = arr[i].l;
		if(st.size())
			ok[*st.rbegin()] = 1;
	}
	cout << accumulate(ok, ok+n, 0);
}
