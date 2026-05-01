#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 4;
    const int N_MAX = 300000;
    const long long COORD_MIN = 0LL;
    const long long COORD_MAX = 1000000000LL;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    // N is even (statement)
    ensuref(N % 2 == 0, "N must be even, got %d", N);

    vector<long long> xs(N), ys(N);
    for (int i = 0; i < N; ++i) {
        xs[i] = inf.readLong(COORD_MIN, COORD_MAX, "x_i");
        inf.readSpace();
        ys[i] = inf.readLong(COORD_MIN, COORD_MAX, "y_i");
        inf.readEoln();
    }

    // First vertex (0,0)
    ensuref(xs[0] == 0 && ys[0] == 0,
            "First vertex must be (0,0), got (%lld,%lld)", xs[0], ys[0]);
    // Last vertex (A,0) with A >= 0 (already ensured by bounds)
    ensuref(ys[N-1] == 0,
            "Last vertex y must be 0, got %lld", ys[N-1]);

    // No consecutive equal vertices, and axis-aligned segments only
    for (int i = 0; i < N - 1; ++i) {
        ensuref(!(xs[i] == xs[i + 1] && ys[i] == ys[i + 1]),
                "Consecutive vertices %d and %d are identical", i, i + 1);
        bool vertical   = (xs[i] == xs[i + 1]);
        bool horizontal = (ys[i] == ys[i + 1]);
        ensuref(vertical || horizontal,
                "Edge %d is not axis-aligned: (%lld,%lld) -> (%lld,%lld)",
                i, xs[i], ys[i], xs[i + 1], ys[i + 1]);
        ensuref(!(vertical && horizontal),
                "Zero-length edge at index %d", i);
    }

    // First edge vertical: (0,0) -> (0, y1)
    ensuref(xs[1] == xs[0],
            "First edge must be vertical from (0,0), got (%lld,%lld)->(%lld,%lld)",
            xs[0], ys[0], xs[1], ys[1]);

    // Last edge vertical: (x_{N-2}, y_{N-2}) -> (A,0)
    ensuref(xs[N - 1] == xs[N - 2],
            "Last edge must be vertical, got (%lld,%lld)->(%lld,%lld)",
            xs[N - 2], ys[N - 2], xs[N - 1], ys[N - 1]);

    // Edges must alternate vertical/horizontal starting with vertical and ending with vertical.
    // Pattern: V H V H ... V has odd number of edges, i.e., (N-1) is odd.
    ensuref((N - 1) % 2 == 1,
            "Number of edges N-1 must be odd so that vertical/horizontal alternation holds, got %d", N - 1);

    int M = N - 1; // number of edges
    for (int i = 0; i < M; ++i) {
        bool vertical = (xs[i] == xs[i + 1]);
        if (i % 2 == 0) {
            // even index: vertical
            ensuref(vertical,
                    "Edge %d must be vertical, got (%lld,%lld)->(%lld,%lld)",
                    i, xs[i], ys[i], xs[i + 1], ys[i + 1]);
        } else {
            // odd index: horizontal
            ensuref(!vertical,
                    "Edge %d must be horizontal, got (%lld,%lld)->(%lld,%lld)",
                    i, xs[i], ys[i], xs[i + 1], ys[i + 1]);
        }
    }

    // x-coordinates non-decreasing (x-monotone from left to right)
    for (int i = 1; i < N; ++i) {
        ensuref(xs[i] >= xs[i - 1],
                "x-coordinates must be non-decreasing, but x[%d]=%lld < x[%d]=%lld",
                i, xs[i], i - 1, xs[i - 1]);
    }

    // Detailed segment checks
    for (int i = 0; i < M; ++i) {
        bool vertical = (xs[i] == xs[i + 1]);
        if (!vertical) {
            // horizontal: y1 == y2, x1 < x2
            ensuref(ys[i] == ys[i + 1],
                    "Horizontal edge %d must have equal y, got y1=%lld, y2=%lld",
                    i, ys[i], ys[i + 1]);
            ensuref(xs[i + 1] > xs[i],
                    "Horizontal edge %d must have strictly increasing x, got x1=%lld, x2=%lld",
                    i, xs[i], xs[i + 1]);
        } else {
            // vertical: x1 == x2, y1 != y2
            ensuref(xs[i] == xs[i + 1],
                    "Vertical edge %d must have equal x, got x1=%lld, x2=%lld",
                    i, xs[i], xs[i + 1]);
            ensuref(ys[i] != ys[i + 1],
                    "Vertical edge %d must have non-zero length", i);
        }
    }

    // y >= 0 for all vertices (already from bounds, but keep explicit)
    for (int i = 0; i < N; ++i) {
        ensuref(ys[i] >= 0,
                "All vertices must have y >= 0, but y[%d]=%lld", i, ys[i]);
    }

    // Optional: check that every horizontal segment is "visible from above"
    // i.e., for each horizontal at y=h from x1..x2, there is no other
    // segment of the boundary strictly above it at the same x-range.
    // This matches "when viewed from above, all bottom segments are visible".
    // Implementation: for each x-interval, track minimum y (since y increases downward).
    // But N up to 3e5, and polygon is x-monotone; the given alternating structure with
    // non-decreasing x already implies each x has a single vertical stack-shaped profile,
    // so every horizontal is exposed. Thus no extra heavy check is needed.

    // Compute polygon area to ensure it's positive (non-degenerate),
    // and that total water volume (area) fits in 64-bit integer and is integer-valued.
    long double area2 = 0.0L;
    for (int i = 0; i < N; ++i) {
        int j = (i + 1) % N;
        area2 += (long double)xs[i] * ys[j] - (long double)xs[j] * ys[i];
    }
    long double abs2 = fabsl(area2);
    long double area = abs2 / 2.0L;
    ensuref(area > 0.0L, "Polygon area must be positive (non-degenerate)");

    // Ensure 2*area fits into signed 64-bit and is integer
    // (The real maxima are far below this, but we just sanity check.)
    ensuref(abs2 <= (long double)9e18L,
            "2*area too large, got %Lf", abs2);
    long long twoArea = llround(abs2);
    ensuref(fabsl(abs2 - (long double)twoArea) < 0.5L,
            "2*area must be integer, got %Lf", abs2);
    ensuref(twoArea % 2 == 0,
            "Area must be integer (liters), but 2*area=%lld is odd", twoArea);

    // Read K, number of holes
    int maxK = N / 2;
    int K = inf.readInt(1, maxK, "K");
    inf.readEoln();

    inf.readEof();
}
