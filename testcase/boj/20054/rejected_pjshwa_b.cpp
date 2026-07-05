#include<stdio.h>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<queue>
#include<assert.h>
using namespace std;
//using lld = long long int;
using lld = __int128;
using pll = pair<lld, lld>;
int type;
int n, m, p;
const lld mod = 1000000007;
lld M[3] = { 998244353, 1004535809, 1092616193 };
lld Mp[3] = { 476, 479, 521 };
lld wlist[3][29];
lld wlist_inv[3][29];
lld expp(lld p, lld q) {
	lld r = 1;
	lld z = p % M[type];
	while (q) {
		if (q & 1) { r = (r * z) % M[type]; }
		q >>= 1;
		if (q) { z = (z * z) % M[type]; }
	}
	return r;
}
void inil() {
	for (int k = 0; k < 3; k++) {
		type = k;
		lld w = expp(3, Mp[type]);
		wlist[k][21] = w;
		wlist_inv[k][21] = expp(w, M[type] - 2);
		for (int i = 20; i >= 0; i--) {
			wlist[k][i] = (wlist[k][i + 1] * wlist[k][i + 1]) % M[type];
			wlist_inv[k][i] = (wlist_inv[k][i + 1] * wlist_inv[k][i + 1]) % M[type];
		}
	}
}
void fft(vector <long long int>& a, bool invert)
{
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	int li = 1;
	for (int len = 2; len <= n; len <<= 1) {
		long long int wlen = invert ? wlist_inv[type][li] : wlist[type][li];
		for (int i = 0; i < n; i += len) {
			long long int w = 1;
			for (int j = 0; j < len / 2; j++) {
				long long int u = a[i + j] % M[type], v = (a[i + j + len / 2] * w) % M[type];
				a[i + j] = (u + v) % M[type];
				a[i + j + len / 2] = (u + M[type] - v) % M[type];
				w = (w * wlen) % M[type];
			}
		}
		li++;
	}
	if (invert) {
		static unordered_map<int, long long int> memoi[3];
		if (memoi[type].find(n) == memoi[type].end())memoi[type][n] = expp(n, M[type] - 2);
		long long int invzn = memoi[type][n];
		for (int i = 0; i < n; i++) a[i] = (a[i] * invzn) % M[type];
	}
}

void multiply(const vector<long long int>& a, const vector<long long int>& b, vector<long long int>& res)
{
	vector <long long int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while (n < a.size() + b.size()) n <<= 1;
	fa.resize(n); fb.resize(n);
	fft(fa, false); fft(fb, false);
	for (int i = 0; i < n; i++) fa[i] = (fa[i] * fb[i]) % M[type];
	fft(fa, true);
	res.resize(n);
	for (int i = 0; i < n; i++) res[i] = fa[i];
	while (n > 1) { if (res[n - 1] == 0)n--; else break; }
	res.resize(n);
}
int main() {
	int t = 1, tv = 0;
	int i, j, k, l;
	inil();
	while (t--) {
		scanf("%d %d", &n, &m);
		vector<long long int> d, s;
		d.push_back(1);
		s.push_back(1);
		int dl = 1;
		type = 0;
		lld np = (expp(M[1], M[0] - 2) * expp(M[2], M[0] - 2)) % M[0];
		type = 1;
		lld nq = (expp(M[0], M[1] - 2) * expp(M[2], M[1] - 2)) % M[1];
		type = 2;
		lld nr = (expp(M[0], M[2] - 2) * expp(M[1], M[2] - 2)) % M[2];

		lld MM = M[0] * M[1] * M[2];
		for (int mi = 1; mi <= m; mi++) {
			vector<long long int> e[3], f[3];
			int el, fl;
			el = fl = 0;
			for (k = 0; k < 3; k++) {
				type = k;
				multiply(d, d, e[k]);
				multiply(d, s, f[k]);
				if (el < e[k].size()) el = e[k].size();
				if (el < f[k].size()) el = f[k].size();
			}

			for (k = 0; k < 3; k++) {
				e[k].resize(el);
				f[k].resize(el);
			}
			if (el > n) el = n;
			dl = el + 1;
			d.resize(dl);
			s.resize(dl);
			d[0] = 0;
			for (i = 0; i < el; i++) {
				lld res = 0;
				lld rfs = 0;
				res = (res + ((e[0][i] * np) % M[0] * M[1] * M[2])) % MM;
				res = (res + ((e[1][i] * nq) % M[1] * M[0] * M[2])) % MM;
				res = (res + ((e[2][i] * nr) % M[2] * M[0] * M[1])) % MM;
				res %= mod;
				rfs = (rfs + ((f[0][i] * np) % M[0] * M[1] * M[2])) % MM;
				rfs = (rfs + ((f[1][i] * nq) % M[1] * M[0] * M[2])) % MM;
				rfs = (rfs + ((f[2][i] * nr) % M[2] * M[0] * M[1])) % MM;
				rfs %= mod;
				d[i + 1] = (2 * rfs - res) % mod;
				if (d[i + 1] < 0) d[i + 1] += mod;
				s[i + 1] = (s[i + 1] + d[i + 1]) % mod;
			}
			/*
			printf("mi : %d / ", mi);
			for (int i = 0; i < dl; i++) {
				printf("%lld ", d[i]);
			}
			printf(" / ");
			for (int i = 0; i < dl; i++) {
				printf("%lld ", s[i]);
			}
			printf("\n");
			*/
		}
		if (s.size() <= n) {
			printf("0\n");
		}
		else {
			printf("%lld\n", s[n]);
		}
	}
}
