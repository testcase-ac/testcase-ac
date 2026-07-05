#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

struct Line {
    int A;
    int B;
    int C;
};

bool parallel(const Line& x, const Line& y) {
    return x.A * y.B == y.A * x.B;
}

bool sameLine(const Line& x, const Line& y) {
    int g1 = gcd(gcd(abs(x.A), abs(x.B)), abs(x.C));
    int g2 = gcd(gcd(abs(y.A), abs(y.B)), abs(y.C));
    int ax = x.A / g1, bx = x.B / g1, cx = x.C / g1;
    int ay = y.A / g2, by = y.B / g2, cy = y.C / g2;
    if (ax < 0 || (ax == 0 && bx < 0) || (ax == 0 && bx == 0 && cx < 0)) {
        ax = -ax;
        bx = -bx;
        cx = -cx;
    }
    if (ay < 0 || (ay == 0 && by < 0) || (ay == 0 && by == 0 && cy < 0)) {
        ay = -ay;
        by = -by;
        cy = -cy;
    }
    return ax == ay && bx == by && cx == cy;
}

bool createsConcurrentTriple(const vector<Line>& lines, const Line& candidate) {
    for (int i = 0; i < (int)lines.size(); ++i) {
        if (sameLine(lines[i], candidate)) {
            return true;
        }
        for (int j = 0; j < i; ++j) {
            if (parallel(lines[i], lines[j])) {
                continue;
            }
            long long det =
                1LL * lines[i].A * lines[j].B * candidate.C +
                1LL * lines[i].B * lines[j].C * candidate.A +
                1LL * lines[i].C * lines[j].A * candidate.B -
                1LL * lines[i].C * lines[j].B * candidate.A -
                1LL * lines[i].B * lines[j].A * candidate.C -
                1LL * lines[i].A * lines[j].C * candidate.B;
            if (det == 0) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of lines
    int N = rnd.next(1, 10);

    vector<Line> lines;
    for (int attempt = 0; attempt < 1000 && (int)lines.size() != N; ++attempt) {
        lines.clear();
        // Number of parallel families
        int K = rnd.next(1, N);
        // Partition N into K positive sizes
        vector<int> sizes(K, 1);
        int extra = N - K;
        while (extra > 0) {
            int i = rnd.next(0, K-1);
            sizes[i]++;
            extra--;
        }
        // Generate direction normals for each family
        set<pair<int,int>> used_dirs;
        vector<pair<pair<int,int>, int>> families; // ((A,B), size)
        for (int i = 0; i < K; i++) {
            int A, B;
            // pick some horizontals/verticals/general for diversity
            double p = rnd.next();
            if (p < 0.3) {
                A = 0; B = 1;
            } else if (p < 0.6) {
                A = 1; B = 0;
            } else {
                // general direction
                do {
                    A = rnd.next(-5, 5);
                    B = rnd.next(-5, 5);
                } while (A == 0 && B == 0);
                int g = gcd(abs(A), abs(B));
                A /= g; B /= g;
            }
            // normalize sign
            if (A < 0 || (A == 0 && B < 0)) {
                A = -A; B = -B;
            }
            // ensure uniqueness
            if (used_dirs.count({A, B})) {
                // retry until new
                i--;
                continue;
            }
            used_dirs.insert({A, B});
            families.push_back({{A, B}, sizes[i]});
        }
        shuffle(families.begin(), families.end());

        bool ok = true;
        for (auto &fam : families) {
            int A = fam.first.first;
            int B = fam.first.second;
            set<int> triedC;
            for (int t = 0; t < fam.second; t++) {
                bool placed = false;
                for (int tries = 0; tries < 200 && !placed; ++tries) {
                    int C = rnd.next(-30, 30);
                    if (triedC.count(C)) {
                        continue;
                    }
                    triedC.insert(C);
                    Line candidate{A, B, C};
                    if (!createsConcurrentTriple(lines, candidate)) {
                        lines.push_back(candidate);
                        placed = true;
                    }
                }
                if (!placed) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                break;
            }
        }
    }

    ensuref((int)lines.size() == N, "failed to generate valid line set");

    // Shuffle order
    shuffle(lines.begin(), lines.end());
    // Output
    println(N);
    for (auto &l : lines) {
        println(l.A, l.B, l.C);
    }
    return 0;
}
