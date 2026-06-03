#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    string first = inf.readToken("[a-z]{2,100000}", "first");
    inf.readEoln();
    string second = inf.readToken("[a-z]{2,100000}", "second");
    inf.readEoln();

    ensuref((int)first.size() == n, "first length is %d, expected %d", (int)first.size(), n);
    ensuref((int)second.size() == n, "second length is %d, expected %d", (int)second.size(), n);

    inf.readEof();
}
