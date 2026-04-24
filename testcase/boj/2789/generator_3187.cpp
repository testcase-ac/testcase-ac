#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Characters to remove and keep
    string remove_str = "CAMBRIDGE";
    vector<char> remove_chars(remove_str.begin(), remove_str.end());
    vector<char> keep_chars;
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (remove_str.find(c) == string::npos)
            keep_chars.push_back(c);
    }
    // Length of the word
    int len = rnd.next(3, 20);
    // Hyper-parameter to bias removal ratio
    int t = rnd.next(-2, 2);
    int ratio_idx = rnd.wnext(101, t); // 0..100, biased
    double ratio = ratio_idx / 100.0;
    int R = int(len * ratio);
    if (R < 0) R = 0;
    if (R > len - 1) R = len - 1;
    // Ensure at least one character remains
    if (len - R < 1) R = len - 1;
    int K = len - R;
    // Build the word
    vector<char> v;
    for (int i = 0; i < R; ++i)
        v.push_back(rnd.any(remove_chars));
    for (int i = 0; i < K; ++i)
        v.push_back(rnd.any(keep_chars));
    shuffle(v.begin(), v.end());
    // Convert to string
    string s;
    for (char c : v) s.push_back(c);
    // Output
    printf("%s\n", s.c_str());
    return 0;
}
