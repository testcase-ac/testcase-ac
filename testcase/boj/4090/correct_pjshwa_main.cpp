#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXX = 1e6 + 1000;
vector<int> V;

int X;
void solve() {
  cout << *lower_bound(V.begin(), V.end(), X) << '\n';
}

int main() {
  fast_io();

  vector<int> P(MAXX + 1);
  for (int a = 1; a <= sqrt(MAXX); ++a) for (int b = a; a * b <= MAXX; ++b) {
    int c = a * b;
    string a_s = to_string(a), b_s = to_string(b), c_s = to_string(c);
    a_s += b_s;
    sort(a_s.begin(), a_s.end());
    sort(c_s.begin(), c_s.end());

    if (a_s == c_s) P[c] = 1;
  }
  for (int i = 1; i <= MAXX; ++i) if (P[i]) V.push_back(i);

  while (cin >> X) {
    if (X == 0) break;
    solve();
  }
}
