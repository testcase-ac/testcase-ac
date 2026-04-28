#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct Fraction {
  ll nom, den;
  Fraction() : nom(0), den(1) {}
  Fraction(ll nom) : nom(nom), den(1) {}
  Fraction(ll nom, ll den) : nom(nom), den(den) {
    ll g = std::gcd(nom, den);
    this->nom /= g;
    this->den /= g;
    if (this->den < 0) {
      this->nom *= -1;
      this->den *= -1;
    }
  }
  string to_string() {
    string ret = "";
    ret += std::to_string(nom);
    if (den > 1) ret += "/" + std::to_string(den);
    return ret;
  }
  Fraction operator*(const int &rhs) {
    return Fraction(nom * rhs, den);
  }
};

struct Term {
  bool sign; Fraction coef; int deg;
  Term(bool sign, Fraction coef, int deg) : sign(sign), coef(coef), deg(deg) {}
  string to_string() {
    string ret = "";
    if (!sign) ret += "-";
    ret += coef.to_string();
    if (deg > 0) {
      ret += "x";
      if (deg > 1) ret += "^" + std::to_string(deg);
    }
    return ret;
  }
  bool is_zero() {
    return coef.nom == 0;
  }
  void differentiate() {
    if (is_zero()) return;
    coef = coef * deg--;
  }
  bool operator==(const Term &rhs) {
    return sign == rhs.sign && coef.nom == rhs.coef.nom && coef.den == rhs.coef.den && deg == rhs.deg;
  }
};

void solve() {
  string S; cin >> S;
  int i = 0, N = S.size();

  function<bool()> read_sign = [&]() {
    bool ret = true;
    if (S[i] == '+') ++i;
    else if (S[i] == '-') {
      ret = false;
      ++i;
    }
    return ret;
  };
  function<Fraction()> read_coef = [&]() {
    if (S[i] == 'C' || S[i] == 'D') {
      ++i;
      return Fraction();
    }
    if (!isdigit(S[i])) return Fraction(1);

    ll nom = 0;
    while (isdigit(S[i])) {
      nom = nom * 10 + S[i] - '0';
      ++i;
    }
    if (S[i] != '/') return Fraction(nom);

    ++i;
    ll den = 0;
    while (isdigit(S[i])) {
      den = den * 10 + S[i] - '0';
      ++i;
    }
    return Fraction(nom, den);
  };
  function<int()> read_deg = [&]() {
    if (i == N || S[i] != 'x') return 0;
    ++i;
    if (i == N || S[i] != '^') return 1;
    ++i;

    int deg = 0;
    while (i < N && isdigit(S[i])) {
      deg = deg * 10 + S[i] - '0';
      ++i;
    }
    return deg;
  };
  function<Term()> read_term = [&]() {
    bool sign = read_sign();
    Fraction coef = read_coef();
    int deg = read_deg();
    return Term(sign, coef, deg);
  };

  vector<Term> A, B;
  while (i < N) A.push_back(read_term());
  cin >> S; i = 0, N = S.size();
  while (i < N) B.push_back(read_term());

  for (auto& term : A) term.differentiate();
  for (auto& term : A) term.differentiate();
  while (!A.empty() && A.back().is_zero()) A.pop_back();
  while (!B.empty() && B.back().is_zero()) B.pop_back();

  if (A.size() != B.size()) cout << "No\n";
  else {
    bool ok = true;
    for (int i = 0; i < (int)A.size(); ++i) ok &= A[i] == B[i];
    if (ok) cout << "Yes\n";
    else cout << "No\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
