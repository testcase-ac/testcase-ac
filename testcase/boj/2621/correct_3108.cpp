#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;
struct card {
	char color;
	int num;
	bool operator< (const card &c) const {
		return num < c.num;
	}
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	card arr[5];
	rep(i,5) cin >> arr[i].color >> arr[i].num;
	sort(arr, arr+5);
	int maxn = arr[4].num;
	bool coloreq = true;
	for(int i=1; i<5; i++) if(arr[i].color != arr[0].color) coloreq = false;
	bool diff1 = true;
	for(int i=1; i<5; i++) if(arr[i].num - arr[i-1].num != 1) diff1 = false;
	vector<int> mp(10);
	for(card &c: arr) mp[c.num]++;
	vector<int> szarr;
	if(coloreq && diff1) {
		return !(cout << 900+maxn);
	}
	for(int i=0; i<10; i++) {
		if(mp[i] == 4)
			return !(cout << 800+i);
	}
	int three = 0, two = 0;
	for(int i=0; i<10; i++) {
		if(mp[i] == 3) three = i;
		else if(mp[i] == 2) two = i;
	}
	if(three && two) return !(cout << 700+three*10+two);
	if(coloreq) return !(cout << 600+maxn);
	if(diff1) return !(cout << 500+maxn);
	if(three) return !(cout << 400+three);
	int t1 = 0;
	for(int i=0; i<10; i++) {
		if(mp[i] == 2) {
			if(!t1) t1 = i;
			else return !(cout << 300+i*10+t1);
		}
	}
	if(two) return !(cout << 200+two);
	cout << 100+maxn;
}
