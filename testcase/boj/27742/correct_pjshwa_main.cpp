#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 4;
ll B[MAX][MAX];

void solve() {
  ll N, K; cin >> N >> K;
  N--;

  int mi, mj;
  for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
    cin >> B[i][j];
    if (B[i][j] == -1) mi = i, mj = j;
  }

  ll left = 0, right = K + 1;
  while (left < right) {
    ll mid = (left + right) / 2;
    B[mi][mj] = mid;

    ll G[4][4]{};

    // 1. 승점
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) {
      if (B[i][j] > B[j][i]) G[i][0] += 3;
      else if (B[i][j] == B[j][i]) G[i][0] += 1, G[j][0] += 1;
      else G[j][0] += 3;
    }

    // 2. 골득실
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) {
      G[i][1] += B[i][j] - B[j][i];
      G[j][1] += B[j][i] - B[i][j];
    }

    // 3. 다득점
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) {
      G[i][2] += B[i][j];
      G[j][2] += B[j][i];
    }

    // 4. 상대 전적
    vector<tuple<ll, ll, ll, ll>> V;
    for (int i = 0; i < 4; i++) V.emplace_back(G[i][0], G[i][1], G[i][2], 3 - i);
    sort(V.begin(), V.end(), greater<>());

    int fst = 3 - get<3>(V[0]), snd = 3 - get<3>(V[1]);
    if (fst == N || snd == N) right = mid;
    else left = mid + 1;
  }

  if (left == K + 1) cout << "-1\n";
  else cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
