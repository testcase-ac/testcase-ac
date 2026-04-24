#include <bits/stdc++.h>
using namespace std;
set<int> st;
int arr[100002], N, Q;
void upd(int t) {
	if(t > N) return;
	if(t == 1 || arr[t-1] > arr[t])
		st.insert(t);
	else
		st.erase(t);
};
int32_t main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> N >> Q;
	for(int i=1; i<=N; i++) {
		cin >> arr[i];
		upd(i);
	}
	while(Q--) {
		int q, l, r;
		cin >> q >> l >> r;
		if(q == 1) {
			auto itl = st.upper_bound(l), itr = st.upper_bound(r);
			if(itl == itr) {
				cout << "CS204\n";
			} else {
				cout << "HSS090\n";
			}
		} else {
			swap(arr[l], arr[r]);
			upd(l);
			upd(l+1);
			upd(r);
			upd(r+1);
		}
	}
}
