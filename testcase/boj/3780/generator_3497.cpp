#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose N
        int N = rnd.next(4, 10);
        println(N);
        // Number of merge commands I (must be < N)
        int M = rnd.next(0, N-1);
        // Number of query commands E
        int Q = rnd.next(1, N*3);
        // Build initial clusters: each company is its own cluster
        struct Cluster { vector<int> mem; int center; };
        vector<Cluster> clusters;
        clusters.reserve(N);
        for (int i = 1; i <= N; i++) {
            Cluster c;
            c.mem = {i};
            c.center = i;
            clusters.push_back(c);
        }
        // Decide mixing pattern: 0: all I then E, 1: all E then I, 2: shuffle
        int mix = rnd.next(0, 2);
        vector<char> ops;
        ops.reserve(M + Q);
        if (mix == 0) {
            ops.insert(ops.end(), M, 'I');
            ops.insert(ops.end(), Q, 'E');
        } else if (mix == 1) {
            ops.insert(ops.end(), Q, 'E');
            ops.insert(ops.end(), M, 'I');
        } else {
            ops.insert(ops.end(), M, 'I');
            ops.insert(ops.end(), Q, 'E');
            shuffle(ops.begin(), ops.end());
        }
        // Process operations in order
        for (char op : ops) {
            if (op == 'E') {
                int x = rnd.next(1, N);
                println("E", x);
            } else { // 'I'
                // pick two distinct clusters A and B
                int sz = clusters.size();
                if (sz < 2) {
                    // no more merges possible, convert to a query
                    int x = rnd.next(1, N);
                    println("E", x);
                    continue;
                }
                int ai = rnd.next(0, sz-1);
                int bi = rnd.next(0, sz-2);
                if (bi >= ai) bi++;
                Cluster A = clusters[ai];
                Cluster B = clusters[bi];
                // pick a member j from B
                int j = rnd.any(B.mem);
                // output merge: center of A connects to j
                println("I", A.center, j);
                // merge A and B into new cluster C; center becomes B.center
                Cluster C;
                C.center = B.center;
                C.mem = A.mem;
                C.mem.insert(C.mem.end(), B.mem.begin(), B.mem.end());
                // remove clusters at ai and bi (erase larger index first)
                if (ai > bi) {
                    clusters.erase(clusters.begin() + ai);
                    clusters.erase(clusters.begin() + bi);
                } else {
                    clusters.erase(clusters.begin() + bi);
                    clusters.erase(clusters.begin() + ai);
                }
                clusters.push_back(C);
            }
        }
        // End of test case
        println("O");
    }
    return 0;
}
