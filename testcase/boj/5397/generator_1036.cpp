#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

string process(const string& s) {
    vector<char> left, right;
    for (char c : s) {
        if (isalnum(c)) {
            left.push_back(c);
        } else if (c == '<') {
            if (!left.empty()) {
                right.push_back(left.back());
                left.pop_back();
            }
        } else if (c == '>') {
            if (!right.empty()) {
                left.push_back(right.back());
                right.pop_back();
            }
        } else if (c == '-') {
            if (!left.empty()) {
                left.pop_back();
            }
        }
    }
    reverse(right.begin(), right.end());
    return string(left.begin(), left.end()) + string(right.begin(), right.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int T = rnd.next(1, 2); // Generate 1 or 2 test cases
    println(T);
    
    for (int t = 0; t < T; t++) {
        string L;
        do {
            int len = rnd.next(1, 8);
            L.clear();
            for (int i = 0; i < len; i++) {
                int r = rnd.next(1, 100);
                if (r <= 60) { // alphanumeric
                    int type = rnd.next(0, 1);
                    char c;
                    if (type == 0) {
                        c = rnd.next('0', '9');
                    } else if (type == 1) {
                        c = rnd.next('a', 'z');
                    }
                    L += c;
                } else if (r <= 75) {
                    L += '<';
                } else if (r <= 90) {
                    L += '>';
                } else {
                    L += '-';
                }
            }
        } while (process(L).empty());
        
        println(L);
    }
    
    return 0;
}
