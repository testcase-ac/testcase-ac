#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct Movie {
    int duration;
    vector<int> starts;
};

vector<int> randomStarts(int count, int l, const vector<int>& required) {
    set<int> values(required.begin(), required.end());
    while ((int)values.size() < count) {
        int bucket = rnd.next(0, 4);
        int value;
        if (bucket == 0) value = rnd.next(0, min(l, 8));
        else if (bucket == 1) value = rnd.next(max(0, l - 8), l);
        else value = rnd.next(0, l);
        values.insert(value);
    }
    return vector<int>(values.begin(), values.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int l = rnd.next(1, 160);
    int n = rnd.next(1, 8);
    vector<Movie> movies;

    if (mode == 0) {
        n = rnd.next(2, 7);
        vector<int> cuts = {0, l};
        while ((int)cuts.size() < n + 1) cuts.push_back(rnd.next(0, l));
        sort(cuts.begin(), cuts.end());
        cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
        n = (int)cuts.size() - 1;

        for (int i = 0; i < n; ++i) {
            int start = cuts[i];
            int need = max(1, cuts[i + 1] - cuts[i]);
            int duration = rnd.next(need, l);
            int c = rnd.next(1, 5);
            movies.push_back({duration, randomStarts(c, l, {start})});
        }
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        int forbiddenPrefix = rnd.next(1, min(l, 30));
        for (int i = 0; i < n; ++i) {
            int duration = rnd.next(1, l);
            int c = rnd.next(1, min(5, l - forbiddenPrefix + 1));
            vector<int> starts;
            for (int j = 0; j < c; ++j) {
                starts.push_back(rnd.next(forbiddenPrefix, l));
            }
            sort(starts.begin(), starts.end());
            starts.erase(unique(starts.begin(), starts.end()), starts.end());
            while ((int)starts.size() < c) {
                starts.push_back(rnd.next(forbiddenPrefix, l));
                sort(starts.begin(), starts.end());
                starts.erase(unique(starts.begin(), starts.end()), starts.end());
            }
            movies.push_back({duration, starts});
        }
    } else if (mode == 2) {
        n = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            int duration = rnd.next(1, l);
            int c = rnd.next(1, min(10, l + 1));
            vector<int> required;
            if (rnd.next(0, 1)) required.push_back(0);
            if (rnd.next(0, 1)) required.push_back(l);
            movies.push_back({duration, randomStarts(max(c, (int)required.size()), l, required)});
        }
    } else {
        l = rnd.any(vector<int>{1, 2, 100000000});
        n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            int duration = rnd.next(1, l);
            int c = rnd.next(1, min(6, l + 1));
            movies.push_back({duration, randomStarts(c, l, {0})});
        }
    }

    println(n, l);
    for (const Movie& movie : movies) {
        printf("%d %d", movie.duration, (int)movie.starts.size());
        for (int start : movie.starts) printf(" %d", start);
        printf("\n");
    }

    return 0;
}
