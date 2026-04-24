#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

using pii = pair<int,int>;

// Generate a valid simple rectilinear polygon point set
vector<pii> genValid() {
    // Choose one of several template shapes
    int shapeId = rnd.next(0,3);
    vector<pii> pts;
    if (shapeId == 0) {
        // Rectangle
        int w = rnd.next(1,5), h = rnd.next(1,5);
        pts = {{0,0},{w,0},{w,h},{0,h}};
    } else if (shapeId == 1) {
        // L-shape
        int w = rnd.next(2,5), h = rnd.next(2,5);
        pts = {{0,0},{w,0},{w,1},{1,1},{1,h},{0,h}};
    } else if (shapeId == 2) {
        // U-shape
        int w = rnd.next(3,6), h = rnd.next(3,6);
        pts = {{0,0},{w,0},{w,1},{1,1},{1,h-1},{w,h-1},{w,h},{0,h}};
    } else {
        // Zigzag shape
        pts = {{0,0},{1,0},{1,1},{2,1},{2,2},{3,2},{3,3},{0,3}};
    }
    // Rotate by k * 90 degrees
    int k = rnd.next(0,3);
    for (auto &p : pts) {
        int x = p.first, y = p.second;
        for (int t = 0; t < k; t++) {
            int nx = -y, ny = x;
            x = nx; y = ny;
        }
        p.first = x; p.second = y;
    }
    // Translate to random position within bounds
    int shift = 1000000 - 10;
    int dx = rnd.next(-shift, shift);
    int dy = rnd.next(-shift, shift);
    for (auto &p : pts) {
        p.first += dx;
        p.second += dy;
    }
    // Shuffle point order
    shuffle(pts.begin(), pts.end());
    return pts;
}

// Generate an invalid case (odd number of points)
vector<pii> genInvalid() {
    int n = rnd.next(5,9);
    if (n % 2 == 0) n++;
    set<pii> st;
    while ((int)st.size() < n) {
        int x = rnd.next(-20,20);
        int y = rnd.next(-20,20);
        st.insert({x,y});
    }
    vector<pii> pts(st.begin(), st.end());
    shuffle(pts.begin(), pts.end());
    return pts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(2,5);
    // Ensure at least one valid and one invalid
    int cntValid = rnd.next(1, T-1);
    int cntInvalid = T - cntValid;
    vector<vector<pii>> cases;
    for (int i = 0; i < cntValid; i++) cases.push_back(genValid());
    for (int i = 0; i < cntInvalid; i++) cases.push_back(genInvalid());
    shuffle(cases.begin(), cases.end());
    // Output
    println(T);
    for (auto &pts : cases) {
        println((int)pts.size());
        for (auto &p : pts) {
            println(p.first, p.second);
        }
    }
    return 0;
}
