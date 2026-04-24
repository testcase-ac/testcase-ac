#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<char> possibles = {'0', '1', '*', '-', '+', '(', ')', '='};
/*
Q ::= E=E
E ::= T | E+T | E-T
T ::= F | T*F
F ::= N | -F | (E)
N ::= 0 | 1B
B ::= ε | 0B | 1B
*/
struct result {
    int val;
    bool ok;

    result operator+(const result &rhs) const {
        return {val + rhs.val, ok && rhs.ok};
    }
    result operator-(const result &rhs) const {
        return {val - rhs.val, ok && rhs.ok};
    }
    result operator*(const result &rhs) const {
        return {val * rhs.val, ok && rhs.ok};
    }
};
result parse_e(string s);
result parse_n(string s) {
    if(s.empty()) {
        return {0, false};
    }
    if(s == "0") {
        return {0, true};
    }
    if(s[0] == '0') {
        return {0, false};
    }
    int res = 0;
    for(int i=0; i<s.size(); i++) {
        res <<= 1;
        res += s[i] - '0';
        if(s[i] != '0' && s[i] != '1') {
            return {0, false};
        } 
    }
    return {res, true};
}
result parse_f(string s) {
    if(s[0] == '-') {
        result res = parse_f(s.substr(1));
        return {-res.val, res.ok};
    } else if(s.size() > 2 && s[0] == '(' && s[s.size()-1] == ')')  {
        return parse_e(s.substr(1, s.size()-2));
    } else {
        return parse_n(s);
    }
}
vector<int> find_op(string s, char op) {
    vector<int> ret;
    int cnt = 0;
    for(int i=0; i<s.size(); i++) {
        if(s[i] == '(') {
            cnt++;
        } else if(s[i] == ')') {
            cnt--;
        } else if(cnt == 0 && (s[i] == op)) {
            ret.push_back(i);
        }
    }
    return ret;
}
result parse_t(string s) {
    vector<int> idxs;
    result res = parse_f(s);
    if(res.ok) {
        return res;
    }
    idxs = find_op(s, '*');
    for(int idx: idxs) {
        result res = parse_t(s.substr(0, idx)) * parse_f(s.substr(idx+1));
        if(res.ok) {
            return res;
        }
    }
    return {0, false};
}

result parse_e(string s) {
    vector<int> idxs;
    result res = parse_t(s);
    if(res.ok) {
        return res;
    }
    idxs = find_op(s, '+');
    for(int idx: idxs) {
        result res = parse_e(s.substr(0, idx)) + parse_t(s.substr(idx+1));
        if(res.ok) {
            return res;
        }
    }
    idxs = find_op(s, '-');
    for(int idx: idxs) {
        result res = parse_e(s.substr(0, idx)) - parse_t(s.substr(idx+1));
        if(res.ok) {
            return res;
        }
    }
    return {0, false};
}

bool parse_q(string s) {
    int idx = s.find('=');
    if(idx == string::npos) return false;
    result lhs = parse_e(s.substr(0, idx));
    result rhs = parse_e(s.substr(idx+1));
    return lhs.ok && rhs.ok && lhs.val == rhs.val;
}

int32_t main() {
    // string chk = "1+10*10+1-(1+1)";
    // printf("%d %d", parse_e(chk).val, parse_e(chk).ok);
    // return 0;
    cin.tie(0)->sync_with_stdio(0);
    string inp;
    cin >> inp;
    vector<char> to_replace(inp.begin(), inp.end());
    auto it = remove_if(to_replace.begin(), to_replace.end(), 
            [](char c) { 
                return find(possibles.begin(), possibles.end(), c) != possibles.end(); 
            }
    );
    to_replace.erase(it, to_replace.end());
    sort(to_replace.begin(), to_replace.end());
    to_replace.erase(unique(to_replace.begin(), to_replace.end()), to_replace.end());
    if(to_replace.size() > 8) {
        return !(cout << 0);
    }
    int cnt = 0;
    sort(possibles.begin(), possibles.end());
    do {
        string s = inp;
        for(char &c: s) {
            int idx = find(to_replace.begin(), to_replace.end(), c) - to_replace.begin();
            if(idx < to_replace.size())
                c = possibles[idx];
        }
        int res = parse_q(s);
        if(res) {
            cnt++;
        }
        reverse(possibles.begin() + to_replace.size(), possibles.end());
    } while(next_permutation(possibles.begin(), possibles.end()));
    cout << cnt;
}
