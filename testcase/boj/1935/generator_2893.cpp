#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N;
vector<double> vals;

// Generate a random postfix expression with k operators
vector<char> gen_postfix(int k) {
    // returns a valid postfix expression with k binary operators and k+1 operands
    if (k == 0) {
        // single operand
        char c = char('A' + rnd.next(0, N-1));
        return vector<char>(1, c);
    }
    // split operators between left and right subtrees
    int t = rnd.next(-1, 1);
    int left_ops = rnd.wnext(k, t) % k; // ensure 0 <= left_ops < k
    int right_ops = k - 1 - left_ops;
    auto L = gen_postfix(left_ops);
    auto R = gen_postfix(right_ops);
    // pick an operator with random weights
    vector<int> w = {rnd.next(1,10), rnd.next(1,10), rnd.next(1,10), rnd.next(1,10)};
    int sumw = w[0]+w[1]+w[2]+w[3];
    int pick = rnd.next(1, sumw);
    char op;
    if (pick <= w[0]) op = '+';
    else if (pick <= w[0]+w[1]) op = '-';
    else if (pick <= w[0]+w[1]+w[2]) op = '*';
    else op = '/';
    vector<char> res;
    res.reserve(L.size()+R.size()+1);
    res.insert(res.end(), L.begin(), L.end());
    res.insert(res.end(), R.begin(), R.end());
    res.push_back(op);
    return res;
}

// Evaluate postfix and check constraints
bool check_expr(const vector<char>& expr) {
    vector<double> st;
    st.reserve(expr.size());
    for (char c : expr) {
        if (c >= 'A' && c <= 'Z') {
            double v = vals[c - 'A'];
            st.push_back(v);
        } else {
            if ((int)st.size() < 2) return false;
            double b = st.back(); st.pop_back();
            double a = st.back(); st.pop_back();
            if (c == '/' && fabs(b) < 1e-12) return false;
            double r = 0;
            if (c == '+') r = a + b;
            else if (c == '-') r = a - b;
            else if (c == '*') r = a * b;
            else if (c == '/') r = a / b;
            if (r < -2e9 || r > 2e9) return false;
            st.push_back(r);
        }
    }
    return st.size() == 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // choose N
    N = rnd.next(1, min(6, 26));
    // assign values 1..100 to avoid zero-divide
    vals.resize(N);
    for (int i = 0; i < N; i++) {
        vals[i] = rnd.next(1, 100);
    }

    // try generating until valid constraints
    vector<char> expr;
    while (true) {
        // number of operators k in [0..7] with varied bias
        int bias = rnd.next(-2, 2);
        int k = rnd.wnext(8, bias);
        expr = gen_postfix(k);
        if ((int)expr.size() > 100) continue;
        if (check_expr(expr)) break;
    }

    // output
    println(N);
    // print expression as string
    string s(expr.begin(), expr.end());
    printf("%s\n", s.c_str());
    // print values for A, B, ...
    for (int i = 0; i < N; i++) {
        println((int)vals[i]);
    }
    return 0;
}
