#include "testlib.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> lexicographicPair(int index) {
    for (int first = 0; first < 11; ++first) {
        for (int second = first + 1; second < 11; ++second) {
            if (index == 0) {
                return {first, second};
            }
            --index;
        }
    }
    return {0, 1};
}

long long productOf(const array<int, 11>& dims) {
    return accumulate(dims.begin(), dims.end(), 1LL, multiplies<long long>());
}

array<int, 11> makeDimensions() {
    array<int, 11> dims{};
    dims.fill(1);

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        for (int i = 0; i < 11; ++i) {
            dims[i] = rnd.next(1, 2);
        }
    } else if (mode == 1) {
        vector<int> positions(11);
        iota(positions.begin(), positions.end(), 0);
        shuffle(positions.begin(), positions.end());
        dims[positions[0]] = rnd.next(3, 6);
        dims[positions[1]] = rnd.next(2, 5);
        dims[positions[2]] = rnd.next(2, 4);
    } else if (mode == 2) {
        int remaining = rnd.next(24, 96);
        for (int i = 0; i < 11 && remaining > 1; ++i) {
            int factor = rnd.next(1, min(4, remaining));
            while (factor > 1 && remaining % factor != 0) {
                --factor;
            }
            dims[i] = factor;
            remaining /= factor;
        }
    } else {
        int wide = rnd.next(0, 10);
        dims[wide] = rnd.next(8, 18);
        dims[(wide + rnd.next(1, 10)) % 11] = rnd.next(2, 3);
    }

    while (productOf(dims) > 180) {
        int idx = rnd.next(0, 10);
        if (dims[idx] > 1) {
            --dims[idx];
        }
    }
    return dims;
}

vector<int> candidateRotationPairs(const array<int, 11>& dims) {
    vector<int> pairs;
    for (int index = 0; index < 55; ++index) {
        auto [first, second] = lexicographicPair(index);
        if (dims[first] >= 2 && dims[second] >= 2) {
            pairs.push_back(index);
        }
    }
    return pairs;
}

void printArrayValues(const array<int, 11>& dims) {
    long long rows = productOf(dims) / dims[10];
    long long valueBase = rnd.next(1, 1000);
    for (long long row = 0; row < rows; ++row) {
        vector<long long> line;
        for (int w = 0; w < dims[10]; ++w) {
            long long value = valueBase + row * dims[10] + w;
            if (rnd.next(0, 4) == 0) {
                value = rnd.next(1LL, 11111111111LL);
            }
            line.push_back(value);
        }
        println(line);
    }
}

void printBoundedOperation(int op, const array<int, 11>& dims) {
    array<int, 11> lo;
    array<int, 11> hi;
    for (int i = 0; i < 11; ++i) {
        lo[i] = rnd.next(1, dims[i]);
        hi[i] = rnd.next(lo[i], dims[i]);
    }

    if (op >= 12) {
        auto [first, second] = lexicographicPair(op - 12);
        lo[first] = rnd.next(1, dims[first] - 1);
        hi[first] = lo[first] + 1;
        lo[second] = rnd.next(1, dims[second] - 1);
        hi[second] = lo[second] + 1;
    }

    vector<int> output;
    output.push_back(op);
    output.insert(output.end(), lo.begin(), lo.end());
    output.insert(output.end(), hi.begin(), hi.end());
    println(output);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    array<int, 11> dims = makeDimensions();
    println(vector<int>(dims.begin(), dims.end()));
    printArrayValues(dims);

    int rho = rnd.next(8, 45);
    println(rho);

    for (int step = 0; step < rho; ++step) {
        vector<int> rotationPairs = candidateRotationPairs(dims);
        int choice = rnd.next(0, rotationPairs.empty() ? 1 : 2);

        if (choice == 0) {
            int op = rnd.next(1, 11);
            printBoundedOperation(op, dims);
        } else if (choice == 1 && !rotationPairs.empty()) {
            int op = 12 + rnd.any(rotationPairs);
            printBoundedOperation(op, dims);
        } else {
            int pairIndex = rnd.next(0, 54);
            auto [first, second] = lexicographicPair(pairIndex);
            println(67 + pairIndex);
            swap(dims[first], dims[second]);
        }
    }

    return 0;
}
