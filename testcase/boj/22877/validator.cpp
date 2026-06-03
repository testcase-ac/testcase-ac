#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "t");
    inf.readEoln();

    string cards = inf.readToken("[RSP]{2,500000}", "cards");
    ensuref((int)cards.size() == n, "cards length must be n: expected %d, found %d",
            n, (int)cards.size());
    inf.readEoln();
    inf.readEof();
}
