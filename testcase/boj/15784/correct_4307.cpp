#include <bits/stdc++.h>
using namespace std;
int arr[1001][1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, a, b;
	cin >> n >> a >> b;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cin >> arr[i][j];
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if(i == a || j == b) {
				if(arr[i][j] > arr[a][b])
					return !(cout << "ANGRY");
			}
		}
	}
	cout << "HAPPY";
}
