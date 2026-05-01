#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose game type
    string games = "YFO";
    char g = games[rnd.next(0, 2)];
    int k; // number of *other* players per game
    if (g == 'Y') k = 1;
    else if (g == 'F') k = 2;
    else k = 3; // 'O'

    int pattern = rnd.next(0, 4);
    int U, N;

    // Decide unique count U and total requests N
    switch (pattern) {
        case 0: {
            // All unique, small to medium size
            U = rnd.next(1, 10);
            N = U;
            break;
        }
        case 1: {
            // Heavy duplication: few unique names, more total requests
            U = rnd.next(1, 5);
            N = rnd.next(U, 40);
            break;
        }
        case 2: {
            // Moderate duplicates, U near N
            N = rnd.next(5, 40);
            U = rnd.next(max(1, N / 2), N);
            break;
        }
        case 3: {
            // U is exact multiple of k (edge on division)
            int m = rnd.next(1, 6);
            U = m * k;
            if (U < 1) U = 1;
            if (U > 40) U = 40;
            N = rnd.next(U, 40);
            break;
        }
        default: {
            // U around multiple of k: just below, exact, or just above
            int m = rnd.next(1, 5);
            int base = m * k;
            int deltaOptions[3] = {-1, 0, 1};
            int delta = deltaOptions[rnd.next(0, 2)];
            U = base + delta;
            if (U < 1) U = 1;
            if (U > 40) U = 40;
            N = rnd.next(U, 40);
            break;
        }
    }

    // Safety: ensure constraints
    if (N < 1) N = 1;
    if (U < 1) U = 1;
    if (U > N) U = N;
    if (N > 40) N = 40;

    // Base name pool with meaningful & varied examples
    vector<string> basePool = {
        "lms0806", "exponentiale", "jthis", "leo020630",
        "powergee", "skeep194", "tony9402", "wider93",
        "mageek2guanaah", "Alice", "Bob", "Carol",
        "A", "B", "C", "X1", "Z9", "user01", "playerX"
    };
    shuffle(basePool.begin(), basePool.end());

    vector<string> uniqueNames;
    // Take from pool first
    for (int i = 0; i < (int)basePool.size() && (int)uniqueNames.size() < U; ++i) {
        uniqueNames.push_back(basePool[i]);
    }

    auto exists = [&](const string &s) {
        for (const string &t : uniqueNames)
            if (t == s) return true;
        return false;
    };

    // Generate additional random names if needed
    string alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while ((int)uniqueNames.size() < U) {
        int len = rnd.next(1, 10);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; ++i)
            s += alphabet[rnd.next(0, (int)alphabet.size() - 1)];
        if (!exists(s))
            uniqueNames.push_back(s);
    }

    // Build request list: ensure each unique name appears at least once
    vector<string> requests = uniqueNames; // first U requests are all distinct
    for (int i = U; i < N; ++i) {
        requests.push_back(rnd.any(uniqueNames));
    }
    shuffle(requests.begin(), requests.end());

    // Output
    println(N, g);
    for (int i = 0; i < N; ++i)
        println(requests[i]);

    return 0;
}
