#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string tracks = "CSIA";
    int mode = rnd.next(0, 5);
    int n = 1;
    char target = rnd.any(tracks);
    vector<char> friends;

    if (mode == 0) {
        n = rnd.next(1, 4);
        target = rnd.any(tracks);
        for (int i = 0; i < n; ++i) {
            friends.push_back(rnd.any(tracks));
        }
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        target = rnd.any(tracks);
        friends.assign(n, target);
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        target = rnd.any(tracks);
        vector<char> others;
        for (char c : tracks) {
            if (c != target) {
                others.push_back(c);
            }
        }
        for (int i = 0; i < n; ++i) {
            friends.push_back(rnd.any(others));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 40);
        target = rnd.any(tracks);
        for (int i = 0; i < n; ++i) {
            friends.push_back(rnd.next(0, 2) == 0 ? target : rnd.any(tracks));
        }
    } else if (mode == 4) {
        n = rnd.next(4, 32);
        vector<char> pool;
        for (char c : tracks) {
            int repeat = rnd.next(1, 4);
            for (int i = 0; i < repeat; ++i) {
                pool.push_back(c);
            }
        }
        target = rnd.any(tracks);
        for (int i = 0; i < n; ++i) {
            friends.push_back(rnd.any(pool));
        }
    } else {
        n = rnd.next(20, 100);
        target = rnd.any(tracks);
        for (int i = 0; i < n; ++i) {
            friends.push_back(rnd.any(tracks));
        }
    }

    shuffle(friends.begin(), friends.end());

    println(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << friends[i];
    }
    cout << '\n';
    println(string(1, target));

    return 0;
}
