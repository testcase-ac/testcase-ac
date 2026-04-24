#include "testlib.h"
#include <vector>
using namespace std;
int generate_int_biased(int min, int max, vector<int> thresholds) {
    int sz = thresholds.size();
    int c = rnd.next(1, sz+1);
    if(c == 1) {
        return rnd.next(min, thresholds[0]);
    } else if(c == sz+1) {
        return rnd.next(thresholds[sz-1]+1, max);
    } else {
        return rnd.next(thresholds[c-2]+1, thresholds[c-1]);
    }
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> bias = {20, 200};
    int T = rnd.next(1, 3);
    println(T);
    for (int i = 0; i < T; i++) {
        int a = generate_int_biased(1, 10000, bias), b = generate_int_biased(1, 10000, bias);
        while(a == b) {
            a = generate_int_biased(1, 10000, bias);
        }
        println(a, b);
    }
}
