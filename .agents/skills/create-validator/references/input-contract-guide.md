# Input Contract Guide

Use this reference to decide what a testcase.ac `validator.cpp` must accept or reject.

## Validator Boundary

An input validator checks whether an input file is a valid instance of the problem. It is not a solver, output checker, generator, or judge for contestant behavior.

A good validator should validate properties that the statement guarantees about the input, and reject invalid, vacuous, undefined, or impractically huge inputs even when the statement forgot a boundary.

## Source of Truth

Build the input contract from these sources, in this order:

1. The provided problem statement, including input format, bounds, guarantees, and official samples or format examples.
2. Local testcase.ac defaults for cases where the statement is silent.
3. A local choice when the statement is ambiguous or contradictory.

Only the provided statement and repo-local policy define validity. Existing solutions, generators, singlegens, fixed testcases, and `--validate-inputs` failures can expose conflicts, but they are not authority over the statement or local defaults.

## 1. Contract From Problem Statement

### Surface Format

- Validate the stated input shape: number of lines, number of test cases, token order, separators, line endings, and EOF.
- Validate value domains: numeric bounds, token alphabets, string lengths, array lengths, matrix dimensions, and per-field domains.
- Treat official samples and explicit format examples as statement evidence. When they demonstrate a broader surface format than local defaults, accept that demonstrated format unless the statement clearly marks it as illustrative or non-graded. For repeated homogeneous input constructs, apply the demonstrated allowance consistently across equivalent parts.

### Structural Consistency

- Validate uniqueness, sortedness, permutations, mappings, and duplicate restrictions when stated or required by the named input object.
- Validate stated relationships across tokens, lines, and test cases; do not stop at lexical format and per-token bounds. Examples:
  - If the input is a connected graph, validate connectivity.
  - If the input is a polygon, validate non-degeneracy unless the statement allows degenerate polygons.
  - If the statement guarantees legal simulation states or transitions, simulate enough to validate those invariants.

### Answer-Related Guarantees

When the statement guarantees or assumes a property of the computed answer for every valid input, treat it as an input constraint; validate it by computing or soundly bounding the derived quantity when practical.

Examples:

- If the statement says an answer always exists, validate existence.
- If the statement says the answer is at most `X`, compute enough to validate that bound.
- If the statement says the answer fits in a fixed numeric type, validate the derived answer range when it is practical to do so exactly or by a sound bound.
- If the statement asks contestants to decide whether an answer exists, accept both existence and non-existence cases that satisfy the rest of the input contract.

### What Validators Must Not Do

- Do not turn the problem's question into an input constraint. Accept any input that satisfies the input contract, regardless of the answer a contestant should produce for it.
- Do not reject an input only because a particular intended solution, reference solution, generator, singlegen, fixed testcase, or `--validate-inputs` run disagrees with it. Use the disagreement to find the conflict, then decide from the source-of-truth order.

## 2. Contract From Local Defaults

Apply the local defaults below only when the statement is silent and official samples or format examples do not clearly imply a broader form.

### Formatting Defaults

- Follow the line breaks shown by the input format, and end the file immediately after the final newline.
- Do not allow trailing spaces before newlines, leading spaces at the start of the line, or repeated separators unless the statement, official samples, or format examples imply that broader format.
- For natural-language string lines made of words, default to ordinary spacing unless the statement or samples imply otherwise: no leading or trailing spaces, no repeated spaces between words, and only ASCII spaces separate words within a line.
- Reject empty or whitespace-only input by default. For ordinary tokens or lines, require at least one non-whitespace character unless the statement explicitly allows an empty string, empty line, or whitespace-only line. A maximum length or allowed space character alone does not make the blank case valid. Allowing leading or trailing whitespace does not explicitly allow whitespace-only input.

### Numeric Defaults

- If the statement says a token is a number, enforce canonical numeric form: no leading zeros, no leading `+` sign, and a single leading `-` sign for negatives.
- The only allowed numeric representation with leading zero is the single token `0`.
- For huge integers, base-B numbers, or special numeric tokens represented as strings in code, manually reject invalid leading zeroes, invalid signs, and out-of-alphabet digits.
- In xor/bitwise contexts, treat integer values as nonnegative unless the statement explicitly allows negatives.
- Make sure to not enforce numeric canonical form for strings of digits or binary strings as well, which are distinct concepts from numbers.

