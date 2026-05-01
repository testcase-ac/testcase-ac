#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;
using i64 = long long;

constexpr int floor_div(int a, int b) {
    return (a > 0 == b > 0) ? a/b : (a - b + 1)/b;
}

struct BigInt {
    // Uses base 10.
    // Front is LSB, back is MSB (reverse to writing order)
    // It may contain one -1 at the very back, indicating the number is negative
    // for example, v = [0, 1, 2, 3, -1] represents the value -10000 + 3000 + 200 + 10 + 0 = -6970
    vector<int> v;

    static BigInt from_str(const string& s) {
        bool is_neg = s[0] == '-';
        BigInt res { vector<int>(s.size() - is_neg) };
        for (int i = 0; i < s.size() - is_neg; i++) {
            res.v[i] = s[s.size()-1 - i] - '0';
        }
        res.normalize();
        return is_neg ? res * from_int(-1) : res;
    }

    static BigInt from_int(int i) {
        BigInt res { { i } };
        res.normalize();
        return res;
    }

    string to_str() {
        bool neg = is_neg();
        BigInt b = abs();

        string res;
        res.resize(b.v.size() + neg);
        for (int i = 0; i < b.v.size(); i++) {
            res[i + neg] = b.v[b.v.size()-1 - i] + '0';
        }
        if (neg) { res[0] = '-'; }
        return res;
    }

    bool is_neg() const { return v.back() < 0; }

    void normalize() {
        for (int i = 0; i < v.size()-1; i++) {
            int carry = floor_div(v[i], 10);
            v[i+1] += carry;
            v[i] -= 10*carry;
        }

        while (v.back() <= -2 || v.back() >= 10) {
            int carry = floor_div(v.back(), 10);
            v.push_back(carry);
            v[v.size()-2] -= 10*carry;
        }
        
        while (v.size() >= 2 && v.back() == 0) { v.pop_back(); }
    }

    BigInt abs() const {
        return is_neg() ? *this * from_int(-1) : *this;
    }

    BigInt operator+(const BigInt& rhs) const {
        BigInt res { vector<int>(max(v.size(), rhs.v.size())) };
        for (int i = 0; i < res.v.size(); i++) {
            int a = i < v.size() ? v[i] : 0;
            int b = i < rhs.v.size() ? rhs.v[i] : 0;
            res.v[i] = a + b;
        }
        res.normalize();
        return res;
    }

    BigInt operator-(const BigInt& rhs) const {
        BigInt res { vector<int>(max(v.size(), rhs.v.size())) };
        for (int i = 0; i < res.v.size(); i++) {
            int a = i < v.size() ? v[i] : 0;
            int b = i < rhs.v.size() ? rhs.v[i] : 0;
            res.v[i] = a - b;
        }
        res.normalize();
        return res;
    }

    BigInt operator*(const BigInt& rhs) const {
        BigInt res { vector<int>(v.size() + rhs.v.size() - 1) };

        int lv_nzcnt = v.size() - count(v.begin(), v.end(), 0);
        int rv_nzcnt = rhs.v.size() - count(rhs.v.begin(), rhs.v.end(), 0);

        // this optimization is necessary for O(NM) division
        auto* lv_ptr = &v;
        auto* rv_ptr = &rhs.v;
        if (lv_nzcnt > rv_nzcnt) { swap(lv_ptr, rv_ptr); }
        auto& lv = *lv_ptr;
        auto& rv = *rv_ptr;

        for (int i = 0; i < lv.size(); i++) {
            if (lv[i] == 0) { continue; }
            for (int j = 0; j < rv.size(); j++) {
                res.v[i+j] += lv[i]*rv[j];
            }
        }
        res.normalize();
        return res;
    }

