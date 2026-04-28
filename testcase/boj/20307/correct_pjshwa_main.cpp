#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i128 = __int128;

namespace __int128__ {
	i128 _abs(i128 n) {
		return n < 0 ? -n : n;
	}
	i128 _gcd(i128 a, i128 b) {
		return b ? _gcd(b, a % b) : a;
	}
	i128 _stoi(string s) {
		i128 ret = 0, i = 0, flag = 0;
		if (s[i] == '-') flag = 1, i++;
		for (; i < s.size(); i++) {
			ret = 10 * ret + (s[i] & 15);
		}
		return flag ? -ret : ret;
	}
	string _to_string(i128 n) {
		string ret, t;
		if (n < 0) ret.push_back('-'), n = -n;
		i128 sz = 1, m = n;
		for (; m >= 10; m /= 10) sz++;
		for (; sz--; n /= 10) t.push_back(n % 10 | 48);
		reverse(t.begin(), t.end()); ret += t;
		return ret;
	}
};
using namespace __int128__;

struct Fraction {
	i128 a, b;
	Fraction(i128 a = 0, i128 b = 0) : a(a), b(b) {}

	void Reduce() {
		i128 g = _gcd(_abs(a), _abs(b));
		if (g) a /= g, b /= g;
		if (b < 0) a = -a, b = -b;
		if (b == 0) exit(1);
	}

	friend istream& operator >> (istream& in, Fraction& i) {
		string s; in >> s;
		if (int t = s.find('/'); t == string::npos) {
			i.a = _stoi(s);
			i.b = 1;
		}
		else {
			i.a = _stoi(s.substr(0, t));
			i.b = _stoi(s.substr(t + 1, s.size()));
			i.Reduce();
		}
		return in;
	}
	friend ostream& operator << (ostream & out, Fraction i) {
		i.Reduce();
		if (i.a == 0) out << 0;
		else if (i.b == 1) out << _to_string(i.a);
		else {
			if (i.a < 0) out << '-', i.a = -i.a;
			out << _to_string(i.a) << '/' << _to_string(i.b);
		}
		return out;
	}

	Fraction& operator += (const Fraction i) { a = a * i.b + i.a * b; b = b * i.b; Reduce(); return *this; }
	Fraction& operator -= (const Fraction i) { a = a * i.b - i.a * b; b = b * i.b; Reduce(); return *this; }
	Fraction& operator *= (const Fraction i) { a = a * i.a; b = b * i.b; Reduce(); return *this; }
	Fraction& operator /= (const Fraction i) { a = a * i.b; b = b * i.a; Reduce(); return *this; }

	friend Fraction operator + (Fraction a, Fraction b) { a += b; return a; }
	friend Fraction operator - (Fraction a, Fraction b) { a -= b; return a; }
	friend Fraction operator * (Fraction a, Fraction b) { a *= b; return a; }
	friend Fraction operator / (Fraction a, Fraction b) { a /= b; return a; }
};

using row = vector<Fraction>;
using matrix = vector<row>;

struct Matrix {
	int n, m; matrix M;
	Matrix(int n, int m) : n(n), m(m), M(n, row(m)) {}

	int f(row& i) { //pos of leading element
		for (int j = 0; j < m; j++) {
			if (i[j].a != 0) return j;
		}
		return m;
	}
	void Div(row& i, Fraction t) {
		for (auto& j : i) j /= t;
	}

	void Sol() {
		for (int i = 0; i < n; i++) {    
	    	sort(M.begin() + i, M.end(), [&](row& a, row& b) {
    			return f(a) < f(b);
		    });
			int t = f(M[i]);
			if (t == m) break;
			Div(M[i], M[i][t]);
			for (int j = 0; j < n; j++) {
				if (i == j || M[j][t].a == 0) continue;
				auto cur = M[j][t];
				for (int k = 0; k < m; k++) {
					M[j][k] -= M[i][k] * cur;
				}
			}
		}
	}
	void Input() {
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
			cin >> M[i][j];
		}
	}
	void Print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) cout << M[i][j] << ' ';
			cout << '\n';
		}
	}
};

int main() {
	fastio;
	int n, m; cin >> n >> m;
	Matrix M(n, m); M.Input();
	M.Sol(); M.Print();
}
