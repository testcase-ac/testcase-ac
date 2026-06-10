#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Constraint {
    char type;
    int a;
    int b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<int> color(n + 1);
    vector<Constraint> edges;

    auto add = [&](char type, int a, int b) {
        edges.push_back({type, a, b});
    };

    for (int i = 1; i <= n; ++i) {
        color[i] = rnd.next(0, 1);
    }

    if (mode == 0) {
        int m = rnd.next(1, 2 * n);
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            add(color[a] == color[b] ? 'S' : 'D', a, b);
        }
    } else if (mode == 1) {
        int m = rnd.next(n - 1, 2 * n);
        for (int i = 2; i <= n; ++i) {
            int parent = rnd.next(1, i - 1);
            add(color[parent] == color[i] ? 'S' : 'D', parent, i);
        }
        while ((int)edges.size() < m) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            add(color[a] == color[b] ? 'S' : 'D', a, b);
        }
    } else if (mode == 2) {
        int a = rnd.next(1, n);
        add('D', a, a);
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n);
            add(rnd.any(string("SD")), x, y);
        }
    } else if (mode == 3) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        add('S', a, b);
        add('D', a, b);
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n);
            add(rnd.any(string("SD")), x, y);
        }
    } else if (mode == 4) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i == center) continue;
            add(rnd.any(string("SD")), center, i);
        }
        int repeats = rnd.next(1, n);
        for (int i = 0; i < repeats; ++i) {
            Constraint e = rnd.any(edges);
            add(e.type, e.a, e.b);
        }
    } else {
        int m = rnd.next(1, 3 * n);
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            if (rnd.next(0, 4) == 0) b = a;
            add(rnd.any(string("SD")), a, b);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const Constraint& e : edges) {
        println(e.type, e.a, e.b);
    }

    return 0;
}
