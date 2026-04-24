#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Base height and variations
    int base = rnd.next(1, 50);
    int highRise = rnd.next(0, base);
    int lowDrop = base > 1 ? rnd.next(0, base - 1) : 0;

    // Probabilities for interior vs border
    double p_ilow  = rnd.next(0.0, 1.0);
    double p_ihigh = rnd.next(0.0, 1.0);
    double p_blow  = rnd.next(0.0, 1.0);
    double p_bhigh = rnd.next(0.0, 1.0);

    // Output M N
    println(M, N);

    for (int i = 1; i <= N; i++) {
        vector<long long> row(M);
        for (int j = 1; j <= M; j++) {
            double p = rnd.next();
            bool isBorder = (i == 1 || i == N || j == 1 || j == M);
            if (isBorder) {
                if (p < p_blow) {
                    int lowmax = base - lowDrop; // >= 1
                    row[j-1] = rnd.next(1, lowmax);
                } else if (p < p_blow + p_bhigh) {
                    if (highRise > 0) row[j-1] = rnd.next(base + 1, base + highRise);
                    else row[j-1] = base;
                } else {
                    row[j-1] = base;
                }
            } else {
                if (p < p_ilow) {
                    if (base > 1) row[j-1] = rnd.next(1, base - 1);
                    else row[j-1] = 1;
                } else if (p < p_ilow + p_ihigh) {
                    if (highRise > 0) row[j-1] = rnd.next(base + 1, base + highRise);
                    else row[j-1] = base;
                } else {
                    row[j-1] = base;
                }
            }
        }
        println(row);
    }

    return 0;
}
