#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Book {
    string title;
    int pages;
};

struct Gift {
    int time;
    string title;
    int pages;
};

static string quoted(const string& title) {
    return "\"" + title + "\"";
}

static int randomPages() {
    int mode = rnd.next(0, 3);
    if (mode == 0) return rnd.next(1, 9);
    if (mode == 1) return rnd.next(10, 120);
    if (mode == 2) return rnd.next(90000, 99999);
    return rnd.next(1, 99999);
}

static string titleFrom(const vector<string>& pool, int index) {
    string title = pool[index % (int)pool.size()];
    if (index >= (int)pool.size()) {
        title += " ";
        title += char('0' + (index / (int)pool.size()) % 10);
    }
    return title;
}

static void addInitial(vector<Book>& books, const vector<string>& pool, int& pos) {
    books.push_back({titleFrom(pool, pos++), randomPages()});
}

static void addGift(vector<Gift>& gifts, const vector<string>& pool, int& pos, int time) {
    gifts.push_back({time, titleFrom(pool, pos++), randomPages()});
}

static void addMixedInitial(vector<Book>& books, const vector<string>& beforeJane,
                            const vector<string>& afterJane, int& beforePos, int& afterPos) {
    if (rnd.next(0, 1) == 0) {
        addInitial(books, beforeJane, beforePos);
    } else {
        addInitial(books, afterJane, afterPos);
    }
}

static void addMixedGift(vector<Gift>& gifts, const vector<string>& beforeJane,
                         const vector<string>& afterJane, int& beforePos, int& afterPos,
                         int time) {
    if (rnd.next(0, 1) == 0) {
        addGift(gifts, beforeJane, beforePos, time);
    } else {
        addGift(gifts, afterJane, afterPos, time);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> beforeJane = {
        "A", "B 2", "Don Quixote", "Great Gatsby", "Jane Adams", "Jane Eyq"
    };
    vector<string> afterJane = {
        "Jane Eys", "Jane Z", "Moby Dick", "Pride 1813", "Z", "z Last"
    };
    vector<string> earlyDigits = {"0", "1 Book", "42", "8 Pages"};

    vector<Book> initial;
    vector<Gift> gifts;
    int beforePos = 0;
    int afterPos = 0;
    int digitPos = 0;

    int mode = rnd.next(0, 5);
    int janePages = randomPages();

    if (mode == 0) {
        int n = rnd.next(0, 2);
        int m = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) addInitial(initial, afterJane, afterPos);
        for (int i = 0; i < m; ++i) addGift(gifts, afterJane, afterPos, rnd.next(0, 30));
    } else if (mode == 1) {
        int n = rnd.next(1, 8);
        int m = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) addInitial(initial, beforeJane, beforePos);
        for (int i = 0; i < m; ++i) addGift(gifts, beforeJane, beforePos, rnd.next(0, 200));
    } else if (mode == 2) {
        int n = rnd.next(1, 6);
        int m = rnd.next(1, 8);
        int time = 0;
        for (int i = 0; i < n; ++i) {
            addMixedInitial(initial, beforeJane, afterJane, beforePos, afterPos);
        }
        for (int i = 0; i < m; ++i) {
            time += rnd.next(0, 40);
            addMixedGift(gifts, beforeJane, afterJane, beforePos, afterPos, time);
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 8);
        int m = rnd.next(2, 8);
        vector<int> finishTimes;
        int elapsed = 0;
        for (int i = 0; i < n; ++i) {
            Book book{titleFrom(beforeJane, beforePos++), rnd.next(1, 25)};
            elapsed += book.pages;
            finishTimes.push_back(elapsed);
            initial.push_back(book);
        }
        for (int i = 0; i < m; ++i) {
            int time = rnd.any(finishTimes);
            addGift(gifts, i % 2 == 0 ? beforeJane : afterJane,
                    i % 2 == 0 ? beforePos : afterPos, time);
        }
    } else if (mode == 4) {
        int n = rnd.next(1, 7);
        int m = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            addInitial(initial, i % 2 == 0 ? earlyDigits : beforeJane,
                       i % 2 == 0 ? digitPos : beforePos);
        }
        for (int i = 0; i < m; ++i) {
            addGift(gifts, i % 2 == 0 ? earlyDigits : afterJane,
                    i % 2 == 0 ? digitPos : afterPos, rnd.next(0, 1000));
        }
    } else {
        int n = rnd.next(8, 18);
        int m = rnd.next(8, 18);
        for (int i = 0; i < n; ++i) {
            addMixedInitial(initial, beforeJane, afterJane, beforePos, afterPos);
        }
        for (int i = 0; i < m; ++i) {
            int time = rnd.next(0, i % 3 == 0 ? 0 : 1000000000);
            addMixedGift(gifts, beforeJane, afterJane, beforePos, afterPos, time);
        }
    }

    shuffle(initial.begin(), initial.end());
    shuffle(gifts.begin(), gifts.end());

    println((int)initial.size(), (int)gifts.size(), janePages);
    for (const Book& book : initial) {
        println(quoted(book.title), book.pages);
    }
    for (const Gift& gift : gifts) {
        println(gift.time, quoted(gift.title), gift.pages);
    }

    return 0;
}
