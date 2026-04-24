#include <bits/stdc++.h>
using namespace std;
int dr[]={-1,-1,0,1,1,1,0,-1}, dc[]={0,1,1,1,0,-1,-1,-1}, N, M, K;
struct fb {
	int r, c, m, s, d;
	void read() { cin >> r >> c >> m >> s >> d; r--; c--; }
	bool operator<(const fb& o) const { return r==o.r ? c<o.c : r<o.r; }
	void move() {
		r = (r+dr[d]*(s%N)+N)%N;
		c = (c+dc[d]*(s%N)+N)%N;
	}
};
vector<fb> fbs;
void go() {
	for(auto& f: fbs) f.move();
	sort(fbs.begin(), fbs.end());
	vector<fb> nxt;
	for(int i=0, j=0; i<fbs.size(); i=j) {
		int m = 0, s = 0, evens = 0;
		while(j<fbs.size() && fbs[i].r==fbs[j].r && fbs[i].c==fbs[j].c) {
			m += fbs[j].m;
			s += fbs[j].s;
			evens += fbs[j].d%2==0;
			j++;
		}
		if(j-i==1) {
			nxt.push_back(fbs[i]);
			continue;
		}
		m /= 5;
		if(m==0) continue;
		s /= j-i;
		for(int k=(evens && evens < j-i); k<=7; k+=2) {
			nxt.push_back({fbs[i].r, fbs[i].c, m, s, k});
		}
	}
	fbs = nxt;
}
int main() {
	cin >> N >> M >> K;
	fbs.resize(M);
	for(auto& f: fbs) f.read();
	while(K--) go();
	int r = 0;
	for(auto& f: fbs) r += f.m;
	cout << r << '\n';
}