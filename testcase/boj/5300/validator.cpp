#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for N; cap it at a practical output size.
    inf.readInt(1, 1000000, "N");
    inf.readEoln();
    inf.readEof();
}
