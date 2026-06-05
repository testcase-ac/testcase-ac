#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    string s = inf.readToken("[HT]{1,3000}", "S");
    ensuref((int)s.size() == n, "S length must equal N: length=%d, N=%d", (int)s.size(), n);
    inf.readEoln();

    inf.readEof();
}
