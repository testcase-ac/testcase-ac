#include "testlib.h"

#include <string>

using namespace std;

string randomParentheses(int n) {
    string s(n, '(');
    for (char& c : s) {
        c = rnd.next(2) == 0 ? '(' : ')';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 24);
        int m = rnd.next(1, 24);
        string a;
        string b;

        if (tc % 4 == 0) {
            a = randomParentheses(n);
            b = randomParentheses(m);
        } else if (tc % 4 == 1) {
            a = string(n, '(');
            b = string(m, ')');
        } else if (tc % 4 == 2) {
            a = randomParentheses(n);
            b = a;
        } else {
            a = string(n, '(');
            b = string(m, '(');
            for (int i = 1; i < n; i += 2) a[i] = ')';
            for (int i = 1; i < m; i += 2) b[i] = ')';
        }

        long long k;
        if (tc % 3 == 0) k = 1;
        else if (tc % 3 == 1) k = rnd.next(2, 100);
        else k = 1000000000000000000LL;
        println(a, b, k);
    }
}
