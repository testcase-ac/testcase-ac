#include <bits/stdc++.h>
using namespace std;

int card[3][200], ans[200];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<3; j++) {
			cin >> card[j][i];
		}
	}
	for(int i=0; i<3; i++) {
		int chosen[101] = {};
		for(int j=0; j<n; j++)
			chosen[card[i][j]]++;
		for(int j=0; j<n; j++) {
			if(chosen[card[i][j]] == 1)
				ans[j] += card[i][j];
		}
	}
	for(int i=0; i<n; i++)
		 cout << ans[i] << '\n';
}
