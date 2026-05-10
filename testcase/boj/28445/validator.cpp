#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: father's body and tail colors
    inf.readToken("[a-z]{1,20}", "father_body");
    inf.readSpace();
    inf.readToken("[a-z]{1,20}", "father_tail");
    inf.readEoln();

    // Second line: mother's body and tail colors
    inf.readToken("[a-z]{1,20}", "mother_body");
    inf.readSpace();
    inf.readToken("[a-z]{1,20}", "mother_tail");
    inf.readEoln();

    inf.readEof();
    return 0;
}
