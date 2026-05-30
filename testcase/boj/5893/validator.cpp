#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string N = inf.readToken("1[01]{0,999}", "N");
    inf.readEoln();
    inf.readEof();
}
