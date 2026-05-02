/**
 *    author:  tourist
 *    created: 08.08.2020 18:25:58       
**/
#undef _GLIBCXX_DEBUG

#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int Decode(char c) {
  if (c >= '0' && c <= '9') {
    return (int) (c - '0');
  }
  return 10 + (int) (c - 'A');
}

int Decode(const string& s) {
  int v = 0;
  for (char c : s) {
    v = v * 16 + Decode(c);
  }
  return v;
}

struct Test {
  int d;
  vector<int> L;
  int S;
  int E;
};

const int MAXD = 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  vector<Test> tests(tt);
  vector<vector<int>> for_d(MAXD + 1);
  for (auto& test : tests) {
    int n;
    cin >> n >> test.d;
    assert(test.d <= MAXD);
    string sS, sE;
    cin >> sS >> sE;
    test.S = Decode(sS);
    test.E = Decode(sE);
    test.L.resize(n);
    for (int i = 0; i < n; i++) {
      string foo;
      cin >> foo;
      test.L[i] = Decode(foo);
    }
    for_d[test.d].push_back(test.S);
    for_d[test.d].push_back(test.E + 1);
  }
  vector<map<vector<int>, vector<long long>>> mp(MAXD + 1);
  for (int d = 2; d <= MAXD; d++) {
    vector<vector<int>> all;
    vector<int> a(d, 2);
    vector<int> b;
    function<void(int)> Dfs = [&](int last) {
      if (*max_element(a.begin(), a.end()) == 0) {
        all.push_back(b);
        return;
      }
      if (last == 0) {
        return;
      }
      bool ok = true;
      {
        int aux = last;
        for (int i = d - 1; i >= 0; i--) {
          int cur = aux % 3;
          if (cur > a[i]) {
            ok = false;
            break;
          }
          aux /= 3;
        }
      }
      if (ok) {
        int aux = last;
        int num = 0;
        int p16 = 1;
        for (int i = d - 1; i >= 0; i--) {
          int cur = aux % 3;
          a[i] -= cur;
          num += cur * p16;
          p16 *= 16;
          aux /= 3;
        }
        b.push_back(num);
        Dfs(last);
        b.pop_back();
        aux = last;
        for (int i = d - 1; i >= 0; i--) {
          int cur = aux % 3;
          a[i] += cur;
          aux /= 3;
        }
      }
      Dfs(last - 1);
    };
    int p3 = 1;
    for (int i = 0; i < d; i++) {
      p3 *= 3;
    }
    Dfs(p3 - 1);
    auto& bounds = for_d[d];
    if (bounds.empty()) {
      continue;
    }
    sort(bounds.begin(), bounds.end());
    bounds.resize(unique(bounds.begin(), bounds.end()) - bounds.begin());
    int nbounds = (int) bounds.size();
    int p16 = 1;
    for (int i = 0; i < d; i++) {
      p16 *= 16;
    }
    for (auto& vec : all) {
      int sz = (int) vec.size();
      vector<int> suf_sum(sz + 1, 0);
      for (int i = sz - 1; i >= 0; i--) {
        suf_sum[i] = suf_sum[i + 1] + vec[i];
      }
      vector<long long> suf_prod(sz + 1, 1);
      for (int i = 16 - sz; i >= 1; i--) {
        suf_prod[sz] *= i;
      }
      for (int i = sz - 1; i >= 0; i--) {
        suf_prod[i] = suf_prod[i + 1] * (16 - i);
      }
      vector<long long> ways(nbounds + 1, 0);
      vector<bool> used(16, false);
      function<void(int, int)> Solve = [&](int pos, int sum) {
        int at = (int) (upper_bound(bounds.begin(), bounds.end(), sum) - bounds.begin());
        int nxt = (at == nbounds ? bounds[0] + p16 : bounds[at]);
        int go_to = nxt - sum;
        int rem = suf_sum[pos] * 15;
        if (rem < go_to) {
          ways[at] += suf_prod[pos];
          return;
        }
        assert(pos < sz);
        for (int coeff = 0; coeff < 16; coeff++) {
          if (used[coeff]) {
            continue;
          }
          used[coeff] = true;
          Solve(pos + 1, (sum + vec[pos] * coeff) % p16);
          used[coeff] = false;
        }
      };
      Solve(0, 0);
      mp[d][vec] = ways;
    }
  }
  long long f16 = 1;
  for (int i = 1; i <= 16; i++) {
    f16 *= i;
  }
  debug(clock());
  for (int qq = 0; qq < tt; qq++) {
    cout << "Case #" << qq + 1 << ": ";
    auto& test = tests[qq];
    int n = (int) test.L.size();
    auto& bounds = for_d[test.d];
    int nbounds = (int) bounds.size();
    int real_p16 = 1;
    for (int i = 0; i < test.d; i++) {
      real_p16 *= 16;
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        vector<int> vec(16);
        for (int rot = 0; rot < 2; rot++) {
          int x = test.L[rot == 0 ? i : j];
          int p16 = 1;
          for (int iter = 0; iter < test.d; iter++) {
            vec[x % 16] += p16;
            p16 *= 16;
            x /= 16;
          }
        }
        sort(vec.rbegin(), vec.rend());
        while (vec.back() == 0) {
          vec.pop_back();
        }
        auto it = mp[test.d].find(vec);
        assert(it != mp[test.d].end());
        auto& ways = it->second;
        for (int i = 0; i <= nbounds; i++) {
          int from = (i == 0 ? 0 : bounds[i - 1]);
          int to = (i == nbounds ? real_p16 - 1 : bounds[i] - 1);
          if (test.S <= from && to <= test.E) {
            ans += ways[i];
          }
        }
      }
    }
    long long num = ans;
    long long den = f16 * n * (n - 1) / 2;
    long long g = __gcd(num, den);
    num /= g;
    den /= g;
    cout << num << " " << den << '\n';
  }
  debug(clock());
  return 0;
}
