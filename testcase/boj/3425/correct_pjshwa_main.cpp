#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9;

int main() {
  fast_io();

  string op;
  while (1) {
    vector<pair<string, ll>> ops;

    while (1) {
      cin >> op;
      if (op == "QUIT") return 0;
      if (op == "END") break;

      int x = -1;
      if (op == "NUM") cin >> x;
      ops.emplace_back(op, x);
    }

    int q;
    cin >> q;
    while (q--) {
      ll n;
      cin >> n;

      stack<ll> nums;
      nums.push(n);

      bool error = false;

      for (auto& [op, x] : ops) {
        if (op == "NUM") nums.push(x);
        if (op == "POP") {
          if (nums.empty()) {
            error = true;
            break;
          }
          nums.pop();
        }
        if (op == "INV") {
          if (nums.empty()) {
            error = true;
            break;
          }
          ll cur = nums.top();
          nums.pop();
          nums.push(-cur);
        }
        if (op == "DUP") {
          if (nums.empty()) {
            error = true;
            break;
          }
          nums.push(nums.top());
        }
        if (op == "SWP") {
          if (nums.size() < 2) {
            error = true;
            break;
          }
          ll c1 = nums.top();
          nums.pop();
          ll c2 = nums.top();
          nums.pop();
          nums.push(c1);
          nums.push(c2);
        }
        if (op == "ADD") {
          if (nums.size() < 2) {
            error = true;
            break;
          }
          ll c1 = nums.top();
          nums.pop();
          ll c2 = nums.top();
          nums.pop();
          if (abs(c1 + c2) > INF) {
            error = true;
            break;
          }
          nums.push(c1 + c2);
        }
        if (op == "SUB") {
          if (nums.size() < 2) {
            error = true;
            break;
          }
          ll c1 = nums.top();
          nums.pop();
          ll c2 = nums.top();
          nums.pop();
          if (abs(c2 - c1) > INF) {
            error = true;
            break;
          }
          nums.push(c2 - c1);
        }
        if (op == "MUL") {
          if (nums.size() < 2) {
            error = true;
            break;
          }
          ll c1 = nums.top();
          nums.pop();
          ll c2 = nums.top();
          nums.pop();
          if (abs(c1 * c2) > INF) {
            error = true;
            break;
          }
          nums.push(c1 * c2);
        }
        if (op == "DIV") {
          if (nums.size() < 2) {
            error = true;
            break;
          }
          ll c1 = nums.top();
          nums.pop();
          ll c2 = nums.top();
          nums.pop();
          if (c1 == 0) {
            error = true;
            break;
          }
          bool neg1 = c1 < 0, neg2 = c2 < 0;
          ll res = abs(c2) / abs(c1);
          if (neg1 ^ neg2) res = -res;
          if (abs(res) > INF) {
            error = true;
            break;
          }
          nums.push(res);
        }
        if (op == "MOD") {
          if (nums.size() < 2) {
            error = true;
            break;
          }
          ll c1 = nums.top();
          nums.pop();
          ll c2 = nums.top();
          nums.pop();
          if (c1 == 0) {
            error = true;
            break;
          }
          bool neg = c2 < 0;
          ll res = abs(c2) % abs(c1);
          if (neg) res = -res;
          if (abs(res) > INF) {
            error = true;
            break;
          }
          nums.push(res);
        }
      }

      if (nums.size() != 1) error = true;

      if (error) cout << "ERROR\n";
      else cout << nums.top() << '\n';
    }

    cout << '\n';
  }

}
