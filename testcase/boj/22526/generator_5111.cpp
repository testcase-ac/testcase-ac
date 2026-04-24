#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Number of datasets
    int D = rnd.next(1, 5);
    vector<int> Toptions = {10, 1000, 100000};
    
    for (int di = 0; di < D; di++) {
        // Number of stages
        int N = rnd.next(1, 8);
        // Choose max time range
        int Tmax = rnd.any(Toptions);
        // Probability that equipment is generally helpful
        bool favorEquip = rnd.next() < 0.5;
        
        println(N);
        for (int i = 1; i <= N; i++) {
            // Base time without equipment
            int t0 = rnd.next(1, Tmax);
            vector<int> row;
            row.push_back(t0);
            for (int j = 1; j <= N; j++) {
                // For each equipment j on stage i
                int tij;
                if (favorEquip) {
                    // equip often helps: half chance it's faster than no-equip
                    if (rnd.next() < 0.5) {
                        tij = rnd.next(1, t0);
                    } else {
                        tij = rnd.next(t0, Tmax);
                    }
                } else {
                    // equip often hurts: half chance slower
                    if (rnd.next() < 0.5) {
                        tij = rnd.next(t0, Tmax);
                    } else {
                        tij = rnd.next(1, t0);
                    }
                }
                row.push_back(tij);
            }
            println(row);
        }
    }
    // Terminate input
    println(0);
    return 0;
}
