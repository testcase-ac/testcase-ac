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
	//ios::sync_with_stdio(false);cin.tie(NULL);
	vector<pair<int,int>> arr(8);
	rep(i, 8) {
		cin >> arr[i].first;
		arr[i].second = i+1;
	}
	sort(arr.begin(), arr.end());
	vector<int> ind(5);
	int sum = 0;
	rep(i, 5) {
		ind[i] = arr[7-i].second;
		sum += arr[7-i].first;
	}
	sort(ind.begin(), ind.end());
	printf("%d\n", sum);
	rep(i, 5)
		printf("%d ", ind[i]);

}
