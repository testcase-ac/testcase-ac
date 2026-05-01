#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int scenario = rnd.next(0, 99);
    int N, K, P;
    vector<int> a;
    if (scenario < 15) {
        // Subtask 1: N = 1
        N = 1;
        K = rnd.next(1, 10);
        P = rnd.next(1, K);
        for (int i = 0; i < N * K; i++) a.push_back(rnd.next(0, 1));
    } else if (scenario < 30) {
        // Subtask 2: K = 1
        K = 1;
        N = rnd.next(1, 10);
        P = 1;
        for (int i = 0; i < N * K; i++) a.push_back(rnd.next(0, 1));
    } else if (scenario < 45) {
        // Subtask 3: all breads same
        N = rnd.next(1, 10);
        K = rnd.next(1, 10);
        P = rnd.next(1, K);
        int bit = rnd.next(0, 1);
        for (int i = 0; i < N * K; i++) a.push_back(bit);
    } else if (scenario < 60) {
        // Subtask 4: each bundle uniform
        N = rnd.next(1, 10);
        K = rnd.next(1, 10);
        P = rnd.next(1, K);
        for (int i = 0; i < N; i++) {
            int b = rnd.next(0, 1);
            for (int j = 0; j < K; j++) a.push_back(b);
        }
    } else if (scenario < 75) {
        // Subtask 5: P = 1
        N = rnd.next(1, 10);
        K = rnd.next(1, 10);
        P = 1;
        for (int i = 0; i < N * K; i++) a.push_back(rnd.next(0, 1));
    } else if (scenario < 90) {
        // general: random density of zeros
        N = rnd.next(1, 10);
        K = rnd.next(1, 10);
        P = rnd.next(1, K);
        double p0 = rnd.next(0.0, 1.0);
        for (int i = 0; i < N * K; i++)
            a.push_back(rnd.next() < p0 ? 0 : 1);
    } else {
        // general with controlled bundles around threshold
        N = rnd.next(1, 10);
        K = rnd.next(1, 10);
        P = rnd.next(1, K);
        int special = min(N, 3);
        for (int i = 0; i < N; i++) {
            if (i < special) {
                vector<int> opts;
                opts.push_back(0);
                if (P - 1 >= 0) opts.push_back(P - 1);
                opts.push_back(P);
                if (P + 1 <= K) opts.push_back(P + 1);
                int zeros = rnd.any(opts);
                zeros = min(zeros, K);
                int start = (int)a.size();
                for (int j = 0; j < zeros; j++) a.push_back(0);
                for (int j = zeros; j < K; j++) a.push_back(1);
                shuffle(a.begin() + start, a.begin() + start + K);
            } else {
                for (int j = 0; j < K; j++) a.push_back(rnd.next(0, 1));
            }
        }
    }
    println(N, K, P);
    println(a);
    return 0;
}
