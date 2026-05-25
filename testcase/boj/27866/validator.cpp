#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[A-Za-z]{1,1000}", "S");
    inf.readEoln();

    inf.readInt(1, (int)s.size(), "i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
