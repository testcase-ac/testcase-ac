#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct Fraction{
	ll p, q;
	Fraction(ll a, ll b) : p(q), q(b) {
		ll g = __gcd(a, b);
		p = a / g;
		q = b / g;
	}
	Fraction() : Fraction(0, 1) {}
	Fraction(ll x) : Fraction(x, 1) {}
	Fraction operator +(Fraction x){
		return Fraction(p*x.q + q*x.p, q*x.q);
	}
	Fraction operator -(Fraction x){
		return Fraction(p*x.q - q*x.p, q*x.q);
	}
	Fraction operator *(Fraction x){
		return Fraction(p*x.p, q*x.q);
	}
	Fraction operator /(Fraction x){
		return Fraction(p*x.q, q*x.p);
	}
	Fraction operator *(ll x){
		return Fraction(p*x, q);
	}
	Fraction operator /(ll x){
		return Fraction(p, q*x);
	}
	bool operator <(Fraction x){
		return p*x.q < x.p*q;
	}
	bool operator >(Fraction x){
		return p*x.q > x.p*q;
	}
	bool operator <=(Fraction x){
		return p*x.q <= x.p*q;
	}
	bool operator >=(Fraction x){
		return p*x.q >= x.p*q;
	}
	bool operator ==(Fraction x){
		return p*x.q == x.p*q;
	}
  bool operator <(const Fraction &x) const {
    return p*x.q < x.p*q;
  }
	Fraction abs(){
		return Fraction(p > 0 ? p : -p, q > 0 ? q : -q);
	}
};

void solve() {
  int N;
  cin >> N;

  int p[N * N];
  for (int i = 0; i < N * N; i++) p[i] = i;

  Fraction mscore = Fraction(0);
  ll it = 10000;
  while (it--) {
    int a[N][N];
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) a[i][j] = p[i * N + j] + 1;

    Fraction xscore = Fraction(999999999);
    for (int i = 0; i < N; i++) {
      for (int j1 = 0; j1 < N; j1++) for (int j2 = j1 + 1; j2 < N; j2++) {
        if (a[i][j1] > a[i][j2]) {
          xscore = min(xscore, Fraction(a[i][j1], a[i][j2]));
        }
        else xscore = min(xscore, Fraction(a[i][j2], a[i][j1]));
      }
    }
    for (int j = 0; j < N; j++) {
      for (int i1 = 0; i1 < N; i1++) for (int i2 = i1 + 1; i2 < N; i2++) {
        if (a[i1][j] > a[i2][j]) xscore = min(xscore, Fraction(a[i1][j], a[i2][j]));
        else xscore = min(xscore, Fraction(a[i2][j], a[i1][j]));
      }
    }
    if (xscore > mscore) mscore = xscore;

    shuffle(p, p + N * N, mt19937(it));
  }

  cout << mscore.p << ' ' << mscore.q << '\n';

  // do {
  //   int a[N][N];
  //   for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) a[i][j] = p[i * N + j] + 1;

  //   double xscore = 999999999;
  //   for (int i = 0; i < N; i++) {
  //     for (int j1 = 0; j1 < N; j1++) for (int j2 = j1 + 1; j2 < N; j2++) {
  //       if (a[i][j1] > a[i][j2]) xscore = min(xscore, (double)a[i][j1] / a[i][j2]);
  //       else xscore = min(xscore, (double)a[i][j2] / a[i][j1]);
  //     }
  //   }
  //   for (int j = 0; j < N; j++) {
  //     for (int i1 = 0; i1 < N; i1++) for (int i2 = i1 + 1; i2 < N; i2++) {
  //       if (a[i1][j] > a[i2][j]) xscore = min(xscore, (double)a[i1][j] / a[i2][j]);
  //       else xscore = min(xscore, (double)a[i2][j] / a[i1][j]);
  //     }
  //   }
  //   if (abs(xscore - mscore) < 1e-9) {
  //     for (int i = 0; i < N; i++) {
  //       for (int j = 0; j < N; j++) cout << a[i][j] << ' ';
  //       cout << '\n';
  //     }
  //     break;
  //     // cout << "====================\n";
  //   }

  // } while (next_permutation(p, p + N * N));
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
