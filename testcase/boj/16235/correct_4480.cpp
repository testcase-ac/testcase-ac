#include <bits/stdc++.h>
using namespace std;
int added[10][10], toadd[10][10];
vector<int> tree[10][10];
int nut[10][10];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, T;
	cin >> n >> m >> T;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> added[i][j];
			nut[i][j] = 5;
		}
	}
	while(m--) {
		int x, y, z;
		cin >> x >> y >> z;
		tree[x-1][y-1] = {z};
	}
	while(T--) {
		// spring
		memset(toadd, 0, sizeof toadd);
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				auto& v = tree[i][j];
				auto& t = nut[i][j];
				sort(v.begin(), v.end());
				for(int k=0; k<v.size(); k++) {
					if(v[k] > t) {
						int s = k;
						while(k < v.size())
							toadd[i][j] += v[k++]/2;
						v.resize(s);
						break;
					}
					t -= v[k];
					v[k]++;
				}
			}
		}
		// summer+winter
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				nut[i][j] += toadd[i][j]+added[i][j];
			}
		}
		// autumn
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				for(int a: tree[i][j]) {
					if(a % 5 == 0) {
						for(int x=i-1; x<=i+1; x++) {
							for(int y=j-1; y<=j+1; y++) {
								if(!(0 <= x && x < n && 0 <= y && y < n)) continue;
								if(x == i && y == j) continue;
								tree[x][y].push_back(1);
							}
						}
					}
				}
			}
		}
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			ans += tree[i][j].size();
		}
	}
	cout << ans;
}
