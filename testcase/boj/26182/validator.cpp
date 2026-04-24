#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read c and d
    int c = inf.readInt(1, 100000, "c");
    inf.readSpace();
    int d = inf.readInt(1, 100000, "d");
    ensuref(c <= d, "Require c <= d, got c=%d, d=%d", c, d);
    inf.readEoln();

    int n = d - c + 1;
    vector<string> t(n);

    // Read the transcript line: n tokens
    for (int i = 0; i < n; i++) {
        t[i] = inf.readToken("[^ ]+", "token");
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // Classify positions and collect constraints
    vector<int> reqA;      // positions x where a must divide x (Fizz or FizzBuzz)
    vector<int> reqB;      // positions x where b must divide x (Buzz or FizzBuzz)
    vector<int> forbA;     // positions x where a must NOT divide x (number or Buzz)
    vector<int> forbB;     // positions x where b must NOT divide x (number or Fizz)

    for (int i = 0; i < n; i++) {
        int x = c + i;
        const string &s = t[i];
        if (s == "Fizz") {
            // a|x, b!|x
            reqA.push_back(x);
            forbB.push_back(x);
        } else if (s == "Buzz") {
            // b|x, a!|x
            reqB.push_back(x);
            forbA.push_back(x);
        } else if (s == "FizzBuzz") {
            // a|x, b|x
            reqA.push_back(x);
            reqB.push_back(x);
        } else {
            // Must be the exact integer x
            // Check digits only
            ensuref(!s.empty(), "Empty token at position %d", i);
            for (char ch : s) {
                ensuref(ch >= '0' && ch <= '9', "Invalid character '%c' in token '%s' at position %d", ch, s.c_str(), i);
            }
            // Must match to_string(x), this enforces no leading zeros and correct value
            string sx = to_string(x);
            ensuref(s == sx, "At position %d expected number '%s' but got '%s'", i, sx.c_str(), s.c_str());
            // and for numbers: both a and b must NOT divide x
            forbA.push_back(x);
            forbB.push_back(x);
        }
    }

    // Compute GCD constraints
    auto compute_gcd = [&](const vector<int>& v) {
        if (v.empty()) return 0;
        int g = v[0];
        for (size_t i = 1; i < v.size(); i++) {
            g = std::gcd(g, v[i]);
        }
        return g;
    };

    int G_a = compute_gcd(reqA);
    int G_b = compute_gcd(reqB);

    // Find a in [1,1e6] satisfying:
    //   if G_a>0, a|G_a; else (no req) we will pick a = d+1
    //   and for every x in forbA, x % a != 0
    const int A_LIMIT = 1000000;
    vector<int> candA;
    if (G_a == 0) {
        // choose a > d so that no x<=d is divisible
        int a0 = d + 1;
        ensuref(a0 <= A_LIMIT, "Cannot choose a=d+1=%d > 1e6", a0);
        candA.push_back(a0);
    } else {
        // enumerate divisors of G_a
        for (int i = 1; (long long)i * i <= G_a; i++) {
            if (G_a % i == 0) {
                if (i <= A_LIMIT) candA.push_back(i);
                int j = G_a / i;
                if (j != i && j <= A_LIMIT) candA.push_back(j);
            }
        }
        ensuref(!candA.empty(), "No divisor of G_a=%d within [1,1e6]", G_a);
    }
    sort(candA.begin(), candA.end());
    candA.erase(unique(candA.begin(), candA.end()), candA.end());

    int foundA = -1;
    for (int a : candA) {
        bool ok = true;
        for (int x : forbA) {
            if (x % a == 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            foundA = a;
            break;
        }
    }
    ensuref(foundA != -1, "No valid a found that satisfies Fizz constraints");

    // Similarly for b
    vector<int> candB;
    if (G_b == 0) {
        int b0 = d + 1;
        ensuref(b0 <= A_LIMIT, "Cannot choose b=d+1=%d > 1e6", b0);
        candB.push_back(b0);
    } else {
        for (int i = 1; (long long)i * i <= G_b; i++) {
            if (G_b % i == 0) {
                if (i <= A_LIMIT) candB.push_back(i);
                int j = G_b / i;
                if (j != i && j <= A_LIMIT) candB.push_back(j);
            }
        }
        ensuref(!candB.empty(), "No divisor of G_b=%d within [1,1e6]", G_b);
    }
    sort(candB.begin(), candB.end());
    candB.erase(unique(candB.begin(), candB.end()), candB.end());

    int foundB = -1;
    for (int b : candB) {
        bool ok = true;
        for (int x : forbB) {
            if (x % b == 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            foundB = b;
            break;
        }
    }
    ensuref(foundB != -1, "No valid b found that satisfies Buzz constraints");

    // All constraints satisfied; just finish validation
    inf.readEof();
    return 0;
}
