#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "M");
    inf.readEoln();

    int length = n + m;
    ensuref(1 <= length && length <= 100000,
            "N + M must be in [1, 100000], got %d", length);

    string s = inf.readToken("[01]{1,100000}", "S");
    inf.readEoln();
    string t = inf.readToken("[01]{1,100000}", "T");
    inf.readEoln();
    inf.readEof();

    ensuref((int)s.size() == length, "S length must be %d, got %d",
            length, (int)s.size());
    ensuref((int)t.size() == length, "T length must be %d, got %d",
            length, (int)t.size());

    int s_zeroes = count(s.begin(), s.end(), '0');
    int t_zeroes = count(t.begin(), t.end(), '0');
    ensuref(s_zeroes == n, "S must contain %d zeroes, got %d", n, s_zeroes);
    ensuref(t_zeroes == n, "T must contain %d zeroes, got %d", n, t_zeroes);
}
