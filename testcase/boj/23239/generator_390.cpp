#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> bias = {10};
    const int MX = 1e5;
    double r = rnd.next();
    if(r < 0.6) {
        println(rnd.next(1, 10), rnd.next(1, 10), rnd.next(1, 10));
    } else {
        println(rnd.next(1, MX), rnd.next(1, MX), rnd.next(1, MX));
    }
}
