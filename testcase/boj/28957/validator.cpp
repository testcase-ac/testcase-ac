#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,5000}", "s");
    inf.readEoln();
    ensuref((int)s.size() == n, "s length must be n: expected %d, got %d",
            n, (int)s.size());

    string t = inf.readToken("[a-z]{1,5000}", "t");
    inf.readEoln();
    ensuref((int)t.size() == n, "t length must be n: expected %d, got %d",
            n, (int)t.size());

    inf.readEof();
}
