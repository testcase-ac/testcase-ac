#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-z]{1,2000}", "first_word");
    inf.readEoln();
    inf.readToken("[a-z]{1,2000}", "second_word");
    inf.readEoln();
    inf.readEof();
}
