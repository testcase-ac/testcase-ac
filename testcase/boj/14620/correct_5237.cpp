#include <bits/stdc++.h>
using namespace std;

int arr[10][10], di[] = {0,0,1,-1}, dj[] = {1,-1,0,0}, ans = INT_MAX, n;
bool seen[10][10];
void f(int d, int cost) {
	if(d == 3) {
		ans = min(ans, cost);
		return;
	}
	for(int i=1; i<n-1; i++) {
		for(int j=1; j<n-1; j++) {
			bool ok = !seen[i][j];
			for(int k=0; k<4; k++) {
				if(seen[i+di[k]][j+dj[k]])
					ok = 0;
			}
			if(!ok) continue;
			int addi = arr[i][j];
			seen[i][j] = 1;
			for(int k=0; k<4; k++) {
				seen[i+di[k]][j+dj[k]] = 1;
				addi += arr[i+di[k]][j+dj[k]];
			}
			f(d+1, cost+addi);
			seen[i][j] = 0;
			for(int k=0; k<4; k++)
				seen[i+di[k]][j+dj[k]] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
		}
	}
	f(0, 0);
	cout << ans;
}
