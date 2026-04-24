#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of photos
    int n = rnd.next(1, 10);

    // Hyper-parameters for diversity
    int clusterCount = rnd.next(1, min(3, n));
    int jitterBound = rnd.next(0, 5);
    double aRatio = rnd.next(0.0, 1.0);
    int maxHalfSide = rnd.next(1, 5);
    int maxHalfDiag = rnd.next(1, 5);

    // Generate cluster centers
    vector<pair<int,int>> clusters;
    for (int i = 0; i < clusterCount; i++) {
        int cx = rnd.next(-10, 10);
        int cy = rnd.next(-10, 10);
        clusters.emplace_back(cx, cy);
    }

    // Build photo specifications
    vector<string> lines;
    for (int i = 0; i < n; i++) {
        bool isA = rnd.next() < aRatio;
        auto cl = clusters[rnd.next(0, clusterCount - 1)];
        int dx = rnd.next(-jitterBound, jitterBound);
        int dy = rnd.next(-jitterBound, jitterBound);
        int x = cl.first + dx;
        int y = cl.second + dy;
        if (isA) {
            int half = rnd.next(1, maxHalfSide);
            int a = 2 * half;
            char buf[50];
            sprintf(buf, "A %d %d %d", x, y, a);
            lines.emplace_back(buf);
        } else {
            int half = rnd.next(1, maxHalfDiag);
            int d = 2 * half;
            char buf[50];
            sprintf(buf, "B %d %d %d", x, y, d);
            lines.emplace_back(buf);
        }
    }

    // Shuffle order for unpredictability
    shuffle(lines.begin(), lines.end());

    // Output
    println(n);
    for (auto &s : lines)
        printf("%s\n", s.c_str());

    return 0;
}
