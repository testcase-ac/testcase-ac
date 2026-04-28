#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool ends_w_punct(string& s) {
  return s.back() == '!' || s.back() == '?' || s.back() == ',' || s.back() == '.';
}

bool is_korea(string& s) {
  if (s == "Korea") return true;
  return s.substr(0, 5) == "Korea" && s.size() == 6 && ends_w_punct(s);
}

void capitalize(string& s) {
  s[0] = toupper(s[0]);
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
  string line; int Z;
  getline(cin, line);

  auto tokens = split(line, " "); Z = tokens.size();
  vector<string> rule_2_applied;

  // Rule 2
  // 단어 'of'와 'Korea'는 대문자와 소문자를 구분한다.
  // 단어 'of' 직전에 나오는 단어의 첫 글자가 소문자일 경우 대문자로 변환한다.
  // 이 규칙을 여러 번 연달아 적용할 수 있는 경우 앞에서부터 적용한다.
  // 단어 'of' 뒤에 문장 부호가 붙어 있는 경우 이 규칙을 적용할 수 없다.
  // 단어 'of' 앞에 단어가 없거나, 단어 'of' 직전에 나오는 단어에 문장 부호가 붙어 있는 경우 이 규칙을 적용할 수 없다.
  // 단어 'Korea' 뒤에 문장 부호가 붙어있는 경우, 단어 'Korea' 뒤의 문장 부호를 단어 'of' 직전에 나오는 단어 뒤에 붙인다.
  for (int i = 0; i < Z; ++i) {
    rule_2_applied.push_back(tokens[i]);

    if (i == 0 || i == Z - 1) continue;
    if (tokens[i] != "of") continue;
    if (ends_w_punct(tokens[i - 1])) continue;
    if (!is_korea(tokens[i + 1])) continue;

    rule_2_applied.pop_back();
    auto word = rule_2_applied.back(); rule_2_applied.pop_back();
    capitalize(word);

    auto k_word = "K-" + word;
    if (ends_w_punct(tokens[i + 1])) {
      auto punct = tokens[i + 1].back();
      k_word.push_back(punct);
    }
    rule_2_applied.push_back(k_word);
    i += 1;
  }

  Z = rule_2_applied.size();
  vector<string> rule_1_applied;

  // Rule 1
  // 단어 'Korea'는 대문자와 소문자를 구분한다.
  // 단어 'Korea' 다음에 나오는 단어의 첫 글자가 소문자일 경우 대문자로 변환한다.
  // 이 규칙을 여러 번 연달아 적용할 수 있는 경우 뒤에서부터 적용한다.
  // 단어 'Korea' 뒤에 문장 부호가 붙어 있는 경우 이 규칙을 적용할 수 없다.
  for (int i = Z - 1; i >= 0; --i) {
    rule_1_applied.push_back(rule_2_applied[i]);

    if (i == Z - 1) continue;
    if (rule_2_applied[i] != "Korea") continue;

    rule_1_applied.pop_back();
    auto word = rule_1_applied.back(); rule_1_applied.pop_back();
    capitalize(word);

    auto k_word = "K-" + word;
    rule_1_applied.push_back(k_word);
  }

  // Print result
  reverse(rule_1_applied.begin(), rule_1_applied.end());
  for (auto& word : rule_1_applied) cout << word << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t; cin.ignore();
  while (t--) solve();
}
