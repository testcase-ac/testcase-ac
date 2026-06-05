#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

string randomLetters(int len) {
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result;
    result.reserve(len);
    for (int i = 0; i < len; ++i) {
        result += rnd.any(letters);
    }
    return result;
}

string randomInteger() {
    int len = rnd.next(1, 17);
    string result;
    result.reserve(len);
    result += char('1' + rnd.next(9));
    for (int i = 1; i < len; ++i) {
        result += char('0' + rnd.next(10));
    }
    return result;
}

string makeObject(const vector<string>& elements) {
    string result = "[ ";
    for (const string& element : elements) {
        result += element;
        result += ' ';
    }
    result += ']';
    return result;
}

string makeElement(int depth);

string makeRandomObject(int depth) {
    if (depth <= 0 || rnd.next(100) < 12) {
        return makeObject({});
    }

    int count = rnd.next(1, depth >= 4 ? 6 : 4);
    vector<string> elements;
    elements.reserve(count);
    for (int i = 0; i < count; ++i) {
        elements.push_back(makeElement(depth - 1));
    }
    return makeObject(elements);
}

string makeElement(int depth) {
    int kind = rnd.next(100);
    if (depth > 0 && kind < 35) {
        return makeRandomObject(depth);
    }
    if (kind < 65) {
        return randomInteger();
    }

    int len = rnd.next(1, rnd.next(100) < 20 ? 40 : 12);
    return randomLetters(len);
}

string makeDeepObject() {
    int depth = rnd.next(3, 12);
    string current = rnd.next(2) == 0 ? randomLetters(rnd.next(1, 8)) : randomInteger();
    for (int i = 0; i < depth; ++i) {
        vector<string> elements;
        if (rnd.next(100) < 35) {
            elements.push_back(makeObject({}));
        }
        elements.push_back(current);
        if (rnd.next(100) < 45) {
            elements.push_back(makeElement(1));
        }
        current = makeObject(elements);
    }
    return current;
}

string makeFlatObject() {
    int count = rnd.next(1, 18);
    vector<string> elements;
    elements.reserve(count);
    for (int i = 0; i < count; ++i) {
        int kind = rnd.next(100);
        if (kind < 15) {
            elements.push_back(makeObject({}));
        } else if (kind < 55) {
            elements.push_back(randomInteger());
        } else {
            elements.push_back(randomLetters(rnd.next(1, 18)));
        }
    }
    return makeObject(elements);
}

string makeBoundaryObject() {
    vector<string> elements;
    elements.push_back(makeObject({}));
    elements.push_back("1");
    elements.push_back("9");
    elements.push_back("99999999999999999");
    elements.push_back(randomLetters(rnd.next(24, 60)));
    elements.push_back(makeRandomObject(3));
    shuffle(elements.begin(), elements.end());
    return makeObject(elements);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string ason;
    int mode = rnd.next(5);
    if (mode == 0) {
        ason = makeObject({});
    } else if (mode == 1) {
        ason = makeFlatObject();
    } else if (mode == 2) {
        ason = makeDeepObject();
    } else if (mode == 3) {
        ason = makeBoundaryObject();
    } else {
        ason = makeRandomObject(rnd.next(2, 6));
    }

    println(ason);
    return 0;
}
