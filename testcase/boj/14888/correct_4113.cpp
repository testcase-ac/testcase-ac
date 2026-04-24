#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <deque>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
int n;
vector<int> arr, opcnt(4);
deque<int> opinuse;
int maxans = INT_MIN, minans = INT_MAX;
void solve() {
	if(sz(opinuse) == n-1) {
		int num = arr[0];
		rep(i, n-1) {
			if(opinuse[i] == 0) { // add
				num += arr[i+1];
			} else if(opinuse[i] == 1) {
				num -= arr[i+1];
			} else if(opinuse[i] == 2) {
				num *= arr[i+1];
			} else if(opinuse[i] == 3) {
				num /= arr[i+1];
			}
		}
		maxans = max(maxans, num);
		minans = min(minans, num);
		return;
	}
	rep(i, 4) {
		if(!opcnt[i]) continue;
		opinuse.push_back(i);
		opcnt[i]--;
		solve();
		opinuse.pop_back();
		opcnt[i]++;
	}
}
int main() {
	cin >> n;
	arr.resize(n);
	rep(i, n)
		cin >> arr[i];
	rep(i, 4)
		cin >> opcnt[i];
	solve();
	printf("%d\n%d", maxans, minans);
}
