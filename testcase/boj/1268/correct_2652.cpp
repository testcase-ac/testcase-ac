#include <bits/stdc++.h>
using namespace std;

int arr[1000][5], ans[1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<5; j++) {
			cin >> arr[i][j];
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			for(int k=0; k<5; k++) {
				if(arr[i][k] == arr[j][k]) {
					ans[i]++;
					ans[j]++;
					break;
				}
			}
		}
	}
	cout << max_element(ans, ans+n)-ans+1;
}
