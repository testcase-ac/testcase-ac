#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 300000, "K");
    inf.readEoln();

    string s = inf.readToken("[NS]{1,300000}", "S");
    inf.readEoln();
    ensuref((int)s.size() == k, "S length is %d, expected K=%d", (int)s.size(), k);

    inf.readEof();
}
