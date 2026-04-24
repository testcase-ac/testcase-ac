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
vector<int> generate_vec(int len_min, int len_max, int elem_min, int elem_max) {
    int N = rnd.next(len_min, len_max);
    vector<int> v;
    for (int i = 0; i < N; i++) {
        v.push_back(rnd.next(elem_min, elem_max));
    }
    return v;
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    while(T--) {
        int x1 = rnd.next(-10, 10), y1 = rnd.next(-10, 10), r1 = rnd.next(1, 10);
        int x2, y2, r2;
        int c = rnd.next(0, 2);
        if(c == 0) {
            x2 = rnd.next(-10, 10), y2 = rnd.next(-10, 10), r2 = rnd.next(1, 10);
        } else if(c == 1) {
            x2 = x1, y2 = y1, r2 = rnd.next(1, 10);
        } else if(c == 2) {
            x2 = rnd.next(-10, 10), y2 = rnd.next(-10, 10), r2 = (int)(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))) - r1 + rnd.next(-1, 1);
            if(r2 <= 0) {
                r2 = 1;
            }
        }
        println(x1, y1, r1, x2, y2, r2);
    }
}
