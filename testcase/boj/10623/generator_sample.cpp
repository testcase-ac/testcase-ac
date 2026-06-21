#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = (mode == 0) ? 1 : rnd.next(2, 35);
    vector<int> parent(n + 1);

    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i - 1;
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = 1;
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 2; i <= spine; ++i) {
            parent[i] = i - 1;
        }
        for (int i = spine + 1; i <= n; ++i) {
            parent[i] = rnd.next(1, spine);
        }
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i / 2;
        }
    } else if (mode == 5) {
        vector<int> layerStart = {1};
        int nextVertex = 2;
        while (nextVertex <= n) {
            int layerSize = min(n - nextVertex + 1, rnd.next(1, 6));
            int previousStart = layerStart.back();
            int previousEnd = nextVertex - 1;
            layerStart.push_back(nextVertex);
            for (int i = 0; i < layerSize; ++i) {
                int v = nextVertex + i;
                parent[v] = rnd.next(previousStart, previousEnd);
            }
            nextVertex += layerSize;
        }
    } else if (mode == 6) {
        for (int i = 2; i <= n; ++i) {
            int bias = rnd.next(-2, 3);
            parent[i] = rnd.wnext(i - 1, bias) + 1;
        }
    }

    println(n);
    if (n > 1) {
        vector<int> parents;
        for (int i = 2; i <= n; ++i) {
            parents.push_back(parent[i]);
        }
        println(parents);
    }

    return 0;
}
