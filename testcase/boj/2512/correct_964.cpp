#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> arr(n);
	int sum = 0, maxval = 0;
	rep(i, n) {
		cin >> arr[i];
		sum += arr[i];
		maxval = max(maxval, arr[i]);
	}
	int tlimit;
	cin >> tlimit;
	if(tlimit >= sum)
		return !(cout << maxval);
	int left = 1, right = tlimit-1, mid;
	while(left < right) {
		mid = (left+right+1) / 2;
		int tempsum = 0;
		rep(i, n)
			tempsum += min(mid, arr[i]);
		if(tempsum <= tlimit)
			left = mid;
		else
			right = mid - 1;
	}
	cout << left;
}
