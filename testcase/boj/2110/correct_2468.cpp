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
	int n, c;
	cin >> n >> c;
	int arr[n];
	rep(i,n) cin >> arr[i];
	sort(arr, arr+n);
	int l = 1, r = 1000000000, mid;
	while(l < r) {
		mid = (l+r+1)/2;
		//printf("l,r,mid=%d,%d,%d ", l,r,mid);
		bool ok = true;
		int i = 0, j, s = c-1;
		while(s--) {
			j = i+1;
			while(j < n && arr[j] - arr[i] < mid)
				j++;
			if(j == n) {
				ok = false;
				break;
			}
			i = j;
		}
		if(ok) {
			l = mid;
			//printf("ok\n");
		}
		else {
			r = mid - 1;
			//printf("not ok\n");
		}
	}
	cout << l;
}
