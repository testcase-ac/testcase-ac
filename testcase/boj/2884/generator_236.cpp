#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> special = {0, 15, 30, 45};
    int h = rnd.next(0, 23);
    int m = rnd.next(0, 59);
    if(rnd.next() < 0.5) {
        h = 0;
    }
    if(rnd.next() < 0.5) {
        m = special[rnd.next(0, 3)];
    }
    println(h, m);
}
