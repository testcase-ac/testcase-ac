//GPT 코드
#include "testlib.h"
#include <set>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int k = inf.readInt();
    int n = inf.readInt();

    set<string> seen;

    for (int i = 0; i < n; i++) {
        long long a = ouf.readLong();
        long long b = ouf.readLong();
        long long c = ouf.readLong();

        // check positive
        if (a <= 0 || b <= 0 || c <= 0)
            quitf(_wa, "Numbers must be positive");

        // check <= 100 digits
        auto check_len = [](long long x) {
            string s = to_string(x);
            return s.length() <= 100;
        };
        if (!check_len(a) || !check_len(b) || !check_len(c))
            quitf(_wa, "Numbers must have at most 100 digits");

        // check uniqueness
        string key = to_string(a) + "," + to_string(b) + "," + to_string(c);
        if (seen.count(key))
            quitf(_wa, "Duplicate triple found");
        seen.insert(key);

        // check equation
        long long lhs = a*a + b*b + c*c;
        long long rhs = k*(a*b + b*c + c*a) + 1;
        if (lhs != rhs)
            quitf(_wa, "Equation not satisfied for (%lld,%lld,%lld)", a,b,c);
    }

    quitf(_ok, "All %d triples are correct", n);
}
