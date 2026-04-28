#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int used[MAX + 1];

priority_queue<int, vector<int>, greater<int>> pq_min;
stack<int> s1;

priority_queue<int, vector<int>, less<int>> pq_max;
queue<int> s2;

int pop_from_s1() {
  while (!s1.empty()) {
    int t = s1.top(); s1.pop();
    if (used[t]) continue;
    used[t] = 1; return t;
  }
  while (!pq_min.empty()) {
    int t = pq_min.top(); pq_min.pop();
    if (used[t]) continue;
    used[t] = 1; return t;
  }
  return -1;
}

int pop_from_s2() {
  while (!pq_max.empty()) {
    int t = pq_max.top(); pq_max.pop();
    if (used[t]) continue;
    used[t] = 1; return t;
  }
  while (!s2.empty()) {
    int t = s2.front(); s2.pop();
    if (used[t]) continue;
    used[t] = 1; return t;
  }
  return -1;
}

void insert_to_s1(int x) {
  s1.push(x);
}

void insert_to_s2(int x) {
  s2.push(x);
}

void rearrange_s1() {
  while (!s1.empty()) {
    int t = s1.top(); s1.pop();
    pq_min.push(t);
  }
}

void rearrange_s2() {
  while (!s2.empty()) {
    int t = s2.front(); s2.pop();
    pq_max.push(t);
  }
}

void solve() {
  int N, Q; cin >> N >> Q;

  int f = 1;
  while (Q--) {
    int op; cin >> op;
    if (op == 0) {
      int x; cin >> x;
      insert_to_s1(x);
      insert_to_s2(x);
    }
    if (op == 1) {
      rearrange_s1();
      rearrange_s2();
    }
    if (op == 2) {
      f = 1 - f;
    }
    if (op == 3) {
      if (f) cout << pop_from_s1() << '\n';
      else cout << pop_from_s2() << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
