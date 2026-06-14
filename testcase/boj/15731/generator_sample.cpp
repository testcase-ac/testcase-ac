#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string randomStatements(int n, int fPercent) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.next(100) < fPercent ? 'f' : 'e');
    }
    s.back() = 'e';
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    string statements;

    if (mode == 0) {
        n = rnd.next(1, 30);
        statements.assign(n, 'e');
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        statements.reserve(n);
        char first = rnd.next(2) == 0 ? 'f' : 'e';
        for (int i = 0; i < n; ++i) {
            statements.push_back(i % 2 == 0 ? first : (first == 'f' ? 'e' : 'f'));
        }
        statements.back() = 'e';
    } else if (mode == 2) {
        n = rnd.next(2, 60);
        statements.assign(n - 1, 'f');
        statements.push_back('e');
    } else if (mode == 3) {
        n = rnd.next(1, 80);
        int fPercent = rnd.next(10, 90);
        statements = randomStatements(n, fPercent);
    } else if (mode == 4) {
        n = rnd.next(1, 120);
        int fPercent = rnd.next(20, 80);
        while ((int)statements.size() < n) {
            char c = rnd.next(100) < fPercent ? 'f' : 'e';
            int run = rnd.next(1, min(12, n - (int)statements.size()));
            statements.append(run, c);
        }
        statements.back() = 'e';
    } else {
        n = rnd.next(200, 5000);
        int fPercent = rnd.next(30, 70);
        statements = randomStatements(n, fPercent);
    }

    println(statements);
    return 0;
}
