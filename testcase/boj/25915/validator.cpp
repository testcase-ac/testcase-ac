#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[A-Z]", "c");
    inf.readEoln();
    inf.readEof();

    return 0;
}
