#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<string> split(const string &str, const char delimiter) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delimiter, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + 1;
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

bool isCantor(ll nom, ll denom, int trial) {
  if (3 * nom >= denom && 2 * denom > 3 * nom) return false;
  if (trial > 10) return true;

  ll newnom = 3 * nom;
  if (2 * denom <= newnom) newnom -= 2 * denom;
  return isCantor(newnom, denom, trial + 1);
}

int main() {
  fast_io();

  string s;
  while (1) {
    cin >> s;
    if (s == "0" || s == "1") {
      cout << "MEMBER\n";
      continue;
    }
    if (s == "END") break;

    string rems = split(s, '.')[1];
    ll denom = lpow(10, rems.size(), 1e18);
    cout << (isCantor(stoll(rems), denom, 0) ? "MEMBER" : "NON-MEMBER") << '\n';
  }

}
