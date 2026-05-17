---
name: create-validator
description: Create or repair a testcase.ac input validator for an explicit problem description and problem path, extracting statement samples, adding coverage-driven fixed testcases when useful, and verifying with repo input validation.
metadata:
  short-description: Write and verify testlib validators
---

# Create Validator

Use this skill when the user asks for `$create-validator` or wants `validator.cpp` for a testcase.ac problem.

## Expected Input

Required:

- `problem path=`: repo problem directory such as `testcase/boj/1000`. If the user gives `testcase/.../metadata.yaml`, use its parent directory.
- `problem description file path=` or `problem description=`: a local Markdown/text/PDF path, a remote URL including PDF URLs, or inline statement text already present in the prompt.

Default behavior is to ignore any existing `validator.cpp` and write a fresh validator. If the user explicitly says to use the existing validator, read it as a starting point and preserve correct checks where they match the statement.

If the problem path is missing, ask before editing.

## Workflow

1. Read the problem description and problem directory.
   - For local or remote PDFs, extract text and render pages when layout is ambiguous.
   - Do not copy problem descriptions into the repo.
2. Extract the input contract:
   - input format, bounds, and multiple-testcase structure;
   - explicit guarantees and holistic properties;
   - statement samples, if present.
3. Classify statement samples before saving them.
   - If the statement explicitly says examples are excluded from judging, illustrative only, or otherwise not subject to the normal input rules, do not save them as fixed testcases.
   - If the sample is clearly invalid under the extracted input contract, do not save it as a fixed testcase. Record the reason in the final report.
   - If an already-saved canonical sample matches an explicitly non-graded or proven-invalid statement sample, remove that sample input and its paired output.
4. Save missing valid statement samples as canonical fixed testcases:
   - `sample_{i}.in`
   - `sample_{i}.out` when official output is present
   Preserve exact sample formatting with a final newline.
5. Normalize exact duplicate legacy fixed testcases.
   - Run `.agents/skills/create-validator/scripts/normalize-statement-samples.py <problem path>` first as a dry run.
   - If it reports only exact normalized duplicates, rerun with `--apply`.
6. Add `additional_{i}.in` only when existing fixed testcases do not cover enough distinct input shapes for validator work.
   - These are input-only.
   - Add up to three total fixed testcases when extra coverage is useful.
   - Prefer shapes that exercise different constraints: minimum bounds, special structures, multi-case input, edge graph/property cases, and representative larger-but-small cases.
7. Write `validator.cpp` using `testlib.h` and the rules in `validator-authoring.md`.
8. Run input validation:

   ```bash
   ./tests/verify/run_problems.sh --validate-inputs testcase/<type>/<id>
   ```

9. If input validation fails, classify ownership:
   - `validator.cpp` compile failure: fix validator.
   - Fixed testcase rejected: compare against the statement. If valid, fix validator. If invalid and created by this skill, fix/remove that testcase. If invalid and pre-existing, report it.
   - Generator or singlegen compile/runtime failure: report it; do not fix it.
   - Generator or singlegen output rejected: compare output against the statement. If valid, fix validator. If invalid, report the provider as likely wrong; do not fix it.
   - Unknown file, no case provider, or oversized fixed testcase: report unless caused by files created by this skill.
10. Iterate until there are no validator-owned input-validation failures.
11. Run the full verifier as the final integration gate:

   ```bash
   ./tests/verify/run_problems.sh testcase/<type>/<id>
   ```

   If the remaining failure is not validator-owned, stop and report the root cause.

## Notes

- Statement samples are official examples from the problem statement.
- Additional fixed testcases are valid input-only cases written from the statement when existing fixed testcases do not cover enough distinct input shapes.
- Input validation runs all case providers through `validator.cpp` and skips output judging.