## 3. Choosing Contract For Special Cases

### Fixed-Size Relaxations

- If the statement fixes a large count or length only to set workload scale, the validator may accept smaller representative inputs down to `1` when the smaller size preserves the same input shape and solution logic, so that users can read and inspect the smallest valid testcases manually.
  - Example 1: a multi-case problem fixes `T = 1000`, but each testcase is independent. In this case, allow `T` down to `1`.
  - Example 2: a bitwise-operation problem fixes the binary string length to `100000`, but shorter equal-length bit-vectors preserve the same input shape and solution logic. In this case, allow the length down to `1`.
- Do not use this relaxation generically. Use it only when a high lower bound or exact fixed size, at least `1000`, forces the smallest valid testcase to be so large that it is hard for users to read or inspect manually. If the high lower bound does not create a large testcase byte size, do not apply this relaxation.
- Do not relax a fixed value when changing it would change the problem being validated. Only relax large fixed counts or lengths that are used purely to make the input long.
- Add a nearby `// CHECK` comment for any fixed-size relaxation, mentioning the original fixed size and the reason for allowing smaller inputs.

### Size Defaults

- If an input-size count has no upper bound, add a practical cap from nearby constraints. Example: if `N <= 1000`, cap graph edges at `1000000` because that matches the `N^2` scale.
- For primarily numeric input, reject inputs that force around `5000000` or more scalar tokens, unless the statement explicitly allows a larger input.
- For primarily string input, reject inputs around `10000000` or more characters, unless the statement explicitly allows a larger input.
- If `T` has no explicit upper bound, allow up to `100000` cases, but cap the aggregate workload to one largest testcase unless the statement suggests otherwise. Use the size term that drives complexity: for `N <= 1000000`, cap `sum(N) <= 1000000`; for data plus queries, cap `sum(N + M)` similarly.
- Add a nearby `// CHECK` comment for practical caps that are not written in the statement.

### Ambiguous Input Contracts

When the statement leaves one constraint unspecified, and it cannot be determined from local defaults as well, then the validator must choose between two conflicting rules. In this case, identify the stricter validator rule and the less restrictive rule it would replace. Choose between those two rules by answering these questions in order.

1. Would accepting the broader case make the central problem object absent or contradict how it is defined? If yes, enforce the stricter rule. Example: if `N` is the size of a group, collection, or game instance, and the written bounds only say `N` is an integer below some upper limit, do not allow `N = 0` unless the statement explicitly allows an empty instance.
2. Otherwise, is the stricter rule explicitly stated, needed by a stated input guarantee, or needed to keep the input useful and well-defined? Unless so, use the less restrictive rule. Example: if the input gives positions of `N` marked points on a line but does not say the positions are distinct, accept two points with the same coordinate.

Whenever either choice depends on this ambiguity judgment, add a nearby comment containing `// CHECK`. This includes common structural checks such as distinct values, unique edges, no self-loops, positive weights, connectivity, or feasibility, whether the validator enforces or omits the stricter rule.

Do not add `// CHECK` for rules that are directly stated by the input contract or by the required behavior for a stated command/case.

### Conflicting Input Contracts

When the primary statement, official samples, or language variants conflict, identify the stricter validator rule and the less restrictive rule it would replace, then choose the most reasonable interpretation for the current problem. When choosing the interpretation, consider:

- Some problems mix small/large version constraints. Samples may follow the large version while the statement text describes the small version. In this case follow the statement text, since that is what actually defines this problem.
- Some statements have mistranslated constraints. In those cases, a language variant statement or official sample may contradict the primary statement.

Add a nearby comment containing `// CHECK` for the chosen interpretation, whether the validator enforces the stricter rule or omits it. Mention the conflict in the final response.

Do not add `// CHECK` when there is no actual conflict between the input contracts.
