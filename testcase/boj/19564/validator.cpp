#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-z]{1,100000}", "S");
    inf.readEoln();
    inf.readEof();
}
