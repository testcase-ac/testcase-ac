#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of swap sequence
    int L = rnd.next(1, 50);

    // Weights for A, B, C to bias letter frequencies
    int wa = rnd.next(1, 10);
    int wb = rnd.next(1, 10);
    int wc = rnd.next(1, 10);
    vector<char> pool;
    for (int i = 0; i < wa; i++) pool.push_back('A');
    for (int i = 0; i < wb; i++) pool.push_back('B');
    for (int i = 0; i < wc; i++) pool.push_back('C');

    // Decide generation mode: independent or clustered
    bool cluster_mode = rnd.next(0, 1) == 1;
    double p_cluster = rnd.next();  // only used if cluster_mode

    string s;
    s.reserve(L);
    // First letter
    char prev = rnd.any(pool);
    s.push_back(prev);

    for (int i = 1; i < L; i++) {
        if (cluster_mode && rnd.next() < p_cluster) {
            // repeat the previous swap
            s.push_back(prev);
        } else {
            // pick a new random swap
            char c = rnd.any(pool);
            s.push_back(c);
            prev = c;
        }
    }

    // Output the sequence
    printf("%s\n", s.c_str());
    return 0;
}
