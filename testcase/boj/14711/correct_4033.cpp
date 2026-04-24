#include <bits/stdc++.h>
using namespace std;

int grid[1000][1000];
char ans[1000][1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<int> ls;
	for(int i=0; i<n; i++) {
		if(s[i] == '#') {
			grid[0][i] = 1;
			ls.push_back(i);
		}
	}
	cout << s << '\n';
	for(int i=1; i<n; i++) {
		for(int j: ls) {
			if(j-1>=0)
				grid[i-1][j-1]++;
			if(j+1<n)
				grid[i-1][j+1]++;
			grid[i-1][j]++;
			grid[i][j]++;
		}
		ls.clear();
		for(int j=0; j<n; j++) {
			if(grid[i-1][j] % 2) {
				cout << '#';
				grid[i][j]++;
				ls.push_back(j);
			}
			else
				cout << '.';
		}
		cout << '\n';
	}
}
