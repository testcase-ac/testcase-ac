#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[01?]{1,1500}", "S");
    inf.readEoln();

    int questionCount = count(s.begin(), s.end(), '?');
    ensuref(questionCount <= 1, "S must contain at most one question mark");

    inf.readEof();
}
