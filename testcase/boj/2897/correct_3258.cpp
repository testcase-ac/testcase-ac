#include <bits/stdc++.h>
using namespace std;

char arr[100][100];
int ans[5];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, c;
	cin >> r >> c;
	for(int i=0; i<r; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<r-1; i++) {
		for(int j=0; j<c-1; j++) {
			int cnt = 0;
			bool ok = 1;
			for(int a=0; a<2; a++) {
				for(int b=0; b<2; b++) {
					if(arr[i+a][j+b] == '#') ok = 0;
					else if(arr[i+a][j+b] == 'X') cnt++;
				}
			}
			if(ok)
				ans[cnt]++;
		}
	}
	for(int i=0; i<5; i++) {
		cout << ans[i] << '\n';
	}
}
