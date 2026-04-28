#include <bits/stdc++.h>
typedef long long ll;
#define pii pair<int, int>
using namespace std;

int main() {
  string s;
  long long k;
  cin >> s >> k;

  int tsz = s.size();
  vector<pii> pos;
  for (int i = 0; i < tsz; i++) {
    if (s[i] % 5 == 4) pos.push_back({i, 0});
    if (s[i] % 5 == 0) pos.push_back({i, 1});
  }
  reverse(pos.begin(), pos.end());
  int psz = pos.size();

  if (k > (1LL << psz)) {
    cout << "-1\n";
    return 0;
  }

  int idx = 0; k--;
  while (idx < psz) {
    auto[p, bias] = pos[idx];
    if (k & 1) bias += 5;
    s[p] = 49 + bias;

    idx++;
    k /= 2;
  }

  cout << s << '\n';
}
