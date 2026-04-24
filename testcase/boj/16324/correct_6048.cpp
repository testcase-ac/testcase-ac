#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5e4;
const string imp = "impossible";
int nc2[MX];
string solve() {
	int zz, zo, oz, oo;
	cin >> zz >> zo >> oz >> oo;
	for(int i=0; i<MX; i++)
		nc2[i] = i*(i-1)/2;
	int tot_cnt;
	for(tot_cnt=1; tot_cnt<MX; tot_cnt++) {
		if(nc2[tot_cnt] == zz+zo+oz+oo)
			break;
	}
	//printf("tot_cnt = %d\n", tot_cnt);
	int zcnt, ocnt;
	if(zz == 0 && oo == 0) {
		if(tot_cnt == 1) {
			return "1";
		} else if(tot_cnt == 2) {
			if(oz == 1 && zo == 0) {
				return "10";
			} else if(oz == 0 && zo == 1) {
				return "01";
			} else
				return imp;
		} else {
			return imp;
		}
	} else {
		for(zcnt=0; zcnt<MX; zcnt++) {
			if(nc2[zcnt] == zz)
				break;
		}
		if(zcnt == MX)
			return imp;
		for(ocnt=0; ocnt<MX; ocnt++) {
			if(nc2[ocnt] == oo)
				break;
		}
		if(ocnt == MX)
			return imp;
		if(zcnt == 0) {
			zcnt = tot_cnt - ocnt;
		} else if(ocnt == 0) {
			ocnt = tot_cnt - zcnt;
		}
	}
	if(ocnt * zcnt != oz + zo) {
		return imp;
	}
	//printf("zcnt = %d, ocnt = %d\n", zcnt, ocnt);
	// 0000011111 -> 01이 최대
	string s;
	int cur_oz = 0, nxt = zcnt, lead_one_cnt = 0;
	while(cur_oz < oz) {
		int diff = oz - cur_oz;
		if(nxt < diff) {
			lead_one_cnt++;
			cur_oz += nxt;
		} else {
			break;
		}
	}
	int diff = oz - cur_oz;
	string mid;
	for(int i=0; i<zcnt; i++) {
		mid.push_back('0');
	}
	//printf("diff = %d, mid length = %d", diff, mid.size());
	if(ocnt)
		mid.insert(mid.end()-diff, '1');
	string ans;
	for(int i=0; i<lead_one_cnt; i++)
		ans.push_back('1');
	ans += mid;
	for(int i=0; i<ocnt-lead_one_cnt-(!!ocnt); i++) {
		ans.push_back('1');
	}
	return ans;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cout << solve();
}
