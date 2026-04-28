#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

priority_queue<int> pqs[4];
struct Fraction {
  ll p, q;

  bool operator<(const Fraction &f) const {
    return p * f.q < q * f.p;
  }
};

int main() {
  fast_io();

  int n, k;
  ll o[4];
  cin >> n >> k;
  for (int i = 0; i < 4; i++) cin >> o[i];

  for (int i = 0; i < n; i++) {
    string ti;
    int ui;
    cin >> ti >> ui;
    pqs[ti[0] - 'A'].push(ui);
  }

  for (int i = 0; i < k; i++) {
    vector<pair<Fraction, int>> c;
    for (int j = 0; j < 4; j++) if (!pqs[j].empty()) c.push_back({{pqs[j].top(), o[j]}, j});
    sort(c.begin(), c.end());

    auto selected = c.back();
    int inc = selected.first.p, idx = selected.second;
    o[idx] += inc;
    pqs[idx].pop();
    cout << (char)('A' + idx) << ' ' << inc << '\n';
  }
}
