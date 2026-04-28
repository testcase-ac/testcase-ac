#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  vector<pair<string, int>> grades_with_scores = {
    {"F", 0},
    {"D0", 100},
    {"D+", 150},
    {"C0", 200},
    {"C+", 250},
    {"B0", 300},
    {"B+", 350},
    {"A0", 400},
    {"A+", 450}
  };
  map<string, int> grades_map(grades_with_scores.begin(), grades_with_scores.end());

  int N; string Xs; cin >> N >> Xs;
  int X = stoi(Xs[0] + Xs.substr(2, 2));

  int credits_sum = 0, wscore_sum = 0;
  for (int i = 0; i < N - 1; ++i) {
    int credit; string grade; cin >> credit >> grade;

    credits_sum += credit;
    wscore_sum += grades_map[grade] * credit;
  }

  int L; cin >> L;
  int T = X * (credits_sum + L);

  for (auto& [grade, score] : grades_with_scores) {
    int total = wscore_sum + score * L;
    total /= (credits_sum + L);

    if (total > X) return cout << grade << '\n', void();
  }
  cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
