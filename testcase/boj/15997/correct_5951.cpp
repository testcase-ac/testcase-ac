#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
int result[6];
double prob[4][4][3], ans[4];

void rec(int dep) {
	if(dep == 6) {
		int pt[4] = {}, t = 0;
		double p = 1;
		rep(i,4) for(int j=i+1; j<4;j++) {
			int r = result[t++];
			p *= prob[i][j][r];
			if(r == 0) pt[i] += 3;
			else if(r == 1) pt[i] += 1, pt[j] += 1;
			else pt[j] += 3;
		}
		if(!p) return;
		int ptc[4];
		memcpy(ptc, pt, sizeof pt);
		sort(ptc, ptc+4), reverse(ptc, ptc+4);
		int a = 0, b;
		while(ptc[a] > ptc[2]) a++;
		b = a;
		while(ptc[b] == ptc[1]) b++;
		double bp = p*((double)(2-a)/(b-a));
		rep(i,4) {
			if(pt[i] > ptc[a]) ans[i] += p;
			else if(b-a && pt[i] == ptc[a]) ans[i] += bp;
		}
		return;
	}
	rep(i,3) {
		result[dep] = i;
		rec(dep+1);
	}
}
int main() {
	int t = 0;
	map<string, int> mp;
	rep(i,4) {
		string s;
		cin >> s;
		mp[s] = t++;
	}
	rep(i,6) {
		string a, b;
		double w, d, l;
		cin >> a >> b >> w >> d >> l;
		int ai = mp[a], bi = mp[b];
		if(ai > bi) {
			swap(ai, bi);
			swap(w, l);
		}
		prob[ai][bi][0] = w;
		prob[ai][bi][1] = d;
		prob[ai][bi][2] = l;
	}
	rec(0);
	rep(i,4) printf("%.10f\n", ans[i]);
}
