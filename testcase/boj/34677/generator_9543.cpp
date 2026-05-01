#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 5);
    int n;
    vector<int> A, B;

    auto makeIdentity = [](int n) {
        vector<int> v(n);
        for (int i = 0; i < n; i++) v[i] = i + 1;
        return v;
    };

    auto randomPerm = [&](int n) {
        vector<int> v = makeIdentity(n);
        ::shuffle(v.begin(), v.end());
        return v;
    };

    switch (type) {
    case 0: { // A and B identical (often k = 1)
        n = rnd.next(1, 8);
        A = makeIdentity(n);
        B = A;
        break;
    }
    case 1: { // A increasing, B reversed (often k = n)
        n = rnd.next(2, 12);
        A = makeIdentity(n);
        B = A;
        reverse(B.begin(), B.end());
        break;
    }
    case 2: { // Both random permutations, small/medium n
        n = rnd.next(1, 20);
        A = randomPerm(n);
        B = randomPerm(n);
        break;
    }
    case 3: { // Block-based: blocks where minima positions match
        n = rnd.next(5, 25);
        A = randomPerm(n);
        B.assign(n, 0);

        int i = 0;
        while (i < n) {
            int maxLen = min(5, n - i);
            int len;
            if (n - i <= 5) len = n - i;
            else len = rnd.next(1, maxLen);

            int l = i;
            int r = i + len - 1;

            // Find position of minimum in this block in A
            int idxMin = l;
            for (int j = l + 1; j <= r; ++j)
                if (A[j] < A[idxMin])
                    idxMin = j;

            B[idxMin] = A[idxMin];
            vector<int> rest;
            for (int j = l; j <= r; ++j)
                if (j != idxMin)
                    rest.push_back(A[j]);

            ::shuffle(rest.begin(), rest.end());
            int p = 0;
            for (int j = l; j <= r; ++j)
                if (j != idxMin)
                    B[j] = rest[p++];

            i = r + 1;
        }
        break;
    }
    case 4: { // Nearly equal permutations (few swaps)
        n = rnd.next(3, 25);
        A = randomPerm(n);
        B = A;
        int swaps = rnd.next(1, max(1, min(4, n / 2)));
        for (int s = 0; s < swaps; ++s) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            while (j == i) j = rnd.next(0, n - 1);
            swap(B[i], B[j]);
        }
        break;
    }
    case 5: { // Medium n: A identity, B random
        n = rnd.next(15, 30);
        A = makeIdentity(n);
        B = randomPerm(n);
        break;
    }
    }

    println(n);
    println(A);
    println(B);

    return 0;
}
