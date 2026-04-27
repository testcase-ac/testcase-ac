#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    string a = inf.readToken("[01]+", "A");
    inf.readEoln();
    string b = inf.readToken("[01]+", "B");
    inf.readEoln();

    ensuref((int)a.size() == n, "A length is %d, expected %d", (int)a.size(), n);
    ensuref((int)b.size() == n, "B length is %d, expected %d", (int)b.size(), n);

    inf.readInt(1, 10000, "p_1");
    inf.readSpace();
    inf.readInt(1, 10000, "p_3");
    inf.readSpace();
    inf.readInt(1, 10000, "p_5");
    inf.readSpace();
    inf.readInt(1, 10000, "p_pair");
    inf.readEoln();

    inf.readEof();
    return 0;
}
