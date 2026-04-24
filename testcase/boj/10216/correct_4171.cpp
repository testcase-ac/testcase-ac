#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
struct Circle {
	int x, y, r;
};
Circle arr[3000];
int parent[3000];
int find(int i) {return i == parent[i] ? i : parent[i] = find(parent[i]);}
void joinroot(int i, int j) { parent[i] = j;}

inline int sq(int i){return i*i;}
bool intersect(int i, int j) {
	return sq(arr[i].x-arr[j].x) + sq(arr[i].y-arr[j].y) <= sq(arr[i].r+arr[j].r);
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		rep(i,n) {
			cin >> arr[i].x >> arr[i].y >> arr[i].r;
			parent[i] = i;
		}
		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				if(intersect(i,j))
					joinroot(find(i), find(j));
			}
		}
		int ans = 0;
		rep(i,n) if(parent[i] == i) ans++;
		cout << ans << '\n';
	}
}
