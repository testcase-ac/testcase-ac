#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{1,100000}", "s");
    inf.readEoln();
    string t = inf.readToken("[a-z]{1,100}", "t");
    inf.readEoln();

    ensuref(t.size() <= s.size(), "|t| must not exceed |s|: |t|=%d, |s|=%d",
            int(t.size()), int(s.size()));

    inf.readEof();
}
