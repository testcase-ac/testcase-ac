#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[ab]{1,1000}", "s");
    inf.readEof();
    return 0;
}
