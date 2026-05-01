#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int Y1 = 36 * 36;       // 1 square yard in square inches = 1296
    const int Y2 = 2 * Y1;        // 2 square yards
    const int Y3 = 3 * Y1;        // 3 square yards = 3888

    int N = rnd.next(1, 8);       // number of datasets, small for readability
    println(N);

    for (int ds = 0; ds < N; ++ds) {
        // Choose number of images I with some variety
        int modeI = rnd.next(0, 2);
        int I;
        if (modeI == 0) {
            I = 1;                    // single-image patterns
        } else if (modeI == 1) {
            I = rnd.next(2, 4);       // small multi-image
        } else {
            I = rnd.next(5, 10);      // larger multi-image
        }

        // Decide rough total area scale for one full set
        int style = rnd.next(0, 4);
        int lo, hi;
        switch (style) {
            case 0: // very small total area
                lo = I;
                hi = min(Y3, 100);
                break;
            case 1: // around 1 yard
                lo = max(I, Y1 / 4);   // around 324
                hi = Y1;               // 1296
                break;
            case 2: // between 1 and 2 yards
                lo = max(I, Y1);
                hi = Y2;               // 2592
                break;
            case 3: // between 2 and 3 yards
                lo = max(I, Y2);
                hi = Y3;               // 3888
                break;
            default: // full range
                lo = I;
                hi = Y3;
                break;
        }
        if (hi < lo) hi = lo;          // safety, though should not happen

        int Amax = rnd.next(lo, hi);   // upper bound on total area of one set

        // Biases for image parameters in this dataset
        int sBiasType = rnd.next(0, 2); // 0: small S, 1: mixed, 2: large S
        int rBiasType = rnd.next(0, 2); // 0: small R, 1: mixed, 2: large R

        vector<pair<int,int>> imgs;
        imgs.reserve(I);

        int totalArea = 0;
        for (int idx = 0; idx < I; ++idx) {
            int remainingImages = I - idx;
            int remainingCap = Amax - totalArea;
            // Reserve at least 1 area unit for each remaining image (including this one)
            int minNeededForFuture = remainingImages - 1;
            int maxForThis = remainingCap - minNeededForFuture;
            if (maxForThis < 1) maxForThis = 1; // should not occur if Amax >= I

            // Choose S
            int Smax = min(1000, maxForThis);
            int S;
            if (sBiasType == 0) {
                // bias towards small S
                S = rnd.wnext(Smax, -3) + 1;
            } else if (sBiasType == 2) {
                // bias towards large S
                S = rnd.wnext(Smax, 3) + 1;
            } else {
                // uniform S
                S = rnd.next(1, Smax);
            }

            int Rmax = maxForThis / S;
            if (Rmax > 100) Rmax = 100;
            if (Rmax < 1) {
                // If chosen S too large, fall back to S=1
                S = 1;
                Rmax = min(100, maxForThis);
            }

            int R;
            if (rBiasType == 0) {
                // bias towards small R
                R = rnd.wnext(Rmax, -3) + 1;
            } else if (rBiasType == 2) {
                // bias towards large R
                R = rnd.wnext(Rmax, 3) + 1;
            } else {
                // uniform R
                R = rnd.next(1, Rmax);
            }

            int area = S * R;
            if (area < 1) area = 1; // safety
            if (totalArea + area + (remainingImages - 1) > Amax) {
                // Clamp area to fit into the remaining capacity if necessary
                int maxAreaAllowed = Amax - totalArea - (remainingImages - 1);
                if (maxAreaAllowed < 1) maxAreaAllowed = 1;
                // Reduce R to fit, keeping S unchanged if possible
                int newRmax = maxAreaAllowed / S;
                if (newRmax >= 1) {
                    if (newRmax > 100) newRmax = 100;
                    if (newRmax < 1) newRmax = 1;
                    R = min(R, newRmax);
                    area = S * R;
                } else {
                    // Fall back to S=1
                    S = 1;
                    newRmax = maxAreaAllowed;
                    if (newRmax > 100) newRmax = 100;
                    if (newRmax < 1) newRmax = 1;
                    R = min(R, newRmax);
                    area = S * R;
                }
            }

            imgs.push_back({S, R});
            totalArea += area;
        }

        // Shuffle images to avoid any pattern
        shuffle(imgs.begin(), imgs.end());

        println(I);
        for (auto &p : imgs) {
            println(p.first, p.second);
        }
    }

    return 0;
}
