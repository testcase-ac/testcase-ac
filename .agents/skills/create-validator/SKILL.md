---
name: create-validator
description: Create or update a testcase.ac input validator for an explicit problem description and problem path, extracting statement samples, adding coverage-driven fixed testcases when useful, and verifying with repo input validation.
metadata:
  short-description: Write and verify testlib validators
---

# Create Validator

Use this skill to create or update a testcase.ac `validator.cpp`, save valid statement samples as fixed testcases, and verify the problem's case providers against the validator.

## Expected Input

Required:

- `problem path=`: repo problem directory such as `testcase/boj/1000`. If the user gives `testcase/.../metadata.yaml`, use its parent directory.
- `problem description file path=` or `problem description=`: a local Markdown/text/PDF path, a remote URL including PDF URLs, or inline statement text already present in the prompt.

Default behavior is to ignore any existing `validator.cpp` and write a fresh validator. If the user explicitly says to use the existing validator, read it as a starting point and preserve correct checks that match the statement and local policy.

If the problem path is missing, ask before editing.

## References

- Read `references/input-contract-guide.md` before deciding what the validator must accept or reject.
- Read `references/testlib-guide.md` before implementing or repairing `testlib.h` code.
- When exact `testlib.h` behavior matters, inspect the vendored header at `third_party/testlib/testlib.h`.

## Workflow

1. Read the problem description and problem directory.
   - For local or remote PDFs, extract text and render pages when layout is ambiguous.
   - Do not copy problem descriptions into the repo.
2. Extract the input contract using `references/input-contract-guide.md`. Separate:
   - statement requirements;
   - local defaults that apply because the statement is silent;
   - ambiguous or policy-chosen rules that need `// CHECK`.
3. Classify statement samples before saving them.
   - If the statement explicitly says examples are excluded from judging, illustrative only, or otherwise not subject to the normal input rules, do not save them as fixed testcases.
   - If the sample is clearly invalid under the extracted input contract, do not save it as a fixed testcase. Record the reason in the final report.
   - If an already-saved canonical sample matches an explicitly non-graded or proven-invalid statement sample, remove that sample input and its paired output.
4. Save missing valid statement samples as canonical fixed testcases:
   - `sample_{i}.in`
   - `sample_{i}.out` when official output is present

   Preserve semantically meaningful sample formatting, normalize accidental whitespace according to `input-contract-guide.md`, and ensure a final newline.

5. Normalize exact duplicate legacy fixed testcases.
   - Run `.agents/skills/create-validator/scripts/normalize-statement-samples.py <problem path>` first as a dry run.
   - If it reports only exact normalized duplicates, rerun with `--apply`.
6. Add `additional_{i}.in` only when existing fixed testcases do not cover enough distinct input shapes for validator work.
   - These are input-only.
   - Add up to three total fixed testcases when extra coverage is useful.
   - Prefer shapes that exercise different constraints: minimum bounds, special structures, multi-case input, edge graph/property cases, and representative larger-but-small cases.
7. Write `validator.cpp` using `testlib.h`, the extracted input contract, and `references/testlib-guide.md`.
8. Run input validation:

   ```bash
   ./tests/verify/run_problems.sh --validate-inputs testcase/<type>/<id>
   ```

   This command runs all case providers (fixed testcases, generators, and singlegens) through `validator.cpp` and checks whether they pass the new validator.

9. If input validation fails, classify ownership:
   - `validator.cpp` compile failure: fix validator.
   - Fixed testcase created by this skill rejected: fix either validator or testcase as needed to resolve the conflict.
   - Existing case provider (fixed testcase, generator, or singlegen) rejected: if the rejection is because of an error in `validator.cpp`, fix the validator. If the provider violates the statement contract or local defaults, report it as an input-provider conflict. Do not weaken a statement-correct validator only to make existing providers pass.
   - Existing generator or singlegen compile/runtime failure: report it unless caused by this skill.
   - Unknown file, no case provider, or oversized fixed testcase: report it unless caused by this skill.
10. Iterate until there are no validator-owned input-validation failures.
11. In the final report, mention any provider conflicts, rejected statement samples, skipped samples, practical caps, or `// CHECK` interpretations.
