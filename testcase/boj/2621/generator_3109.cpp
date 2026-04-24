#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool is_consecutive_nums(vector<int> v) {
    sort(v.begin(), v.end());
    for (int i = 1; i < (int)v.size(); i++)
        if (v[i] != v[0] + i) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<char> colors = {'R','B','Y','G'};
    int pattern = rnd.next(1, 9);
    vector<pair<char,int>> cards;

    auto pick_colors = [&](int k) {
        vector<char> c = colors;
        shuffle(c.begin(), c.end());
        c.resize(k);
        return c;
    };

    auto pick_numbers = [&](int k) {
        vector<int> nums(9);
        iota(nums.begin(), nums.end(), 1);
        shuffle(nums.begin(), nums.end());
        nums.resize(k);
        return nums;
    };

    if (pattern == 1) {
        // Straight flush
        int h = rnd.next(5, 9);
        char c = rnd.any(colors);
        for (int x = h-4; x <= h; x++)
            cards.emplace_back(c, x);
    }
    else if (pattern == 2) {
        // Four of a kind
        int x = rnd.next(1, 9);
        for (char c : colors)
            cards.emplace_back(c, x);
        int y;
        do { y = rnd.next(1, 9); } while (y == x);
        cards.emplace_back(rnd.any(colors), y);
    }
    else if (pattern == 3) {
        // Full house
        vector<int> ab = pick_numbers(2);
        int three = ab[0], two = ab[1];
        auto c3 = pick_colors(3);
        for (char c : c3) cards.emplace_back(c, three);
        auto c2 = pick_colors(2);
        for (char c : c2) cards.emplace_back(c, two);
    }
    else if (pattern == 4) {
        // Flush (not straight)
        char cf = rnd.any(colors);
        vector<int> nums;
        do {
            nums = pick_numbers(5);
        } while (is_consecutive_nums(nums));
        for (int x : nums)
            cards.emplace_back(cf, x);
    }
    else if (pattern == 5) {
        // Straight (not flush)
        int h = rnd.next(5, 9);
        vector<int> nums;
        for (int x = h-4; x <= h; x++)
            nums.push_back(x);
        vector<char> cs;
        do {
            cs.clear();
            for (int i = 0; i < 5; i++)
                cs.push_back(rnd.any(colors));
        } while (count_if(cs.begin(), cs.end(), [&](char c){ return c==cs[0]; }) == 5);
        for (int i = 0; i < 5; i++)
            cards.emplace_back(cs[i], nums[i]);
    }
    else if (pattern == 6) {
        // Three of a kind
        vector<int> abc = pick_numbers(3);
        int three = abc[0], y = abc[1], z = abc[2];
        auto c3 = pick_colors(3);
        for (char c : c3) cards.emplace_back(c, three);
        cards.emplace_back(rnd.any(colors), y);
        cards.emplace_back(rnd.any(colors), z);
    }
    else if (pattern == 7) {
        // Two pair
        vector<int> abc = pick_numbers(3);
        int x = abc[0], y = abc[1], z = abc[2];
        auto c2x = pick_colors(2);
        for (char c : c2x) cards.emplace_back(c, x);
        auto c2y = pick_colors(2);
        for (char c : c2y) cards.emplace_back(c, y);
        cards.emplace_back(rnd.any(colors), z);
    }
    else if (pattern == 8) {
        // One pair
        int x = rnd.next(1, 9);
        vector<char> c2 = pick_colors(2);
        for (char c : c2) cards.emplace_back(c, x);
        vector<int> rest;
        for (int i = 1; i <= 9; i++)
            if (i != x) rest.push_back(i);
        shuffle(rest.begin(), rest.end());
        for (int i = 0; i < 3; i++)
            cards.emplace_back(rnd.any(colors), rest[i]);
    }
    else {
        // High card: no pairs, not straight, not flush
        vector<int> nums;
        vector<char> cs;
        do {
            nums = pick_numbers(5);
        } while (is_consecutive_nums(nums));
        do {
            cs.clear();
            for (int i = 0; i < 5; i++)
                cs.push_back(rnd.any(colors));
        } while (count_if(cs.begin(), cs.end(), [&](char c){ return c==cs[0]; }) == 5);
        for (int i = 0; i < 5; i++)
            cards.emplace_back(cs[i], nums[i]);
    }

    // random order
    shuffle(cards.begin(), cards.end());
    for (auto &p : cards)
        println(p.first, p.second);

    return 0;
}
