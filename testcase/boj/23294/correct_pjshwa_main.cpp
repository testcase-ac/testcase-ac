#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int cap[MAX + 1];

int main() {
  fast_io();

  int n, q, c;
  cin >> n >> q >> c;
  for (int i = 1; i <= n; i++) {
    cin >> cap[i];
  }

  deque<int> bw, fw;
  int cur = -1, cache = 0;

  while (q--) {
    string op;
    cin >> op;

    if (op == "B") {
      if (bw.size()) {
        int lst = bw.front();
        bw.pop_front();
        fw.push_back(cur);
        cur = lst;
      }
    }
    if (op == "F") {
      if (fw.size()) {
        int lst = fw.back();
        fw.pop_back();
        bw.push_front(cur);
        cur = lst;
      }
    }
    if (op == "A") {
      int nxt;
      cin >> nxt;
      cache += cap[nxt];

      while (!fw.empty()) {
        cache -= cap[fw.back()];
        fw.pop_back();
      }

      if (cur != -1) bw.push_front(cur);
      cur = nxt;

      while (cache > c) {
        cache -= cap[bw.back()];
        bw.pop_back();
      }
    }
    if (op == "C") {
      stack<int> t;
      while (!bw.empty()) {
        if (t.empty() || t.top() != bw.front()) t.push(bw.front());
        cache -= cap[bw.front()];
        bw.pop_front();
      }
      while (!t.empty()) {
        bw.push_front(t.top());
        cache += cap[t.top()];
        t.pop();
      }
    }

  }

  cout << cur << '\n';
  if (bw.size()) {
    while (!bw.empty()) {
      cout << bw.front() << ' ';
      bw.pop_front();
    }
    cout << '\n';
  }
  else cout << "-1\n";
  if (fw.size()) {
    while (!fw.empty()) {
      cout << fw.back() << ' ';
      fw.pop_back();
    }
    cout << '\n';
  }
  else cout << "-1\n";
}
