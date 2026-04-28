#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct Item {
  bool is_num;
  string content;

  bool operator<(const Item& other) const {
    if (is_num != other.is_num) return is_num;
    if (is_num) {
      if (content.size() != other.content.size()) return content.size() < other.content.size();
      for (int i = 0; i < content.size(); ++i) {
        if (content[i] != other.content[i]) return content[i] < other.content[i];
      }
      return false;
    } else {
      return content < other.content;
    }
  }
};

void print(vector<Item>& v) {
  for (Item& item : v) {
    cout << item.content << ' ';
  }
  cout << '\n';
}

bool is_less(vector<Item>& a, vector<Item>& b) {
  for (int i = 0; i < a.size(); ++i) {
    if (i == b.size()) return false;
    if (a[i] < b[i]) return true;
    if (b[i] < a[i]) return false;
  }
  return a.size() < b.size();
}

vector<Item> to_item_v(string& s) {
  int flag = 0; string digits;
  vector<Item> res;
  for (char c : s) {
    if (isdigit(c)) {
      if (flag == 0) flag = 1;
      digits += c;
    } else {
      if (flag == 1) {
        flag = 0;
        res.push_back({true, digits});
        digits.clear();
      }
      res.push_back({false, string(1, c)});
    }
  }
  if (flag == 1) res.push_back({true, digits});
  return res;
}

void solve() {
  int N; string S0; cin >> N >> S0;
  auto V0 = to_item_v(S0);
  // print(V0);

  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    auto V = to_item_v(S);
    // print(V);

    if (is_less(V, V0)) cout << "-\n";
    else cout << "+\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
