#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <vector>
#include <algorithm>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
bool comp(pair<int,int> a, pair<int,int> b) {
	return a.second < b.second || (a.second == b.second && a.first < b.first);
}
int main() {
	 int n, a, b;
	 cin >> n;
	 vector<pair<int,int>> arr(n);
	 rep(i, n) {
	 	cin >> a >> b;
	 	arr[i].first = a;
	 	arr[i].second = b;
	}
	sort(arr.begin(), arr.end(), comp);
	int endtime=arr[0].second, ans=1;
	for(int i=1; i<n; i++) {
		if(arr[i].first >= endtime) {
			ans++;
			endtime = arr[i].second;
		}
	}
	cout << ans;
}
