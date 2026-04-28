#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  deque<int> d;
  int n, x;
  char op[11];
  cin >> n;

  while (n--) {
    cin >> op;
    if (!strcmp(op, "push_front")) {
      cin >> x;
      d.push_front(x);
    }
    else if (!strcmp(op, "push_back")) {
      cin >> x;
      d.push_back(x);
    }
    else if (!strcmp(op, "pop_front")) {
      if (d.empty()) cout << "-1\n";
      else {
        cout << d.front() << '\n';
        d.pop_front();
      }
    }
    else if (!strcmp(op, "pop_back")) {
      if (d.empty()) cout << "-1\n";
      else {
        cout << d.back() << '\n';
        d.pop_back();
      }
    }
    else if (!strcmp(op, "size")) {
      cout << d.size() << '\n';
    }
    else if (!strcmp(op, "empty")) {
      if (d.empty()) cout << "1\n";
      else cout << "0\n";
    }
    else if (!strcmp(op, "front")) {
      if (d.empty()) cout << "-1\n";
      else cout << d.front() << '\n';
    }
    else if (!strcmp(op, "back")) {
      if (d.empty()) cout << "-1\n";
      else cout << d.back() << '\n';
    }
  }
}
