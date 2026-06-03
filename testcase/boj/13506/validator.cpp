#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{1,1000000}", "S");
    inf.readEoln();
    inf.readEof();

    return 0;
}
