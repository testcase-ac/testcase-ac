#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int x;
	while(!(cin >> x).eof()) {
		x *= 10000000;
		int n;
		cin >> n;
		int arr[n];
		for(int i=0; i<n; i++) {
			cin >> arr[i];
		}
		sort(arr,arr+n);
		int ok = 0;
		for(int i=0; i<n; i++) {
			if(binary_search(arr+i+1, arr+n, x-arr[i])) {
				ok = arr[i];
				break;
			}
		}
		if(ok) printf("yes %d %d\n", ok, x-ok);
		else printf("danger\n");
	}
}
