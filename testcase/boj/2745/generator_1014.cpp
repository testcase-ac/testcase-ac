#include "testlib.h"
using namespace std;

char get_char(int d) {
    if (d < 10) {
        return '0' + d;
    } else {
        return 'A' + (d - 10);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int B = rnd.next(2, 36);
    int L = rnd.next(1, 5);
    string N;
    
    for (int i = 0; i < L; ++i) {
        int digit;
        if (i == 0) {
            if (L == 1) {
                digit = rnd.next(0, B - 1);
            } else {
                digit = rnd.next(1, B - 1);
            }
        } else {
            digit = rnd.next(0, B - 1);
        }
        N += get_char(digit);
    }
    
    println(N, B);
    
    return 0;
}
