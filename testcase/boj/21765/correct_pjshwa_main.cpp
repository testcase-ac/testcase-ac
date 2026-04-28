#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

const double EPS = 1e-8;
const int MAX = 2e5;
vector<int> s[MAX];
vector<pii> slengths;
bool vis[MAX];

bool do_search(double p) {
  memset(vis, 0, sizeof(vis));
  for (auto [sl, si] : slengths) {
    if (p * sl > sl - 1) {
      for (auto sii : s[si]) vis[sii] = true;
    }
    else {
      for (auto sii : s[si]) {
        if (!vis[sii]) return false;
      }
    }
  }
  return true;
}

int main() {
  int n, m, sl, si;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    cin >> sl;
    slengths.push_back({sl, i});
    while (sl--) {
      cin >> si;
      s[i].push_back(si - 1);
    }
  }
  sort(slengths.begin(), slengths.end());

  double left = 0, right = 1;
  double mid = (left + right) / 2;

  while (right - left > EPS) {
    if (do_search(mid)) right = mid;
    else left = mid + EPS;

    mid = (left + right) / 2;
  }

  cout << fixed << setprecision(8) << mid;
}
