#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string readLowercaseString(int n, const char* name) {
    string s = inf.readToken("[a-z]{1,100000}", name);
    ensuref((int)s.size() == n, "%s length must be %d, found %d", name, n, (int)s.size());
    return s;
}

void ensureOrthogonal(const string& s, const string& basis, const char* sName, int basisIndex) {
    for (int i = 0; i < (int)s.size(); ++i) {
        ensuref(s[i] != basis[i],
                "%s is not orthogonal to V_%d at position %d: both are '%c'",
                sName,
                basisIndex,
                i + 1,
                s[i]);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "k");
    inf.readEoln();
    ensuref(1LL * n * k <= 100000, "n * k must be at most 100000, found %lld", 1LL * n * k);

    vector<string> basis(k);
    for (int i = 0; i < k; ++i) {
        basis[i] = readLowercaseString(n, "V_i");
        inf.readEoln();
    }

    string a = readLowercaseString(n, "A");
    inf.readEoln();
    string b = readLowercaseString(n, "B");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        ensureOrthogonal(a, basis[i], "A", i + 1);
        ensureOrthogonal(b, basis[i], "B", i + 1);
    }

    inf.readEof();
}
