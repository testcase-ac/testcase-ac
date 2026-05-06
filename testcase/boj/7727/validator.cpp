#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n1 n2
    int n1 = inf.readInt(1, 10000, "n1");
    inf.readSpace();
    int n2 = inf.readInt(1, 10000, "n2");
    inf.readEoln();

    // Second line: string s1 of length n1, lowercase letters only
    string s1 = inf.readToken("[a-z]{1,10000}", "s1");
    inf.readEoln();
    ensuref((int)s1.size() == n1,
            "Length of s1 (%d) does not match n1 (%d)", (int)s1.size(), n1);

    // Third line: string s2 of length n2, lowercase letters only
    string s2 = inf.readToken("[a-z]{1,10000}", "s2");
    inf.readEoln();
    ensuref((int)s2.size() == n2,
            "Length of s2 (%d) does not match n2 (%d)", (int)s2.size(), n2);

    inf.readEof();
}
