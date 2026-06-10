#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Book {
    int price;
    int genre;
};

int randomPrice(int mode, int index) {
    if (mode == 0) return rnd.next(1, 30);
    if (mode == 1) return rnd.next(99950, 100000);
    if (mode == 2) return rnd.next(1, 100000);
    if (mode == 3) return 10 + index % 7;
    return rnd.next(100, 300);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 20);
    } else {
        n = rnd.next(21, 60);
    }

    int k;
    int kMode = rnd.next(0, 3);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = n - 1;
    } else {
        k = rnd.next(1, n - 1);
    }

    vector<Book> books;
    books.reserve(n);
    int priceMode = rnd.next(0, 4);

    for (int i = 0; i < n; ++i) {
        int genre;
        if (mode == 0) {
            genre = 1;
        } else if (mode == 1) {
            genre = (i % 10) + 1;
        } else if (mode == 2) {
            genre = rnd.next(1, 10);
        } else if (mode == 3) {
            genre = rnd.next(1, 3);
        } else {
            genre = rnd.next(8, 10);
        }

        books.push_back({randomPrice(priceMode, i), genre});
    }

    shuffle(books.begin(), books.end());

    println(n, k);
    for (const Book& book : books) {
        println(book.price, book.genre);
    }

    return 0;
}
