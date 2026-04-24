#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small grid dimensions, at least 3 cells
    int r, c;
    do {
        r = rnd.next(1, 3);
        c = rnd.next(2, 5);
    } while (r * c < 3);
    int cells = r * c;
    // Build pool of available keys (excluding '*')
    vector<char> pool;
    for (char ch = 'A'; ch <= 'Z'; ++ch) pool.push_back(ch);
    for (char ch = '0'; ch <= '9'; ++ch) pool.push_back(ch);
    pool.push_back('-');
    // Shuffle and pick cells-1 unique keys
    shuffle(pool.begin(), pool.end());
    vector<char> keys;
    for (int i = 0; i < cells - 1; ++i) {
        keys.push_back(pool[i]);
    }
    // Add the Enter key '*'
    keys.push_back('*');
    // Shuffle all keys and fill the grid
    shuffle(keys.begin(), keys.end());
    vector<string> grid(r, string(c, '?'));
    int idx = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            grid[i][j] = keys[idx++];
        }
    }
    // Generate text to type: length hyperparameter via weighted next
    int tParam = rnd.next(-2, 2);
    int len0 = rnd.wnext(20, tParam); // 0..19
    int n = len0 + 1;                 // 1..20
    // Collect non-* keys for text
    vector<char> textKeys;
    for (char ch : keys) if (ch != '*') textKeys.push_back(ch);
    // Build text
    string text;
    for (int i = 0; i < n; ++i) {
        text.push_back(rnd.any(textKeys));
    }
    // Output
    println(r, c);
    for (int i = 0; i < r; ++i) {
        printf("%s\n", grid[i].c_str());
    }
    printf("%s\n", text.c_str());
    return 0;
}
