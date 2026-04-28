#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;
int L[5];
int n, V;

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> L[i];
  cin >> V;

  map<tuple<int, int, int, int>, int> cdist;
  priority_queue<
    pair<int, tuple<int, int, int, int>>,
    vector<pair<int, tuple<int, int, int, int>>>,
    greater<pair<int, tuple<int, int, int, int>>>
  > pq;
  pq.push({0, {L[0], 0, 0, 0}});
  cdist[{L[0], 0, 0, 0}] = 0;

  while (!pq.empty()) {
    auto [w, v] = pq.top();
    pq.pop();

    if (w > cdist[v]) continue;

    auto [v1, v2, v3, v4] = v;
    int v5 = L[0] - (v1 + v2 + v3 + v4);
    int p12 = min(v1, L[1] - v2);
    int p13 = min(v1, L[2] - v3);
    int p14 = min(v1, L[3] - v4);
    int p15 = min(v1, L[4] - v5);
    int p21 = min(v2, L[0] - v1);
    int p23 = min(v2, L[2] - v3);
    int p24 = min(v2, L[3] - v4);
    int p25 = min(v2, L[4] - v5);
    int p31 = min(v3, L[0] - v1);
    int p32 = min(v3, L[1] - v2);
    int p34 = min(v3, L[3] - v4);
    int p35 = min(v3, L[4] - v5);
    int p41 = min(v4, L[0] - v1);
    int p42 = min(v4, L[1] - v2);
    int p43 = min(v4, L[2] - v3);
    int p45 = min(v4, L[4] - v5);
    int p51 = min(v5, L[0] - v1);
    int p52 = min(v5, L[1] - v2);
    int p53 = min(v5, L[2] - v3);
    int p54 = min(v5, L[3] - v4);

    if (!cdist.count({v1 - p12, v2 + p12, v3, v4}) || cdist[{v1 - p12, v2 + p12, v3, v4}] > w + p12) {
      cdist[{v1 - p12, v2 + p12, v3, v4}] = w + p12;
      pq.push({w + p12, {v1 - p12, v2 + p12, v3, v4}});
    }
    if (!cdist.count({v1 - p13, v2, v3 + p13, v4}) || cdist[{v1 - p13, v2, v3 + p13, v4}] > w + p13) {
      cdist[{v1 - p13, v2, v3 + p13, v4}] = w + p13;
      pq.push({w + p13, {v1 - p13, v2, v3 + p13, v4}});
    }
    if (!cdist.count({v1 - p14, v2, v3, v4 + p14}) || cdist[{v1 - p14, v2, v3, v4 + p14}] > w + p14) {
      cdist[{v1 - p14, v2, v3, v4 + p14}] = w + p14;
      pq.push({w + p14, {v1 - p14, v2, v3, v4 + p14}});
    }
    if (!cdist.count({v1 - p15, v2, v3, v4}) || cdist[{v1 - p15, v2, v3, v4}] > w + p15) {
      cdist[{v1 - p15, v2, v3, v4}] = w + p15;
      pq.push({w + p15, {v1 - p15, v2, v3, v4}});
    }
    if (!cdist.count({v1 + p21, v2 - p21, v3, v4}) || cdist[{v1 + p21, v2 - p21, v3, v4}] > w + p21) {
      cdist[{v1 + p21, v2 - p21, v3, v4}] = w + p21;
      pq.push({w + p21, {v1 + p21, v2 - p21, v3, v4}});
    }
    if (!cdist.count({v1, v2 - p23, v3 + p23, v4}) || cdist[{v1, v2 - p23, v3 + p23, v4}] > w + p23) {
      cdist[{v1, v2 - p23, v3 + p23, v4}] = w + p23;
      pq.push({w + p23, {v1, v2 - p23, v3 + p23, v4}});
    }
    if (!cdist.count({v1, v2 - p24, v3, v4 + p24}) || cdist[{v1, v2 - p24, v3, v4 + p24}] > w + p24) {
      cdist[{v1, v2 - p24, v3, v4 + p24}] = w + p24;
      pq.push({w + p24, {v1, v2 - p24, v3, v4 + p24}});
    }
    if (!cdist.count({v1, v2 - p25, v3, v4}) || cdist[{v1, v2 - p25, v3, v4}] > w + p25) {
      cdist[{v1, v2 - p25, v3, v4}] = w + p25;
      pq.push({w + p25, {v1, v2 - p25, v3, v4}});
    }
    if (!cdist.count({v1 + p31, v2, v3 - p31, v4}) || cdist[{v1 + p31, v2, v3 - p31, v4}] > w + p31) {
      cdist[{v1 + p31, v2, v3 - p31, v4}] = w + p31;
      pq.push({w + p31, {v1 + p31, v2, v3 - p31, v4}});
    }
    if (!cdist.count({v1, v2 + p32, v3 - p32, v4}) || cdist[{v1, v2 + p32, v3 - p32, v4}] > w + p32) {
      cdist[{v1, v2 + p32, v3 - p32, v4}] = w + p32;
      pq.push({w + p32, {v1, v2 + p32, v3 - p32, v4}});
    }
    if (!cdist.count({v1, v2, v3 - p34, v4 + p34}) || cdist[{v1, v2, v3 - p34, v4 + p34}] > w + p34) {
      cdist[{v1, v2, v3 - p34, v4 + p34}] = w + p34;
      pq.push({w + p34, {v1, v2, v3 - p34, v4 + p34}});
    }
    if (!cdist.count({v1, v2, v3 - p35, v4}) || cdist[{v1, v2, v3 - p35, v4}] > w + p35) {
      cdist[{v1, v2, v3 - p35, v4}] = w + p35;
      pq.push({w + p35, {v1, v2, v3 - p35, v4}});
    }
    if (!cdist.count({v1 + p41, v2, v3, v4 - p41}) || cdist[{v1 + p41, v2, v3, v4 - p41}] > w + p41) {
      cdist[{v1 + p41, v2, v3, v4 - p41}] = w + p41;
      pq.push({w + p41, {v1 + p41, v2, v3, v4 - p41}});
    }
    if (!cdist.count({v1, v2 + p42, v3, v4 - p42}) || cdist[{v1, v2 + p42, v3, v4 - p42}] > w + p42) {
      cdist[{v1, v2 + p42, v3, v4 - p42}] = w + p42;
      pq.push({w + p42, {v1, v2 + p42, v3, v4 - p42}});
    }
    if (!cdist.count({v1, v2, v3 + p43, v4 - p43}) || cdist[{v1, v2, v3 + p43, v4 - p43}] > w + p43) {
      cdist[{v1, v2, v3 + p43, v4 - p43}] = w + p43;
      pq.push({w + p43, {v1, v2, v3 + p43, v4 - p43}});
    }
    if (!cdist.count({v1, v2, v3, v4 - p45}) || cdist[{v1, v2, v3, v4 - p45}] > w + p45) {
      cdist[{v1, v2, v3, v4 - p45}] = w + p45;
      pq.push({w + p45, {v1, v2, v3, v4 - p45}});
    }
    if (!cdist.count({v1 + p51, v2, v3, v4}) || cdist[{v1 + p51, v2, v3, v4}] > w + p51) {
      cdist[{v1 + p51, v2, v3, v4}] = w + p51;
      pq.push({w + p51, {v1 + p51, v2, v3, v4}});
    }
    if (!cdist.count({v1, v2 + p52, v3, v4}) || cdist[{v1, v2 + p52, v3, v4}] > w + p52) {
      cdist[{v1, v2 + p52, v3, v4}] = w + p52;
      pq.push({w + p52, {v1, v2 + p52, v3, v4}});
    }
    if (!cdist.count({v1, v2, v3 + p53, v4}) || cdist[{v1, v2, v3 + p53, v4}] > w + p53) {
      cdist[{v1, v2, v3 + p53, v4}] = w + p53;
      pq.push({w + p53, {v1, v2, v3 + p53, v4}});
    }
    if (!cdist.count({v1, v2, v3, v4 + p54}) || cdist[{v1, v2, v3, v4 + p54}] > w + p54) {
      cdist[{v1, v2, v3, v4 + p54}] = w + p54;
      pq.push({w + p54, {v1, v2, v3, v4 + p54}});
    }
  }

  int ans = INF;
  for (auto& [v, z] : cdist) {
    if (get<0>(v) == V) ans = min(ans, z);
  }
  if (ans == INF) cout << "impossible\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
