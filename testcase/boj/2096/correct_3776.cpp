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
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> arr(3), maxa(3), mina(3), pmaxa(3), pmina(3);
	rep(i, 3) {
		cin >> arr[i];
		pmaxa[i] = arr[i];
		pmina[i] = arr[i];
	}
	mina = pmina, maxa = pmaxa;
	for(int i=1; i<n; i++) {
		cin >> arr[0] >> arr[1] >> arr[2];
		maxa[0] = max(pmaxa[0], pmaxa[1]) + arr[0];
		maxa[1] = max(max(pmaxa[0], pmaxa[1]), pmaxa[2]) + arr[1];
		maxa[2] = max(pmaxa[1], pmaxa[2]) + arr[2];
		mina[0] = min(pmina[0], pmina[1]) + arr[0];
		mina[1] = min(min(pmina[0], pmina[1]), pmina[2]) + arr[1];
		mina[2] = min(pmina[1], pmina[2]) + arr[2];
		//printf("maxa: %d %d %d, mina: %d %d %d\n", maxa[0], maxa[1], maxa[2], mina[0], mina[1], mina[2]);
		pmina = mina, pmaxa = maxa;
	}
	cout << *max_element(maxa.begin(), maxa.end()) << ' ' << *min_element(mina.begin(), mina.end());
}
