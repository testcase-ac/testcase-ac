#include <bits/stdc++.h>
using namespace std;
int dr[] = {0,1,1,1,0,-1,-1,-1};
int dc[] = {1,1,0,-1,-1,-1,0,1};
char arr[30][31];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			for(int d=0; d<8; d++) {
				int i1 = i+dr[d], j1 = j+dc[d], i2 = i1+dr[d], j2 = j1+dc[d];
				if(!(0 <= i2 && i2 < n && 0 <= j2 && j2 < n)) continue;
				if(isalpha(arr[i][j]) && arr[i][j] == arr[i1][j1] && arr[i][j] == arr[i2][j2])
					return !(cout << arr[i][j]);
			}
		}
	}
	cout << "ongoing";
}
