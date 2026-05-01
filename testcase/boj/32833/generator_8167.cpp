#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of bars k (histogram has 2*k vertices)
    int k = rnd.next(2, 10);
    vector<int> widths, heights, good;
    // generate until at least one bar has width>=2 and height>=2
    do {
        // widths between consecutive x-coordinates, size k-1, >=1
        widths.assign(k-1, 0);
        for (int i = 0; i < k-1; i++) {
            widths[i] = rnd.next(1, 3);
        }
        // ensure at least one width >= 2 for interior x
        if (!any_of(widths.begin(), widths.end(), [](int w){ return w >= 2; })) {
            widths[rnd.next(0, k-2)] = rnd.next(2, 3);
        }
        // heights for bars, size k; heights[0..k-2]>=1, heights[k-1]=0
        heights.assign(k, 0);
        heights[0] = rnd.next(1, 5);
        for (int i = 1; i < k-1; i++) {
            int h;
            do { h = rnd.next(1, 5); } while (h == heights[i-1]);
            heights[i] = h;
        }
        heights[k-1] = 0;
        // collect bars that allow an interior point: width>=2 and height>=2
        good.clear();
        for (int i = 0; i < k-1; i++) {
            if (widths[i] >= 2 && heights[i] >= 2) {
                good.push_back(i);
            }
        }
    } while (good.empty());

    // compute x-coordinates
    vector<int> x(k);
    x[0] = 0;
    for (int i = 1; i < k; i++) {
        x[i] = x[i-1] + widths[i-1];
    }

    // build v-array of size n = 2*k: v[2*i]=x[i], v[2*i+1]=heights[i]
    int n = 2 * k;
    vector<int> v(n);
    for (int i = 0; i < k; i++) {
        v[2*i] = x[i];
        v[2*i+1] = heights[i];
    }

    // choose a bar index for the piercing point
    int idx = rnd.any(good);
    // pick T strictly inside the chosen bar
    int tx = x[idx] + rnd.next(1, widths[idx] - 1);
    int ty = rnd.next(1, heights[idx] - 1);

    // pick S outside: either left or right of the histogram, above the boundary
    bool placeLeft = rnd.next(0, 1) == 0;
    int sx, sy;
    if (placeLeft) {
        sx = x[0] - rnd.next(1, 3);
        sy = heights[0] + rnd.next(1, 3);
    } else {
        sx = x[k-1] + rnd.next(1, 3);
        sy = heights[k-2] + rnd.next(1, 3);
    }

    // output
    println(n);
    println(v);
    println(sx, sy, tx, ty);
    return 0;
}
