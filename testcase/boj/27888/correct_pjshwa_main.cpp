#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<string> split(const string &str, string delim) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delim, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delim.size();
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

void compress(vector<string>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

int getidx(vector<string>& a, string& b) {
  auto it = lower_bound(a.begin(), a.end(), b);
  if (it == a.end() || *it != b) return -1;
  return it - a.begin();
}

const int MAXN = 5e5;
int B[MAXN], F[1 << 9];

void solve() {
  int N; cin >> N;

  vector<string> stations(N);
  for (int i = 0; i < N; ++i) cin >> stations[i];
  sort(stations.begin(), stations.end());

  int Q; cin >> Q;
  vector<tuple<int, string, string>> queries;
  vector<string> features;
  for (int i = 0; i < Q; ++i) {
    string op; cin >> op;
    if (op == "U") {
      string sta, feats; cin >> sta >> feats;
      queries.emplace_back(0, sta, feats);
      for (auto& feat : split(feats, ",")) features.push_back(feat);
    }
    else {
      string feats; cin >> feats;
      queries.emplace_back(1, "", feats);
    }
  }
  compress(features);
  int Z = features.size();
  assert(Z <= 9);

  F[0] = N;
  for (int i = 0; i < Q; ++i) {
    auto& [op, sta, feats] = queries[i];

    int feat_s = 0, ok = 1;
    for (auto& feat : split(feats, ",")) {
      int feat_idx = getidx(features, feat);
      if (feat_idx == -1) ok = 0;
      else feat_s |= 1 << feat_idx;
    }

    if (op == 0) {
      int sta_idx = getidx(stations, sta);
      --F[B[sta_idx]];
      B[sta_idx] = feat_s;
      ++F[B[sta_idx]];
    }
    else {
      if (!ok) {
        cout << "0\n";
        continue;
      }

      int ans = 0;
      for (int s = 0; s < (1 << Z); ++s) {
        if ((s & feat_s) == feat_s) ans += F[s];
      }
      cout << ans << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
