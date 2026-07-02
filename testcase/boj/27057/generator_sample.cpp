#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

static vector<int> randomMovie(int n, int minSize, int maxSize) {
    int size = rnd.next(minSize, maxSize);
    vector<int> cows;
    for (int cow = 1; cow <= n; ++cow) {
        cows.push_back(cow);
    }
    shuffle(cows.begin(), cows.end());
    cows.resize(size);
    sort(cows.begin(), cows.end());
    return cows;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(6, 14);
    } else {
        n = rnd.next(2, 20);
    }

    vector<vector<int>> movies;

    if (mode == 0) {
        vector<int> all;
        for (int cow = 1; cow <= n; ++cow) {
            all.push_back(cow);
        }
        movies.push_back(all);
    } else if (mode == 1) {
        for (int cow = 2; cow <= n; ++cow) {
            movies.push_back({cow - 1, cow});
        }
    } else if (mode == 2) {
        for (int cow = 2; cow <= n; ++cow) {
            movies.push_back({1, cow});
        }
    } else {
        set<int> reached;
        reached.insert(1);
        for (int cow = 2; cow <= n; ++cow) {
            int anchor = rnd.any(reached);
            movies.push_back({anchor, cow});
            reached.insert(cow);
        }
    }

    int extra = rnd.next(0, max(1, 2 * n));
    for (int i = 0; i < extra; ++i) {
        int maxSize = min(n, rnd.next(2, min(n, 8)));
        movies.push_back(randomMovie(n, 2, maxSize));
    }

    shuffle(movies.begin(), movies.end());

    println(n, static_cast<int>(movies.size()));
    for (vector<int>& movie : movies) {
        println(static_cast<int>(movie.size()), movie);
    }

    return 0;
}
