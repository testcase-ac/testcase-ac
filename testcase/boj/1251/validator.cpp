#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[a-z]{3,50}", "word");
    inf.readEof();

    return 0;
}
