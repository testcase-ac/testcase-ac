#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
const ll INF = 1e18;
map<string, int> fi;
map<int, string> lead;
int fcount;
int parent[MAX];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
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

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    string S;
    cin >> S >> S >> S;
    fidx(S);

    parent[i] = i;
    lead[i] = S;
  }

  cin.ignore();
  while (M--) {
    string line;
    getline(cin, line);

    auto tokens = split(line, ",");
    string k1 = split(tokens[0], " of ")[1];
    string k2 = split(tokens[1], " of ")[1];
    int x1 = fidx(k1), x2 = fidx(k2);

    // Vassal attacks master
    if (Find(x1) == Find(x2)) {
      if (tokens[2] == "1") lead[Find(x1)] = k1;
      if (tokens[2] == "2") lead[Find(x1)] = k2;
    }
    else {
      string l1 = lead[Find(x1)], l2 = lead[Find(x2)];
      Union(x1, x2);

      if (tokens[2] == "1") lead[Find(x1)] = l1;
      if (tokens[2] == "2") lead[Find(x1)] = l2;
    }
  }

  set<int> groups;
  for (int i = 0; i < N; i++) groups.insert(Find(i));

  set<string> kingdoms;
  for (int group : groups) kingdoms.insert(lead[group]);

  cout << kingdoms.size() << '\n';
  for (auto& k : kingdoms) cout << "Kingdom of " << k << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
