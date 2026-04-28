#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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

const int MAX = 1000;
bool A[MAX + 1];
int N;

void solve() {
  string S;
  cin >> S;

  memset(A, 0, sizeof(A));
  for (auto& chunk : split(S, ",")) {
    auto tokens = split(chunk, "-");
    if (tokens.size() == 1) {
      int page = stoi(tokens[0]);
      if (1 <= page && page <= N) A[page] = true;
    }
    else {
      int low = stoi(tokens[0]), high = stoi(tokens[1]);
      for (int i = low; i <= min(N, high); i++) A[i] = true;
    }
  }

  cout << accumulate(A, A + N + 1, 0) << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
