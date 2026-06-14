#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomChar(int alphabetSize) {
    return static_cast<char>('a' + rnd.next(0, alphabetSize - 1));
}

string randomString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(randomChar(alphabetSize));
    }
    return s;
}

string alternatingString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    char a = randomChar(alphabetSize);
    char b = randomChar(alphabetSize);
    if (alphabetSize > 1) {
        while (b == a) {
            b = randomChar(alphabetSize);
        }
    }
    for (int i = 0; i < n; ++i) {
        s.push_back(i % 2 == 0 ? a : b);
    }
    return s;
}

string runHeavyString(int n, int alphabetSize) {
    string s;
    while (static_cast<int>(s.size()) < n) {
        char c = randomChar(alphabetSize);
        int len = rnd.next(1, min(6, n - static_cast<int>(s.size())));
        s.append(len, c);
    }
    return s;
}

string palindromeBlockString(int n, int alphabetSize) {
    string s;
    while (static_cast<int>(s.size()) < n) {
        int remaining = n - static_cast<int>(s.size());
        int blockType = rnd.next(0, 3);
        if (blockType == 0 && remaining >= 2) {
            char c = randomChar(alphabetSize);
            s.push_back(c);
            s.push_back(c);
        } else if (blockType == 1 && remaining >= 3) {
            char outer = randomChar(alphabetSize);
            char middle = randomChar(alphabetSize);
            if (alphabetSize > 1) {
                while (middle == outer) {
                    middle = randomChar(alphabetSize);
                }
            }
            s.push_back(outer);
            s.push_back(middle);
            s.push_back(outer);
        } else if (blockType == 2 && remaining >= 4) {
            char a = randomChar(alphabetSize);
            char b = randomChar(alphabetSize);
            s.push_back(a);
            s.push_back(b);
            s.push_back(b);
            s.push_back(a);
        } else {
            s.push_back(randomChar(alphabetSize));
        }
    }
    return s;
}

string stackAwareString(int n, int alphabetSize) {
    string s;
    vector<char> stack;
    s.reserve(n);
    stack.reserve(n);

    for (int i = 0; i < n; ++i) {
        int action = rnd.next(0, 99);
        char c;
        if (!stack.empty() && action < 35) {
            c = stack.back();
        } else if (stack.size() >= 2 && action < 70) {
            c = stack[stack.size() - 2];
        } else {
            c = randomChar(alphabetSize);
        }

        s.push_back(c);
        if (!stack.empty() && stack.back() == c) {
            stack.pop_back();
        } else if (stack.size() >= 2 && stack[stack.size() - 2] == c) {
            stack.pop_back();
            stack.pop_back();
        } else {
            stack.push_back(c);
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(60, 200);
    } else {
        n = rnd.next(1, 40);
    }
    int alphabetSize = rnd.next(1, 8);

    string s;
    if (mode == 0) {
        s = randomString(n, alphabetSize);
    } else if (mode == 1) {
        s = alternatingString(n, max(2, alphabetSize));
    } else if (mode == 2) {
        s = runHeavyString(n, alphabetSize);
    } else if (mode == 3) {
        s = palindromeBlockString(n, alphabetSize);
    } else if (mode == 4) {
        s = stackAwareString(n, alphabetSize);
    } else {
        string prefix = randomString(rnd.next(0, min(10, n)), alphabetSize);
        string suffix = randomString(n - static_cast<int>(prefix.size()), alphabetSize);
        reverse(suffix.begin(), suffix.end());
        s = prefix + suffix;
    }

    println(static_cast<int>(s.size()));
    println(s);

    return 0;
}
