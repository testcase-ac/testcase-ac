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
	int n, m;
	cin >> n >> m;
	vector<int> arr1(n), arr2(m);
	rep(i, n) cin >> arr1[i];
	rep(i, m) cin >> arr2[i];
	int i = 0, j = 0;
	while(i < n && j < m) {
		if(arr1[i] < arr2[j])
			cout << arr1[i++] << ' ';
		else
			cout << arr2[j++] << ' ';
	}
	while(i < n)
		cout << arr1[i++] << ' ';
	while(j < m)
		cout << arr2[j++] << ' ';
}
