#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <cmath>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define db(i) ((double)(i))
using namespace std;

int main() {
	int n, sum=0;
	scanf("%d", &n);
	vector<int> arr(n);
	rep(i, n) {
		scanf("%d", &arr[i]);
		sum += arr[i];
	}
	sort(arr.begin(), arr.end());
	printf("%d\n", (int)((db(sum)/db(n))+(sum > 0 ? 0.5:-0.5)));
	printf("%d\n", arr[n/2]);

	int index = 0;
	int mode, modecnt = 0;
	bool twomodes = false;
	while(1) {
		if(index >= n) break;
		int numChecking = arr[index];
		int cnt = 0;
		while(index < n && arr[index] == numChecking) {
			index++;
			cnt++;
		}
		if(cnt > modecnt) {
			mode = numChecking;
			twomodes = false;
			modecnt = cnt;
		} else if(cnt == modecnt && !twomodes) {
			mode = numChecking;
			twomodes = true;
		}	
	}
	printf("%d\n", mode);
	printf("%d\n", arr[n-1]-arr[0]);

}
