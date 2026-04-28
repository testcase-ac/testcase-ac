#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string Astr, Bstr, Cstr; cin >> Astr >> Bstr >> Cstr;

  int ansSq;
  if (Astr == "?") {
    int B = stoi(Bstr), C = stoi(Cstr);
    ansSq = C * C - B * B;
  } else if (Bstr == "?") {
    int A = stoi(Astr), C = stoi(Cstr);
    ansSq = C * C - A * A;
  } else {
    int A = stoi(Astr), B = stoi(Bstr);
    ansSq = A * A + B * B;
  }

  int q = sqrt(ansSq);
  if (q * q == ansSq) cout << q << '\n';
  else {
    for (int s = q; s >= 2; --s) {
      if (ansSq % (s * s) == 0) {
        ansSq /= s * s;
        cout << s << " \\cdot \\sqrt{" << ansSq << "}\n";
        return;
      }
    }
    cout << "\\sqrt{" << ansSq << "}\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
