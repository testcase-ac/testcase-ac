#include <bits/stdc++.h>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  queue<int> q;
	int n; cin >> n;
  while (n--) {
    char op[6]; int x;
    cin >> op;
    if (!strcmp(op, "push")) {
      cin >> x;
      q.push(x);
    }
    else if (!strcmp(op, "pop")) {
      if (q.empty()) cout << "-1\n";
      else {
        cout << q.front() << '\n';
        q.pop();
      }
    }
    else if (!strcmp(op, "size")) {
      cout << q.size() << '\n';
    }
    else if (!strcmp(op, "empty")) {
      if (q.empty()) cout << "1\n";
      else cout << "0\n";
    }
    else if (!strcmp(op, "front")) {
      if (q.empty()) cout << "-1\n";
      else cout << q.front() << '\n';
    }
    else if (!strcmp(op, "back")) {
      if (q.empty()) cout << "-1\n";
      else cout << q.back() << '\n';
    }
  }
}