    BigInt operator/(const BigInt& rhs) const {
        BigInt labs = abs();
        BigInt rabs = rhs.abs();

        if (is_neg() != rhs.is_neg()) {
            // floor(-a/b) = -ceil(a/b) for positive integers a and b
            return ((labs + rabs - from_int(1)) / rabs) * from_int(-1);
        }
        
        BigInt labs_rem = labs;
        BigInt res { vector<int>(max(1ll, i64(labs.v.size()) - i64(rabs.v.size()) + 1)) }; // unsigned overflow smh
        
        for (int i = res.v.size()-1; i >= 0; i--) {
            // long division
            BigInt p10 { vector<int>(i+1) };
            for (int d = 9; d >= 1; d--) {
                p10.v[i] = d;
                BigInt b = p10 * rabs; // p10 is extremely sparse, so this multiplication is O(M)
                if (labs_rem < b) { continue; }
                res.v[i] = d;
                labs_rem = labs_rem - b;
                break;
            }
        }

        res.normalize();
        return res;
    }

    bool operator<(const BigInt& rhs) {
        // different signs
        if (is_neg() != rhs.is_neg()) { return is_neg(); }
        
        // same signs
        if (!is_neg()) {
            if (v.size() != rhs.v.size()) { return v.size() < rhs.v.size(); }
            for (int i = v.size()-1; i >= 0; i--) {
                if (v[i] != rhs.v[i]) { return v[i] < rhs.v[i]; }
            }
            return false;
        } else {
            BigInt labs = abs();
            BigInt rabs = rhs.abs();
            if (labs.v.size() != rabs.v.size()) { return labs.v.size() > rabs.v.size(); }
            for (int i = v.size()-1; i >= 0; i--) {
                if (labs.v[i] != rabs.v[i]) { return labs.v[i] > rabs.v[i]; }
            }
            return false;
        }
    }

    bool is_zero() const { return v.back() == 0; } // The only representation of zero is v=[0] upon normalization
};

void error() {
    cout << "ROCK" << "\n";
    exit(0);
}

constexpr bool is_op(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
constexpr bool is_digit(char ch) {
    return '0' <= ch && ch <= '9';
}

constexpr int prec(char op) {
    switch (op) {
        case '+': return 0;
        case '-': return 0;
        case '*': return 1;
        case '/': return 1;
    }
    assert(false);
}
BigInt apply_op(const BigInt& lhs, char op, const BigInt& rhs) {
    switch (op) {
        case '+': return lhs + rhs;
        case '-': return lhs - rhs;
        case '*': return lhs * rhs;
        case '/':
            if (rhs.is_zero()) { error(); }
            return lhs / rhs;
    }
    assert(false);
}

string expr;
pair<BigInt, int> eval(int head) {
    int n = expr.size();
    
    int begin = head;

    auto read_operand = [&](int i) {
        if (expr[i] == '(') {
            auto [res, end] = eval(head+1);
            return pair { res, end+1 };
        } else {
            int cur = head;
            while (cur < n && is_digit(expr[cur])) { cur++; }
            return pair { BigInt::from_str(expr.substr(head, cur-head)), cur };
        }
    };

    vector<BigInt> st_num;
    vector<char> st_op;

    auto eval_stack = [&](int nxt_prec) {
        assert(st_num.size() == st_op.size()+1);

        int left = st_op.size() - 1;
        int cur_prec;
        while (left >= 0 && (cur_prec = prec(st_op[left])) > nxt_prec) {
            while (left >= 0 && prec(st_op[left]) == cur_prec) { left--; }
            left++;
            BigInt val = st_num[left];
            for (int i = left; i < st_op.size(); i++) {
                val = apply_op(val, st_op[i], st_num[i+1]);
            }
            st_num.resize(left+1);
            st_num[left] = val;
            st_op.resize(left);
            left--;
        }
    };

    bool prev_op = true;
    while (true) {
        if (head >= n) {
            if (begin != 0) { error(); }
            break;
        }

        if (expr[head] == ')') {
            if (begin == 0) { error(); }
            break;
        } else if (is_op(expr[head])) {
            if (prev_op) { error(); }
            int nxt_prec = prec(expr[head]);
            eval_stack(nxt_prec);
            st_op.push_back(expr[head++]);
            prev_op = true;
        } else {
            if (!prev_op) { error(); }
            auto [val, nhead] = read_operand(head);
            head = nhead;
            st_num.push_back(move(val));
            prev_op = false;
        }
    }

    if (prev_op) { error(); }
    eval_stack(-1);

    return { st_num[0], head };
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> expr;
    cout << eval(0).first.to_str() << "\n";

    return 0;
}
