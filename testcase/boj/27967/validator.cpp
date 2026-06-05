#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "N");
    inf.readEoln();

    string s = inf.readToken("[()G]{2,20}", "S");
    inf.readEoln();
    ensuref((int)s.size() == n, "S length must equal N: length=%d, N=%d", (int)s.size(), n);

    vector<int> possible(n + 1, 0);
    possible[0] = 1;
    for (int i = 0; i < n; ++i) {
        vector<int> next(n + 1, 0);
        if (s[i] == '(' || s[i] == 'G') {
            for (int balance = 0; balance < n; ++balance) {
                if (possible[balance]) {
                    next[balance + 1] = 1;
                }
            }
        }
        if (s[i] == ')' || s[i] == 'G') {
            for (int balance = 1; balance <= n; ++balance) {
                if (possible[balance]) {
                    next[balance - 1] = 1;
                }
            }
        }
        possible = next;
    }
    ensuref(possible[0], "S must have at least one valid bracket restoration");

    inf.readEof();
}
