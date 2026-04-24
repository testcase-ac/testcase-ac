#include "testlib.h"
#include <vector>
#include <numeric>
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
    while(1) {
        int K = rnd.next(1, 8), N = rnd.next(1, 15);
        while(!(K <= N)) {
            K = rnd.next(1, 8);
            N = rnd.next(1, 15);
        }
        int mn = rnd.next(1, 15);
        int mx = rnd.next(mn, mn+15);
        if(rnd.next() < 0.2) { // try very large mn, mx: close to INT_MAX
            mn = rnd.next(INT_MAX-10, INT_MAX);
            mx = rnd.next(mn, INT_MAX);
        }
        vector<int> v = generate_vec(K, K, mn, mx);
        long long sum = accumulate(v.begin(), v.end(), 0ll);
        if(sum < N) {
            continue;
        }
        println(K, N);
        for(int i = 0; i < K; i++) {
            printf("%d\n", v[i]);
        }
        break;
    }

}
