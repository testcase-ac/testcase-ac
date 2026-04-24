#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
bool comp(pair<int,string> p1, pair<int,string> p2) {
	return p1.first < p2.first;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<pair<int, string>> arr(n);
	rep(i, n) cin >> arr[i].first >> arr[i].second;
	stable_sort(arr.begin(), arr.end(), comp);
	for(auto p: arr)
		cout << p.first << ' ' << p.second << '\n';
}
