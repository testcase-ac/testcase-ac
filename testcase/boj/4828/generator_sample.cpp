#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

string tagName() {
    int len = rnd.next(1, 5);
    string chars = "abcdefghijklmnopqrstuvwxyz0123456789";
    string tag;
    for (int i = 0; i < len; ++i) {
        tag += rnd.any(chars);
    }
    return tag;
}

string plainText(int maxLen) {
    int len = rnd.next(0, maxLen);
    string chars = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:;!?+-*/()[]_";
    string text;
    for (int i = 0; i < len; ++i) {
        text += rnd.any(chars);
    }
    return text;
}

string hexEntity() {
    int bytes = rnd.next(1, 3);
    string digits = "0123456789ABCDEF";
    string entity = "&x";
    for (int i = 0; i < bytes * 2; ++i) {
        entity += rnd.any(digits);
    }
    entity += ";";
    return entity;
}

string validElement(int depth) {
    if (depth == 0 || rnd.next(0, 3) == 0) {
        string tag = tagName();
        return "<" + tag + "/>";
    }

    string tag = tagName();
    string body = plainText(8);
    int parts = rnd.next(1, 3);
    for (int i = 0; i < parts; ++i) {
        int kind = rnd.next(0, 4);
        if (kind == 0) {
            body += "&lt;";
        } else if (kind == 1) {
            body += "&gt;";
        } else if (kind == 2) {
            body += "&amp;";
        } else if (kind == 3) {
            body += hexEntity();
        } else {
            body += validElement(depth - 1);
        }
        body += plainText(5);
    }
    return "<" + tag + ">" + body + "</" + tag + ">";
}

string validDocument() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return plainText(20);
    }
    if (mode == 1) {
        return plainText(8) + rnd.any(vector<string>{"&lt;", "&gt;", "&amp;", hexEntity()}) + plainText(8);
    }

    string doc;
    int parts = rnd.next(1, 4);
    for (int i = 0; i < parts; ++i) {
        if (rnd.next(0, 1) == 0) {
            doc += plainText(6);
        } else {
            doc += validElement(rnd.next(1, 3));
        }
    }
    return doc;
}

string invalidDocument() {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return plainText(8) + "&" + plainText(8);
    }
    if (mode == 1) {
        return plainText(8) + "<" + tagName() + plainText(5);
    }
    if (mode == 2) {
        return plainText(8) + ">" + plainText(8);
    }
    if (mode == 3) {
        string tag = tagName();
        return "<" + tag + ">" + plainText(8);
    }
    if (mode == 4) {
        string open = tagName();
        string close = tagName();
        while (close == open) {
            close = tagName();
        }
        return "<" + open + ">" + plainText(6) + "</" + close + ">";
    }
    return plainText(6) + "&x" + string(rnd.next(1, 2) * 2 - 1, 'A') + ";" + plainText(6);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int lines = rnd.next(1, 12);
    for (int i = 0; i < lines; ++i) {
        int kind = rnd.next(0, 9);
        if (kind == 0) {
            println("");
        } else if (kind <= 5) {
            println(validDocument());
        } else {
            println(invalidDocument());
        }
    }

    return 0;
}
