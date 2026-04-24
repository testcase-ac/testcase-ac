#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
const int MX = 1e6+1, BUK = 1e3;
#else
const int MX = 1e6+1, BUK = 3;
#endif
char arr[MX];
int diff[BUK], mx[BUK], mn[BUK], fliped[BUK];
void flip_buk(int b) {
	fliped[b] ^= 1;
	diff[b] *= -1;
	swap(mx[b], mn[b]);
	mx[b] *= -1;
	mn[b] *= -1;
}
void calc_buk(int b) {
	int cur = 0ll;
	mx[b] = mn[b] = cur;
	for(int i=b*BUK; i<(b+1)*BUK; i++) {
		if(!arr[i]) break;
		cur += ((arr[i] == '(') ^ (fliped[b])) ? 1: -1;
		mx[b] = max(mx[b], cur);
		mn[b] = min(mn[b], cur);
	}
	diff[b] = cur;
}
void query(int l, int r, int& qst, int& qed, int& qmn) {
	int lb = l / BUK, rb = r/BUK, cur = 0;
	for(int i=l/BUK*BUK; i<l; i++) {
		cur += ((arr[i] == '(') ^ (fliped[lb])) ? 1: -1;
	}
	qst = qmn = cur;
	while(l % BUK && l <= r) {
		cur += ((arr[l] == '(') ^ (fliped[l/BUK])) ? 1: -1;
		qmn = min(qmn, cur);
		l++;
	}
	while(l / BUK < r / BUK) {
		qmn = min(qmn, cur+mn[l / BUK]);
		cur += diff[l / BUK];
		l += BUK;
	}
	while(l <= r) {
		cur += ((arr[l] == '(') ^ (fliped[l/BUK])) ? 1: -1;
		qmn = min(qmn, cur);
		l++;
	}
	qed = cur;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n >> arr;
	for(int b=0; b<(n+BUK-1)/BUK; b++) {
		calc_buk(b);
	}
	int q;
	cin >> q;
	while(q--) {
		int t, a, b;
		cin >> t >> a >> b;
		a--, b--;
		if(t == 1) {
			int l = a, r = b;
			while(l % BUK && l <= r) {
				arr[l] = arr[l] == '(' ? ')' : '(';
				l++;
			}
			calc_buk(a/BUK);
			while(l / BUK < r / BUK) {
				flip_buk(l/BUK);
				assert(fliped[l/BUK] >= 0 && fliped[l/BUK] <= 1);
				l += BUK;
			}
			while(l <= r) {
				arr[l] = arr[l] == '(' ? ')' : '(';
				l++;
			}
			calc_buk(r/BUK);
		} else {
			int qst, qed, qmn;
			query(a, b, qst, qed, qmn);
			//printf("qst = %d, qed = %d, qmn = %d\n", qst, qed, qmn);

			if(qst > qed)
				swap(qst, qed);
			int ans = qed - qst + (qst - qmn) * 2;
			cout << ans + (b-a+1) << '\n';
		}
	}
}
