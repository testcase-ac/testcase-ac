#include <bits/stdc++.h>
#define INFLL (0x3f3f3f3f3f3f3f3fll)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef __int128_t lll;
typedef pair<ll, ll> pll;
const char *pfstr[] = {"00", "25", "50", "75"};
void print(ll x) { cout << x/4 << '.' << pfstr[x%4] << '\n'; }
ll pw(ll x) { return x*x; }
ll f(const pll &p, ll x) { return p.fi * x + p.se; }
lll operator * (const pll &a, const pll &b) { return lll(a.fi) * b.se - lll(a.se) * b.fi; }
lll ccw(const pll &a, const pll &b, const pll &c) { return a*b + b*c + c*a; }

const int MAXN = 100055;

pll P[MAXN];
ll D[MAXN];

ll X[MAXN], H[MAXN];

int N, Ps, Pe;

void normInput() {
	int n = 1;
	for(int i = 2; i <= N; i++) {
		for(; n && H[n]-X[n] <= H[i]-X[i]; n--);
		n++;
		H[n] = H[i]; X[n] = X[i];
	}
	N = n;
	int e = n;
	for(int i = N-1; i; i--) {
		for(; e <= n && H[e]+X[e] <= H[i]+X[i]; e++);
		e--;
		H[e] = H[i]; X[e] = X[i];
	}
	for(int i = 1, j = e; j <= N; i++, j++) {
		X[i] = X[j];
		H[i] = H[j];
	}
	N = n-e+1;
}

void run() {
	cin >> N;
	for(int i = 1; i <= N; i++)
		cin >> X[i] >> H[i];

	normInput();

	D[0] = 0;
	P[0].fi = 2ll * (H[1]-X[1]);
	P[0].se = pw(H[1]-X[1]);
	Ps = 0; Pe = 1;

	for(int i = 1; i <= N; i++) {
		ll x = X[i]+H[i];
		for(; Ps+1 < Pe && f(P[Ps], x) >= f(P[Ps+1], x); Ps++);
		D[i] = pw(x) + f(P[Ps], x);

		pll p(2ll * (H[i+1]-X[i+1]), D[i] + pw(H[i+1]-X[i+1]));
		for(; Ps+1 < Pe && ccw(P[Pe-2], P[Pe-1], p) >= 0; Pe--);
		P[Pe++] = p;
	}

	print(D[N]);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	for(; T--;) run();
	return 0;
}
