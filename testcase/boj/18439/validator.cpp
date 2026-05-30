#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[A-Z]{1,50000}", "s1");
    inf.readLine("[A-Z]{1,50000}", "s2");
    inf.readEof();
}
