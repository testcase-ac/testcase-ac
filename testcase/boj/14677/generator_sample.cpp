#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char expectedAt(int eaten) {
    static const string cycle = "BLD";
    return cycle[eaten % 3];
}

string randomString(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

string cycleString(int len, int offset) {
    static const string cycle = "BLD";
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(cycle[(i + offset) % 3]);
    }
    return s;
}

string dequeConsumableString(int n) {
    int len = 3 * n;
    string result(len, '?');
    int left = 0;
    int right = len - 1;
    for (int eaten = 0; eaten < len; ++eaten) {
        char need = expectedAt(eaten);
        if (rnd.next(2) == 0) {
            result[left++] = need;
        } else {
            result[right--] = need;
        }
    }
    return result;
}

string blockedAfterPrefixString(int n) {
    int len = 3 * n;
    int prefix = rnd.next(0, min(len, 18));
    string s(len, '?');
    int left = 0;
    int right = len - 1;

    for (int eaten = 0; eaten < prefix && left <= right; ++eaten) {
        char need = expectedAt(eaten);
        if (rnd.next(2) == 0) {
            s[left++] = need;
        } else {
            s[right--] = need;
        }
    }

    char blocker = expectedAt(prefix);
    string choices = "BLD";
    choices.erase(remove(choices.begin(), choices.end(), blocker), choices.end());
    while (left <= right) {
        s[left++] = rnd.any(choices);
    }
    return s;
}

int chooseN() {
    int bucket = rnd.next(100);
    if (bucket < 70) {
        return rnd.next(1, 10);
    }
    if (bucket < 93) {
        return rnd.next(11, 60);
    }
    return rnd.next(120, 500);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = chooseN();
    int len = 3 * n;
    int mode = rnd.next(7);
    string medicines;

    if (mode == 0) {
        medicines = cycleString(len, 0);
    } else if (mode == 1) {
        medicines = cycleString(len, rnd.next(0, 2));
        if (rnd.next(2)) {
            reverse(medicines.begin(), medicines.end());
        }
    } else if (mode == 2) {
        medicines = dequeConsumableString(n);
    } else if (mode == 3) {
        medicines = blockedAfterPrefixString(n);
    } else if (mode == 4) {
        vector<char> chars = {'B', 'L', 'D'};
        shuffle(chars.begin(), chars.end());
        int firstRun = rnd.next(1, len);
        medicines.assign(firstRun, chars[0]);
        medicines += randomString(len - firstRun, string(chars.begin() + 1, chars.end()));
    } else if (mode == 5) {
        string half = randomString((len + 1) / 2, "BLD");
        medicines = half;
        for (int i = len / 2 - 1; (int)medicines.size() < len && i >= 0; --i) {
            medicines.push_back(half[i]);
        }
    } else {
        string alphabet = rnd.next(100) < 45 ? "BLD" : string(1, rnd.any(string("BLD")));
        medicines = randomString(len, alphabet);
    }

    println(n);
    println(medicines);
    return 0;
}
