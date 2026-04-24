#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read 홍준's ID: must be 1 to 20 characters, alphanumeric only
    inf.readToken("[A-Za-z0-9]{1,20}", "id");
    inf.readEoln();

    inf.readEof();
    return 0;
}
