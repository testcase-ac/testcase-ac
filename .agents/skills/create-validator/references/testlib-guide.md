# Testlib Guide

Use this reference for `testlib.h` APIs and C++ patterns used in testcase.ac validators.

When exact behavior matters, inspect the vendored implementation at `third_party/testlib/testlib.h` instead of guessing from memory.

## Common APIs

| Goal | Call | Notes |
| --- | --- | --- |
| Register validator | `registerValidation(argc, argv)` | Call once at the start of `main`. |
| Read integer | `inf.readInt(L, R, "name")` | Reads a canonical decimal `int` and checks inclusive range `[L, R]`. |
| Read long long | `inf.readLong(L, R, "name")` | Bounds should be `long long` literals such as `1LL`. |
| Read real | `inf.readDouble(L, R, "name")` | Checks inclusive range. Use only when real input is specified. |
| Read integer array | `inf.readInts(n, L, R, "name")` | Reads exactly `n` space-separated values. Does not consume end-of-line. |
| Read long long array | `inf.readLongs(n, L, R, "name")` | Reads exactly `n` space-separated values. Does not consume end-of-line. |
| Read token | `inf.readToken(regex, "name")` | Reads one whitespace-free token and validates the whole token against `regex`. |
| Read line | `inf.readLine(regex, "name")` | Reads through EOLN. The returned string does not include EOLN. |
| Read spacing | `inf.readSpace()`, `inf.readEoln()`, `inf.readEof()` | Use these to enforce exact formatting. |
| Extra check | `ensuref(cond, "message", ...)` | Rejects input with a custom message. Include failing indices and values. |
| Multi-case labels | `setTestCase(t)` | Call after reading the case index to improve diagnostics. |

Prefer descriptive names for every read where testlib supports them.

## Reading Patterns

### Decimal Numbers

Use numeric readers whenever a decimal number fits the target type:

```cpp
int n = inf.readInt(1, 100000, "n");
inf.readEoln();
```

`readInt`, `readLong`, `readInts`, and `readLongs` already check decimal canonical form, signs, and ranges.

### Huge Or Base-B Numbers

If a number exceeds `long long`, or uses a non-decimal base or special format, read it as a token or line, then enforce numeric policy manually.

```cpp
string x = inf.readToken("[0-9A-F]{1,6}", "x");
ensuref(x == "0" || x[0] != '0', "x has leading zero: %s", x.c_str());
```

### Strings

For simple string formats, use a small regex:

```cpp
string s = inf.readToken("[a-z]{1,100}", "s");
```

For complex strings, read broadly and check with code:

```cpp
string line = inf.readLine("[^]+", "line");
ensuref(!line.empty(), "line must not be empty");
```

### Arrays

Prefer whole-line array readers when all elements share bounds:

```cpp
vector<int> a = inf.readInts(n, 1, 1000, "a_i");
inf.readEoln();
```

## Regex Notes

testlib regex is a limited mini-regex. Use it for simple lexical checks, not for complex semantic validation.

Supported syntax includes:

- Character classes such as `[a-z]` and negated classes such as `[^a-z]`.
- Repetition: `{L,R}`, `*`, `+`, and `?`.
- Alternation with `foo|bar`.
- Optional signs and simple ranges such as `-?[1-9][0-9]{0,3}`.

Important limitations:

- Regex is greedy by design. Pattern `[0-9]?1` fails on input `1` because `[0-9]?` consumes the `1`.
- There is no match-all `.`. Use `[^]` to match any character.
- There is no `\d`, `\r`, or `\n` shorthand.
- Escaped shorthand such as `\d` may be parsed as a slash or `d`, not as a digit.
- Escape spaces in line regexes, for example `inf.readLine("[A-Z\\ ]{1,100}", "line")`.
- There is no lookahead or lookbehind.
- Do not use `^` or `$`. `readToken` and `readLine` already validate the entire token or line.
- Do not encode complex semantic constraints only in regex when an explicit computation with `ensuref` is clearer.

## Common Pitfalls

- Passing one argument to `readToken` or `readLine` treats it as a regex, not as a field name.
  - Bad: `inf.readToken("token");`
  - Good: `inf.readToken("[^]+", "token");`
- `readLine()` consumes EOLN but does not include it in the returned string. Do not call `inf.readEoln()` immediately after `readLine()`.
- `readInts()` and `readLongs()` do not consume EOLN. Call `inf.readEoln()` after them when the line should end.
- `readLong` and `readLongs` bounds should use `long long` literals.
  - Bad: `long long x = inf.readLong(1, 1000, "x");`
  - Good: `long long x = inf.readLong(1LL, 1000LL, "x");`
- Use `long long` when computing sums of `int`, and `__int128_t` when computing sums or products of `long long`.
- For undirected duplicate-edge checks, normalize the edge or store both directions consistently.

## Template

```cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate input here.

    inf.readEof();
}
```

## Example

Undirected graph without loops or multiple edges:

```cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge index %d: (%d, %d)", i + 1, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i + 1, a, b);
    }

    inf.readEof();
}
```
