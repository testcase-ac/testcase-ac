#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first string (구사과's letters)
    string s1 = inf.readToken("[a-z]{1,300000}", "s1");
    inf.readEoln();

    // Read second string (큐브러버's letters)
    string s2 = inf.readToken("[a-z]{1,300000}", "s2");
    inf.readEoln();

    int n = s1.length();
    ensuref(s2.length() == n, "Both strings must have the same length N, but got %d and %d", n, (int)s2.length());

    inf.readEof();
}
