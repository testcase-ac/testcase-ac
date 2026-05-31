# Generator Guide

Use this reference when designing and implementing testcase.ac `generator_*.cpp` files.

## Generator Boundary

A generator emits one valid input file for the problem. Its job is to produce inputs that can expose wrong solutions while remaining compact enough for humans to inspect.

Concretely, the goals of the generators include:
- **Validity**: satisfy every constraint from the statement.
- **Compactness**: keep overall input sizes small / simple to allow manual verification.
- **Variablity**: create diverse test cases with multiple hyper-parameters.

While validity is the absolute requirement, you should try to balance compactness and variability so that testcases are both readable and diverse.

## Generator vs Fixed Testcase Boundary

Do not use a generator to emit a small hardcoded list of exact testcases. Exact hand-picked inputs belong in fixed testcase files, especially when they are statement samples, regression cases, or one-off edge cases.

A generator should choose at least one meaningful part of the input randomly from the seed. It may include deterministic branches or small mode tables, but each mode should still randomize values, sizes, ordering, labels, or structure inside the valid input space.

## Source of Truth

The provided problem statement should be primary source of truth when deciding on what input to generate. 

When `validator.cpp` exists, treat it as the executable mirror of the statement and in-house local-policy judgments made by skill `$create-validator`, including practical bounds or choices for ambiguous and self-conflicting statements.

Correct solutions, fixed testcases, and existing generators can reveal useful conflicts, but they do not override the statement or validator.

## Compactness

The overall input size should be small enough to manually read and verify. Sometimes generate medium-size testcases that are not very small but still compact enough to inspect by hand.

- In graph problems, the maximum number of nodes should preferably be less than `15`.
- In string problems, the maximum string length should preferably be less than `30`.
- Avoid generating testcases over about `500` characters unless the problem requires a larger case.
- Choose testcase size randomly so seeds vary across small and medium cases.

## Hyperparameters

Create multiple diverse hyperparameters so generated cases are more likely to catch wrong solutions that fail only on specific input patterns. Hyperparameters should be chosen strategically for the problem while balancing diversity with hand-checkable size.

Examples:

- For a graph problem, sample density from `0` to `1`, then randomly add edges with probability equal to the density.
- For an alphabetical string, sample maximum character `x` from `[a-z]`, then generate a string using characters from `[a-x]`.
- When labels do not affect the algorithm, prefer succinct labels like `A`, `B`, `C` with high probability instead of fully random strings.
- For an array of size `n`, sample lower and upper bounds for the elements first, then choose `n` elements from that range.


## testlib.h Guide

- The first executable statement in `main` must be `registerGen(argc, argv, 1);`.
- Use `println(...)` for automatic spaces and newlines where practical.
- Use `println(v)` to print a vector with elements separated by spaces.
- Use `printf` for output formats that do not fit `println`.
- Use `shuffle(v.begin(), v.end())` from `testlib.h` instead of `std::random_shuffle`.

## Randomness

| Goal | Call | Notes |
| --- | --- | --- |
| Inclusive integer range | `rnd.next(lo, hi)` | Uniform integer in `[lo, hi]`. `lo > hi` is not allowed. |
| Zero-based integer range | `rnd.next(hi)` | Uniform integer in `[0, hi - 1]`. |
| Real probability | `rnd.next()` | Double in `[0, 1)`. |
| Weighted integer | `rnd.wnext(hi, t)` | If `t > 0`, equivalent to the maximum of `t + 1` samples from `rnd.next(hi)`. If `t < 0`, equivalent to the minimum of `-t + 1` samples. |
| Random element | `rnd.any(container)` | Random element from a vector or string. |
| Shuffle | `shuffle(v.begin(), v.end())` | Uses testlib's `rnd`-backed stable shuffle; prefer it over `std::random_shuffle`. |

## Template

Avoid `#include <bits/stdc++.h>` and keep the header includes minimal to reduce compilation time.

```cpp
#include "testlib.h"
#include <vector>
#include <utility>
// Include any additional headers you need
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes
    int N = rnd.next(2, 10);
    int M = rnd.next(0, N * (N - 1) / 2);

    // Build candidate set clearly
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; ++i)
        for (int j = i + 1; j <= N; ++j)
            edges.emplace_back(i, j);

    // Hyper-parameter example for diversity
    double swapProb = rnd.next(0.0, 1.0);
    shuffle(edges.begin(), edges.end());
    for (auto &e : edges)
        if (rnd.next() < swapProb) swap(e.first, e.second);

    edges.resize(M);

    // Output input
    println(N, M);
    for (auto &e : edges) println(e.first, e.second);

    return 0;
}
```


