#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int D = 30;       // spacing between centers
    const int dx_min = 4;   // half-width range
    const int dx_max = 7;
    const int dy_min = 4;   // half-height range
    const int dy_max = 7;

    // Choose N with some variability but keep it small/medium
    int bucket = rnd.next(0, 99);
    int N;
    if (bucket < 30) N = rnd.next(1, 5);
    else if (bucket < 80) N = rnd.next(6, 10);
    else N = rnd.next(11, 15);

    // Choose K with bias to edges and middle
    int typeK = rnd.next(0, 99);
    int K;
    if (typeK < 30) K = 1;
    else if (typeK < 60) K = N;
    else K = rnd.next(1, N);

    println(N, K);

    struct Center { int x, y; };
    vector<Center> centers(N);

    int layout = rnd.next(0, 2); // 0: line+, 1: line centered-ish, 2: grid

    if (layout == 0) {
        // Line along positive x-axis (some small shift)
        int startShift = rnd.next(-2, 2);
        for (int i = 0; i < N; i++) {
            centers[i].x = (i + startShift) * D;
            centers[i].y = 0;
        }
    } else if (layout == 1) {
        // Line roughly centered around origin
        for (int i = 0; i < N; i++) {
            centers[i].x = (i - N / 2) * D;
            centers[i].y = 0;
        }
    } else {
        // Grid around origin
        int maxRows = min(4, N);
        int rows = rnd.next(1, maxRows);
        int cols = (N + rows - 1) / rows;

        vector<Center> tmp;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                Center ct;
                ct.x = c * D;
                ct.y = r * D;
                tmp.push_back(ct);
            }
        }
        shuffle(tmp.begin(), tmp.end());
        tmp.resize(N);

        int shiftX = (cols - 1) * D / 2;
        int shiftY = (rows - 1) * D / 2;
        for (int i = 0; i < N; i++) {
            centers[i].x = tmp[i].x - shiftX;
            centers[i].y = tmp[i].y - shiftY;
        }
    }

    // Optionally shuffle centers to break monotone distance patterns
    if (rnd.next(0, 1) == 1) {
        shuffle(centers.begin(), centers.end());
    }

    for (int i = 0; i < N; i++) {
        int Pi;
        int t = rnd.next(0, 99);
        if (t < 30) Pi = 3;                 // triangle
        else if (t < 60) Pi = 4;            // rectangle
        else Pi = rnd.next(5, 10);          // rectilinear convex polygon

        println(Pi);

        int cx = centers[i].x;
        int cy = centers[i].y;

        if (Pi == 3) {
            // Right triangle, axis-aligned, convex
            int dx = rnd.next(dx_min, dx_max);
            int dy = rnd.next(dy_min, dy_max);

            vector<int> coords;
            coords.push_back(cx - dx); coords.push_back(cy - dy); // bottom-left
            coords.push_back(cx + dx); coords.push_back(cy - dy); // bottom-right
            coords.push_back(cx - dx); coords.push_back(cy + dy); // top-left

            println(coords);
        } else {
            // Axis-aligned convex polygon based on a rectangle with extra points on edges
            int dx = rnd.next(dx_min, dx_max);
            int dy = rnd.next(dy_min, dy_max);

            int extra = Pi - 4;
            vector<int> sides(4, 0); // 0: bottom, 1: right, 2: top, 3: left
            for (int e = 0; e < extra; e++) {
                int side = rnd.next(0, 3);
                sides[side]++;
            }

            vector<pair<int,int>> pts;

            int xl = cx - dx;
            int xr = cx + dx;
            int yb = cy - dy;
            int yt = cy + dy;

            // Bottom side: from left to right
            pts.push_back({xl, yb}); // bottom-left

            int s0 = sides[0];
            if (s0 > 0) {
                vector<int> cand;
                for (int v = 1; v < 2 * dx; v++) { // xl+1 .. xr-1
                    cand.push_back(xl + v);
                }
                shuffle(cand.begin(), cand.end());
                cand.resize(s0);
                sort(cand.begin(), cand.end());
                for (int x : cand) pts.push_back({x, yb});
            }
            pts.push_back({xr, yb}); // bottom-right

            // Right side: from bottom to top
            int s1 = sides[1];
            if (s1 > 0) {
                vector<int> cand;
                for (int v = 1; v < 2 * dy; v++) { // yb+1 .. yt-1
                    cand.push_back(yb + v);
                }
                shuffle(cand.begin(), cand.end());
                cand.resize(s1);
                sort(cand.begin(), cand.end());
                for (int y : cand) pts.push_back({xr, y});
            }
            pts.push_back({xr, yt}); // top-right

            // Top side: from right to left
            int s2 = sides[2];
            if (s2 > 0) {
                vector<int> cand;
                for (int v = 1; v < 2 * dx; v++) { // xr-1 .. xl+1
                    cand.push_back(xr - v);
                }
                shuffle(cand.begin(), cand.end());
                cand.resize(s2);
                sort(cand.rbegin(), cand.rend()); // descending x
                for (int x : cand) pts.push_back({x, yt});
            }
            pts.push_back({xl, yt}); // top-left

            // Left side: from top to bottom
            int s3 = sides[3];
            if (s3 > 0) {
                vector<int> cand;
                for (int v = 1; v < 2 * dy; v++) { // yt-1 .. yb+1
                    cand.push_back(yt - v);
                }
                shuffle(cand.begin(), cand.end());
                cand.resize(s3);
                sort(cand.rbegin(), cand.rend()); // descending y
                for (int y : cand) pts.push_back({xl, y});
            }

            // Flatten and output
            vector<int> coords;
            coords.reserve(2 * Pi);
            for (auto &p : pts) {
                coords.push_back(p.first);
                coords.push_back(p.second);
            }
            println(coords);
        }
    }

    return 0;
}
