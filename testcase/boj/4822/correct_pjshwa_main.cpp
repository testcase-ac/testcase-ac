#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<string, int> fi;
int fcount;
int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

void init() {
  fi.clear(); fcount = 0;
}

string r2rank(int r) {
  if (r == 0) return "1st";
  if (r == 1) return "2nd";
  if (r == 2) return "3rd";
  return to_string(r + 1) + "th";
}

int N, M;
void solve() {
  init();
  vector<string> teams(N);
  vector<int> scores(N);

  for (int i = 0; i < N; ++i) {
    cin >> teams[i];
    fidx(teams[i]);
  }

  // team1 vs team2: x y
  vector<pii> undet;
  for (int i = 0; i < M; ++i) {
    string t1_s, t2_s; cin >> t1_s >> t2_s >> t2_s;
    t2_s.pop_back();

    int x, y; cin >> x >> y;
    int t1 = fidx(t1_s), t2 = fidx(t2_s);
    if (x == -1 && y == -1) undet.emplace_back(t1, t2);
    else {
      if (x > y) scores[t1] += 3;
      else if (x < y) scores[t2] += 3;
      else ++scores[t1], ++scores[t2];
    }
  }

  vector<int> minr(N, N + 1), maxr(N, 0);
  vector<pair<int, int>> ranks(N);
  function<void(int)> dfs = [&](int i) {
    if (i == undet.size()) {
      for (int j = 0; j < N; ++j) ranks[j] = {scores[j], j};
      sort(ranks.begin(), ranks.end(), greater<>());

      int lscore = -1, lrank = -1;
      for (int j = 0; j < N; ++j) {
        auto [s, t] = ranks[j]; int rank = j;
        if (s == lscore) rank = lrank;
        else lscore = s, lrank = rank;
        minr[t] = min(minr[t], rank);
        maxr[t] = max(maxr[t], rank);
      }
      return;
    }

    auto [t1, t2] = undet[i];
    scores[t1] += 3; dfs(i + 1); scores[t1] -= 3;
    scores[t2] += 3; dfs(i + 1); scores[t2] -= 3;
    ++scores[t1]; ++scores[t2]; dfs(i + 1); --scores[t1]; --scores[t2];
  };
  dfs(0);

  for (int i = 0; i < N; ++i) {
    cout << "Team " << teams[i] << " can finish as high as " << r2rank(minr[i]);
    cout << " place and as low as " << r2rank(maxr[i]) << " place.\n";
  }
}

int main() {
  fast_io();

  int f = 0;
  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    if (f) cout << '\n';
    solve(); f = 1;
  }
}
