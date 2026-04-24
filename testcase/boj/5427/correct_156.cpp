#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
#define pii pair<int,int>
using namespace std;

int di[] = {1,-1,0,0};
int dj[] = {0,0,-1,1};
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int R, C;
		cin >> C >> R;
		string arr[R];
		rep(i,R) cin >> arr[i];
		queue<pii> fire, ppl;
		rep(i,R) {
			rep(j,C) {
				if(arr[i][j] == '@') {
					ppl.emplace(i,j);
				}
				else if(arr[i][j] == '*')
					fire.emplace(i,j);
			}
		}
		auto valid = [&](int x, int y) {
			return x>=0 && y>=0 && x < R && y < C;
		};
		int t = 1;
		while(!ppl.empty()) {
			int s = sz(fire);
			while(s--) {
				auto f = fire.front();
				fire.pop();
				rep(i,4) {
					int tx = f.first+di[i], ty = f.second+dj[i];
					if(!valid(tx,ty)) continue;
					if(arr[tx][ty] == '#' || arr[tx][ty] == '*') continue;
					arr[tx][ty] = '*';
					fire.emplace(tx,ty);
				}
			}
			s = sz(ppl);
			while(s--) {
				auto p = ppl.front();
				ppl.pop();
				rep(i,4) {
					int tx = p.first+di[i], ty = p.second+dj[i];
					if(!valid(tx,ty)) {
						cout << t << '\n';
						goto nexttc;
					}
					if(arr[tx][ty] == '#' || arr[tx][ty] == '*' || arr[tx][ty] == '@') continue;
					ppl.emplace(tx,ty);
					arr[tx][ty] = '@';
				}
			}
			t++;
		}
		cout << "IMPOSSIBLE\n";
		nexttc:;
	}
}
