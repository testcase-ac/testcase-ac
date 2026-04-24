#include <bits/stdc++.h>
using namespace std;
int arr[100][100], mxc = 3, mxr = 3;
vector<int> srt(vector<int>& v) {
	vector<int> res;
	map<int, int> mp;
	for(int i: v) {
		if(!i) continue;
		mp[i]++;
	}
	vector<pair<int, int>> mpv(mp.begin(), mp.end());
	sort(mpv.begin(), mpv.end(), [](pair<int, int>& a, pair<int, int>& b){
		return tie(a.second, a.first) < tie(b.second, b.first);
	});
	for(auto pr: mpv) {
		res.push_back(pr.first);
		res.push_back(pr.second);
		if(res.size() == 100)
			break;
	}
	return res;
}
int srtcol(int c) {
	vector<int> v;
	for(int i=0; i<mxr; i++)
		v.push_back(arr[i][c]);
	vector<int> res = srt(v);
	for(int i=0; i<100; i++)
		arr[i][c] = i < res.size() ? res[i] : 0;
	return res.size();
}
int srtrow(int r) {
	vector<int> v(arr[r], arr[r]+mxc);
	vector<int> res = srt(v);
	for(int i=0; i<100; i++)
		arr[r][i] = i < res.size() ? res[i] : 0;
	return res.size();
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, c, k;
	cin >> r >> c >> k;
	r--, c--;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			cin >> arr[i][j];
		}
	}
	for(int t=0; t<=100; t++) {
		if(arr[r][c] == k) return !(cout << t);
		int nxt = 0;
		if(mxr >= mxc) {
			for(int i=0; i<mxr; i++)
				nxt = max(nxt, srtrow(i));
			mxc = nxt;
		} else {
			for(int i=0; i<mxc; i++)
				nxt = max(nxt, srtcol(i));
			mxr = nxt;
		}
	}
	cout << -1;
}
