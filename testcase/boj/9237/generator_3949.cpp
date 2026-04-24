#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);               // number of saplings
    int max_t = rnd.next(1, 20);           // maximum growth time
    double mix_p = rnd.next(0.0, 1.0);     // mixture probability
    
    vector<int> t(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < mix_p) {
            // biased towards larger times
            t[i] = rnd.wnext(max_t, 1) + 1;  
        } else {
            // uniform times
            t[i] = rnd.next(1, max_t);
        }
    }
    // shuffle order so it's not sorted
    shuffle(t.begin(), t.end());
    
    // output
    println(N);
    println(t);
    return 0;
}
