#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int la = rnd.next(19000, 32000);
    int lb = rnd.next(19000, 32000);

    string A(la, '9');
    string B(lb, '9');

    println(A);
    println(B);

    return 0;
}
