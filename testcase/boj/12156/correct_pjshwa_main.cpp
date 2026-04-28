#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve(int tc) {
  int r, c, n;
  cin >> r >> c >> n;
  if (r > c) swap(r, c);

  int ans;
  if (n <= (r * c + 1) / 2) ans = 0;
  else if (r == 1) {
    int d = r * c - n, w = c - 1;
    ans = w - 2 * d;
  }
  else {
    int d = r * c - n, w = 2 * r * c - r - c;

    int corners1 = (r % 2 && c % 2) ? 4 : 2;
    int corners2 = 4 - corners1;

    int inners1 = ((r - 2) * (c - 2) + 1) / 2;
    int inners2 = (r - 2) * (c - 2) - inners1;

    int edges1 = (r * c + 1) / 2 - corners1 - inners1;
    int edges2 = r * c / 2 - corners2 - inners2;

    vector<int> v1, v2;
    for (int i = 0; i < inners1; i++) v1.push_back(4);
    for (int i = 0; i < edges1; i++) v1.push_back(3);
    for (int i = 0; i < corners1; i++) v1.push_back(2);
    for (int i = 0; i < inners2; i++) v2.push_back(4);
    for (int i = 0; i < edges2; i++) v2.push_back(3);
    for (int i = 0; i < corners2; i++) v2.push_back(2);

    ans = min(
      w - accumulate(v1.begin(), v1.begin() + d, 0),
      w - accumulate(v2.begin(), v2.begin() + d, 0)
    );
  }
  
  cout << "Case #" << tc << ": " << ans << '\n';
}

int main() {
  fast_io();
  
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) solve(i);
}
