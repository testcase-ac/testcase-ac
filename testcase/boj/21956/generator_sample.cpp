#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

string reduceString(const string& s, int k) {
    vector<pair<char, int>> groups;
    for (char c : s) {
        if (!groups.empty() && groups.back().first == c) {
            ++groups.back().second;
        } else {
            groups.push_back({c, 1});
        }

        if (groups.back().second == k) {
            groups.pop_back();
        }
    }

    string result;
    for (auto [c, count] : groups) {
        result.append(count, c);
    }
    return result;
}

char nextChar(char c) {
    return c == 'z' ? 'a' : static_cast<char>(c + 1);
}

string randomSafeString(int n, int k, const string& alphabet) {
    string s;
    while (static_cast<int>(s.size()) < n) {
        char c = rnd.any(alphabet);
        int limit = 1;
        if (!s.empty() && s.back() == c) {
            int tail = 0;
            for (int i = static_cast<int>(s.size()) - 1; i >= 0 && s[i] == c; --i) {
                ++tail;
            }
            limit = max(1, k - 1 - tail);
        } else {
            limit = k - 1;
        }
        int add = rnd.next(1, min(limit, n - static_cast<int>(s.size())));
        s.append(add, c);
    }
    return s;
}

string makeCase(int n, int k, int mode) {
    string alphabet = "abcde";
    if (mode == 0) {
        return randomSafeString(n, k, alphabet.substr(0, rnd.next(2, 5)));
    }

    if (mode == 1) {
        char erase = rnd.any(alphabet);
        char keep = nextChar(erase);
        int left = rnd.next(1, min(k - 1, n - k - 1));
        int right = n - k - left;
        string s(left, keep);
        s.append(k, erase);
        for (int i = 0; i < right; ++i) {
            s.push_back(i % 2 == 0 ? nextChar(keep) : keep);
        }
        return s;
    }

    if (mode == 2) {
        char edge = rnd.any(alphabet);
        char middle = nextChar(edge);
        int left = rnd.next(1, k - 1);
        int right = k - left;
        string s(left, edge);
        s.append(k, middle);
        s.append(right, edge);
        while (static_cast<int>(s.size()) < n) {
            s.push_back(rnd.any(string("cdefg")));
        }
        s.resize(n);
        return s;
    }

    string s;
    while (static_cast<int>(s.size()) < n) {
        char c = rnd.any(alphabet);
        int len = rnd.next(1, min(k, n - static_cast<int>(s.size())));
        s.append(len, c);
        if (static_cast<int>(s.size()) < n && s.back() == c) {
            s.push_back(nextChar(c));
        }
    }
    s.resize(n);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    for (int attempt = 0; attempt < 1000; ++attempt) {
        int k = rnd.next(2, 8);
        int n = rnd.next(k + 2, 35);
        int mode = rnd.next(4);
        string s = makeCase(n, k, mode);
        if (static_cast<int>(s.size()) != n || reduceString(s, k).empty()) {
            continue;
        }

        println(n, k);
        println(s);
        return 0;
    }

    println(2, 2);
    println("ab");
    return 0;
}
