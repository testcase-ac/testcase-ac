#include "testlib.h"
#include <vector>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of islands
    int N = rnd.next(2, 10);
    // Number of events
    int Q = rnd.next(1, 20);

    // Track existing bridges
    vector<pair<int,int>> existing;
    vector<vector<bool>> exist(N, vector<bool>(N, false));

    int queryCount = 0;
    vector<tuple<int,int,int,int>> events; // (type, X, Y, V)

    for (int i = 0; i < Q; i++) {
        // Ensure at least one query
        bool forceQuery = (i == Q-1 && queryCount == 0);
        int type;
        if (forceQuery) {
            type = 2;
        } else {
            // Hyper-parameters for probabilities
            double x1 = rnd.next();
            double x2 = rnd.next();
            double p_add = x1;
            double p_rem = x2 * (1 - p_add);
            double p_q = 1 - p_add - p_rem;

            int maxPairs = N*(N-1)/2;
            int canAdd = maxPairs - (int)existing.size();
            int canRem = existing.size();

            // If no space to add
            if (canAdd == 0) {
                p_add = 0;
                double s = p_rem + p_q;
                if (s > 0) {
                    p_rem /= s;
                    p_q   /= s;
                } else {
                    p_rem = p_q = 0.5;
                }
            }
            // If nothing to remove
            if (canRem == 0) {
                p_rem = 0;
                double s = p_add + p_q;
                if (s > 0) {
                    p_add /= s;
                    p_q   /= s;
                } else {
                    p_add = p_q = 0.5;
                }
            }

            double r = rnd.next();
            if (r < p_add) type = 0;
            else if (r < p_add + p_rem) type = 1;
            else type = 2;
        }

        int X, Y, V;
        if (type == 0) {
            // Add a bridge
            vector<pair<int,int>> cand;
            for (int a = 0; a < N; a++)
                for (int b = a+1; b < N; b++)
                    if (!exist[a][b])
                        cand.emplace_back(a, b);
            auto pr = rnd.any(cand);
            X = pr.first; 
            Y = pr.second;
            V = rnd.next(0, 9);
            exist[X][Y] = exist[Y][X] = true;
            existing.emplace_back(X, Y);
        } else if (type == 1) {
            // Remove a bridge
            auto pr = rnd.any(existing);
            X = pr.first;
            Y = pr.second;
            V = 0;
            exist[X][Y] = exist[Y][X] = false;
            for (auto it = existing.begin(); it != existing.end(); ++it) {
                if (it->first == X && it->second == Y) {
                    existing.erase(it);
                    break;
                }
            }
        } else {
            // Query safest path
            queryCount++;
            X = rnd.next(0, N-1);
            Y = rnd.next(0, N-2);
            if (Y >= X) Y++;
            V = 0;
        }

        events.emplace_back(type, X, Y, V);
    }

    // Output
    println(N, Q);
    for (auto &e : events) {
        int t, x, y, v;
        tie(t, x, y, v) = e;
        if (t == 0) println(0, x, y, v);
        else println(t, x, y);
    }

    return 0;
}
