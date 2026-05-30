#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[^ \t\r\n]{1,2000}", "first_word");
    inf.readEoln();
    inf.readToken("[^ \t\r\n]{1,2000}", "second_word");
    inf.readEoln();
    inf.readEof();
}
