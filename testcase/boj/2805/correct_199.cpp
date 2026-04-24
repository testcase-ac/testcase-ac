#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

#define MAXH 1000000000
using namespace std;

// Complexity: O(log(MAXH)) * (O(N) + O(logN)) = O(Nlog(MAXH))
bool rev(ll a, ll b) {return a > b;}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	ll n, m;
	cin >> n >> m;
	vector<ll> arr(n);
	rep(i, n) cin >> arr[i];
	sort(arr.begin(), arr.end(), rev);
	int left=0, right=MAXH, mid;
	while(left <= right) {
		mid = (left+right+1) / 2;  // why not "(left+right)/2" ?
		ll tsum = 0;
		auto end_it = lower_bound(arr.begin(), arr.end(), mid, rev);
		for(auto it = arr.begin(); it != end_it; it++) {
			tsum += (*it - mid);
		}
		//printf("left=%d, right=%d, mid=%d, end_it-begin=%d,tsum=%lld\n", left, right, mid, end_it-arr.begin(), tsum);
		if(tsum >= m) {
			if(left == mid) break;
			left = mid;
		} else {
			right = mid - 1;
		}
	}
	cout << mid;
}