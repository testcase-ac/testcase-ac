#include <bits/stdc++.h>
using namespace std;
bool solve(int T, vector<int> cnt, vector<int> score, vector<int> kayak) {
	int n = kayak.size();
	int big = max(score[0] + score[2], 2*score[1]);
	int small = min(score[0] + score[2], 2*score[1]);
	bool zerotwo = (big == score[0]+score[2]);

	for(int &k: kayak) {
		if(k * score[0]*2 >= T) {
			k = 1;
		} else if(k * (score[0] + score[1]) >= T) {
			k = 2;
		} else if(k * small >= T) {
			k = 3;
		} else if(k* big >= T) {
			k = 4;
		} else if(k * (score[1] + score[2]) >= T) {
			k = 5;
		} else if(k * score[2]*2 >= T) {
			k = 6;
		} else {
			return false;
		}
	}
	int r = n-1, l = 0;
	vector<int> three;
	while(r >= 0 && kayak[r] == 6) {
		if(cnt[2] >= 2) {
			cnt[2] -= 2;
		} else {
			return false;
		}
		r--;
	}
	while(r >= 0 && kayak[r] == 5) {
		if(cnt[1] >= 1 && cnt[2] >= 1) {
			cnt[1]--;
			cnt[2]--;
		} else if(cnt[2] >= 2) {
			cnt[2] -= 2;
		} else return false;
		r--;
	}
	int new_l = -1;
	while(l < n && kayak[l] == 1) {
		if(cnt[0] >= 2) {
			cnt[0] -= 2;
		} else if(cnt[0] >= 1 && cnt[1] >= 1) {
			cnt[0]--;
			cnt[1]--;
		} else {
			if(new_l < 0) {
				new_l = l;
			}
			kayak[l] = 3;
		}
		l++;
	}
	while(l < n && kayak[l] == 2) {
		if(cnt[0] >= 1 && cnt[1] >= 1) {
			cnt[0]--;
			cnt[1]--;
		} else {
			if(new_l < 0) {
				new_l = l;
			}
			kayak[l] = 3;
		}
		l++;
	}
	if(new_l < 0) new_l = l;
	while(r >= 0 && kayak[r] == 4) {
		if(zerotwo) {
			if(cnt[0] >=1 && cnt[2] >= 1) {
				cnt[0]--;
				cnt[2]--;
			} else if(cnt[1] >= 1 && cnt[2] >= 1) {
				cnt[1]--;
				cnt[2]--;
			} else if(cnt[2] >= 2) {
				cnt[2]-=2;
			} else {
				return false;
			}
		}
		else {
			if(cnt[1] >= 2) {
				cnt[1]-=2;
			} else if(cnt[1] >= 1 && cnt[2] >= 1) {
				cnt[1]--;
				cnt[2]--;
			} else if(cnt[2] >= 2) {
				cnt[2]-=2;
			} else {
				return false;
			}
		}
		r--;
	}
	return cnt[0] <= cnt[2];
}

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	vector<int> cnt(3);
	vector<int> score(3);
	cin >> cnt[0] >> cnt[1] >> cnt[2];
	cin >> score[0] >> score[1] >> score[2];
	int n = cnt[0] + cnt[1] + cnt[2];
	n /= 2;
	vector<int> kayak(n);
	for(int i=0; i<n; i++) {
		cin >> kayak[i];
	}
	sort(kayak.begin(), kayak.end());
	reverse(kayak.begin(), kayak.end());

	int l = 1, r = 2e8;
	while(l < r) {
		int m = (l+r+1)/2;
		if(solve(m, cnt, score, kayak)) {
			l = m;
		} else {
			r = m-1;
		}
	}
	cout << l;
}
