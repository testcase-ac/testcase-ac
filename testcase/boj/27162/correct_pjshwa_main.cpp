#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int A[5], ans = 0;

void rank_ones() {
  int cur = 0;
  for (int i = 0; i < 5; i++) if (A[i] == 1) cur += 1;
  ans = max(ans, cur);
}

void rank_twos() {
  int cur = 0;
  for (int i = 0; i < 5; i++) if (A[i] == 2) cur += 2;
  ans = max(ans, cur);
}

void rank_threes() {
  int cur = 0;
  for (int i = 0; i < 5; i++) if (A[i] == 3) cur += 3;
  ans = max(ans, cur);
}

void rank_fours() {
  int cur = 0;
  for (int i = 0; i < 5; i++) if (A[i] == 4) cur += 4;
  ans = max(ans, cur);
}

void rank_fives() {
  int cur = 0;
  for (int i = 0; i < 5; i++) if (A[i] == 5) cur += 5;
  ans = max(ans, cur);
}

void rank_sixes() {
  int cur = 0;
  for (int i = 0; i < 5; i++) if (A[i] == 6) cur += 6;
  ans = max(ans, cur);
}

void rank_four_of_a_kind() {
  map<int, int> t;
  for (int i = 0; i < 5; i++) t[A[i]]++;
  for (auto& [k, v] : t) {
    if (v >= 4) ans = max(ans, k * 4);
  }
}

void rank_full_house() {
  map<int, int> t; int sum = 0;
  for (int i = 0; i < 5; i++) t[A[i]]++, sum += A[i];
  for (auto& [k, v] : t) {
    if (t.size() == 2 && (v == 2 || v == 3)) ans = max(ans, sum);
  }
}

void rank_little_straight() {
  set<int> t;
  for (int i = 0; i < 5; i++) t.insert(A[i]);
  if (t.size() == 5 && t.count(1) && t.count(2) && t.count(3) && t.count(4) && t.count(5)) ans = max(ans, 30);
}

void rank_big_straight() {
  set<int> t;
  for (int i = 0; i < 5; i++) t.insert(A[i]);
  if (t.size() == 5 && t.count(2) && t.count(3) && t.count(4) && t.count(5) && t.count(6)) ans = max(ans, 30);
}

void rank_yacht() {
  map<int, int> t;
  for (int i = 0; i < 5; i++) t[A[i]]++;
  for (auto& [k, v] : t) {
    if (v == 5) ans = max(ans, 50);
  }
}

void rank_choice() {
  int sum = 0;
  for (int i = 0; i < 5; i++) sum += A[i];
  ans = max(ans, sum);
}

void solve() {
  string S;
  cin >> S >> A[0] >> A[1] >> A[2];

  for (A[3] = 1; A[3] <= 6; A[3]++) for (A[4] = 1; A[4] <= 6; A[4]++) {
    if (S[0] == 'Y') rank_ones();
    if (S[1] == 'Y') rank_twos();
    if (S[2] == 'Y') rank_threes();
    if (S[3] == 'Y') rank_fours();
    if (S[4] == 'Y') rank_fives();
    if (S[5] == 'Y') rank_sixes();
    if (S[6] == 'Y') rank_four_of_a_kind();
    if (S[7] == 'Y') rank_full_house();
    if (S[8] == 'Y') rank_little_straight();
    if (S[9] == 'Y') rank_big_straight();
    if (S[10] == 'Y') rank_yacht();
    if (S[11] == 'Y') rank_choice();
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
