#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int k, n;
	cin >> k >> n;
	vector<int> arr(k);
	int maxlength = 0;
	rep(i, k) {
		cin >> arr[i];
		maxlength = max(arr[i], maxlength);
	}
	ll left = 0, right = maxlength, mid;
	while(left < right) {
		mid = (left+right+1) / 2;
		ll piececnt = 0;
		rep(i, k) piececnt += (arr[i] / mid);
		//printf("left=%lld, right=%lld, mid=%lld. piececnt=%lld\n",left, right, mid, piececnt);
		if(piececnt >= n) {
			left = mid;
		} else {
			right = mid - 1;
		}
	}
	cout << left;
}
