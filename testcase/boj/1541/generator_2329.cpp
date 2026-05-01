#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters:
    // number of numbers in expression (terms)
    int terms = rnd.next(2, 8);
    // probability to pick '-' versus '+'
    double minus_prob = rnd.next(0.0, 1.0);
    // maximum digits per number
    int max_digits = rnd.next(1, 5);

    vector<string> nums;
    vector<char> ops;

    // generate each number (allow leading zeros)
    for (int i = 0; i < terms; i++) {
        int len = rnd.next(1, max_digits);
        string s;
        for (int j = 0; j < len; j++) {
            // each digit 0-9
            s += char('0' + rnd.next(0, 9));
        }
        nums.push_back(s);
    }

    // generate operators between numbers
    for (int i = 0; i < terms - 1; i++) {
        // choose '-' with minus_prob, else '+'
        char op = (rnd.next() < minus_prob ? '-' : '+');
        ops.push_back(op);
    }

    // build the expression and ensure it's <= 50 chars
    string expr;
    for (int i = 0; i < terms; i++) {
        expr += nums[i];
        if (i < terms - 1) expr += ops[i];
    }
    // if expression is too long, truncate number of terms
    if ((int)expr.size() > 50) {
        // recompute with fewer terms
        terms = rnd.next(2, 5);
        nums.clear();
        ops.clear();
        for (int i = 0; i < terms; i++) {
            int len = rnd.next(1, max_digits);
            string s;
            for (int j = 0; j < len; j++) {
                s += char('0' + rnd.next(0, 9));
            }
            nums.push_back(s);
        }
        for (int i = 0; i < terms - 1; i++) {
            char op = (rnd.next() < minus_prob ? '-' : '+');
            ops.push_back(op);
        }
        expr.clear();
        for (int i = 0; i < terms; i++) {
            expr += nums[i];
            if (i < terms - 1) expr += ops[i];
        }
    }

    // output single test case
    println(expr);
    return 0;
}
