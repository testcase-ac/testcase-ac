---
name: create-checker
description: "Create or update a testcase.ac C++ testlib output checker for an explicit problem description and problem path. Use for non-exact judging: multiple accepted outputs, certificates, optimization, floating tolerance, or YES/NO plus witness."
---

# Create Checker

Use this skill to create or update a testcase.ac `checker.cpp` when a problem has multiple accepted outputs, certificate-style answers, optimization answers, floating tolerance, or another non-exact output rule.

## Expected Input

Required:

- `problem path=`: repo problem directory such as `testcase/boj/2618`. If the user gives `testcase/.../metadata.yaml`, use its parent directory.
- `problem description file path=` or `problem description=`: a local Markdown/text/PDF path, a remote URL including PDF URLs, or inline statement text already present in the prompt.

Default behavior is to ignore any existing `checker.cpp` and write a fresh checker. If the user explicitly asks to repair or preserve the existing checker, read it as a starting point and preserve correct checks that match the statement and local policy.

If the problem path is missing, ask before editing.

## References

- Read `references/checker-guide.md` before deciding the output contract, implementing `checker.cpp`, or writing targeted cases.
- If `validator.cpp` exists, read it only as evidence for the input contract and local policy choices.
- When exact `testlib.h` behavior matters, inspect the vendored header at `third_party/testlib/testlib.h`.

## Workflow

1. Read the problem description and problem directory.
   - For local or remote PDFs, extract text and render pages when output-format layout is ambiguous.
   - Do not copy problem descriptions into the repo.
2. Decide whether a checker is needed.
   - If exact output comparison is enough, report that `checker.cpp` is unnecessary unless the user explicitly asked for one anyway.
3. Extract the output contract using `references/checker-guide.md`. Separate:
   - jury baseline and any jury-output validity checks;
   - participant output format;
   - semantic validity checks;
   - comparison rule against jury output;
   - cases where invalid jury output or a better participant answer should be checker failure.
4. Write `checker.cpp` using `testlib.h` and the jury-baseline, shared-parser, or tolerance pattern from `references/checker-guide.md`.
5. Set `isSpecialJudge: true` in `metadata.yaml` when the checker is required for judging accepted output. Do not change unrelated metadata.
6. Exercise targeted checker cases using scratch input/output files, then remove the scratch files unless the user asks to preserve evidence.
   - Include at least one accepted case.
   - Include at least one rejected participant-output case.
   - Include an accepted case whose participant output differs from jury output when the statement permits multiple valid outputs, tolerance, or flexible coordinates.
   - Include one fail case when the checker validates a jury certificate, feasibility decision, or optimization value.
7. Run the narrow checker gate for every targeted case. It compiles `checker.cpp` in the Docker runtime and runs one explicit `(input, participant output, jury output, expected verdict)` case:

   ```bash
   .agents/skills/create-checker/scripts/check-checker-case.sh testcase/<type>/<id> <expected> <input-file> <participant-file> <jury-file>
   ```

8. If the narrow gate fails, classify ownership:
   - checker compile/runtime failure: fix `checker.cpp`;
   - accepted case rejected: fix the checker or scratch case according to the output contract;
   - rejected case accepted: strengthen the checker;
   - fail case not failed: validate jury-answer handling and optimum comparison.
9. Iterate until every checker-owned targeted case passes.
10. In the final report, mention the checker file, the output contract, the targeted cases run, and any assumptions or conflicts.

Full repository verification with `./tests/verify/run_problems.sh testcase/<type>/<id>` is an optional integration follow-up, not this skill's completion criterion.
