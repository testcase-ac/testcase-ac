#include <bits/stdc++.h>
using namespace std;
int arr[1000][100];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			cin >> arr[i][j];
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			bool a = 0, b = 0;
			for(int k=0; k<m; k++) {
				if(arr[i][k] && !arr[j][k])
					a = 1;
				if(!arr[i][k] && arr[j][k])
					b = 1;
			}
			if(a && b)
				return !(cout << "NO");
		}
	}
	cout << "YES";
}
