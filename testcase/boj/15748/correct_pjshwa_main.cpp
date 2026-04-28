#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int x[MAX];

struct Stop {
  ll pos, tastiness;

  bool operator<(const Stop& rhs) const {
    return tastiness == rhs.tastiness ? pos > rhs.pos : tastiness > rhs.tastiness;
  }
} s[MAX];

int main() {
  fast_io();

  int l, n, rf, rb;
  cin >> l >> n >> rf >> rb;
  for (int i = 0; i < n; i++) {
    cin >> s[i].pos >> s[i].tastiness;
  }
  sort(s, s + n);

  ll cpos = 0, mx = 0;
  for (int i = 0; i < n; i++) {
    if (cpos > s[i].pos) continue;
    mx += s[i].tastiness * (s[i].pos - cpos) * (rf - rb);
    cpos = max(cpos, s[i].pos);
  }
  cout << mx << '\n';
}
