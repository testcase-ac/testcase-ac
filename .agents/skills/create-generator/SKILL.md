---
name: create-generator
description: Create or update a testcase.ac C++ testlib generator for an explicit problem description and problem path, verifying generated inputs through validator.cpp and repo verification.
metadata:
  short-description: Write and test testcase generators
---

# Create Generator

Use this skill to create or update a testcase.ac `generator_*.cpp`, keep generated inputs statement-valid and hand-checkable, and verify the generator against the problem's validator and repository verifier.

## Expected Input

Required:

- `problem path=`: repo problem directory such as `testcase/boj/1000`. If the user gives `testcase/.../metadata.yaml`, use its parent directory.
- `problem description file path=` or `problem description=`: a local Markdown/text/PDF path, a remote URL including PDF URLs, or inline statement text already present in the prompt.

Optional:

- generator filename: default to `generator_sample.cpp` when omitted. If the user explicitly names an existing generator, update that file.

Default behavior is to write one generator focused on compact, varied, valid inputs. If `generator_sample.cpp` already exists, update it. If other existing generators are present, read them for coverage context but do not mechanically duplicate their modes.

If the problem path is missing, ask before editing.

## References

- Read `references/generator-guide.md` before designing or implementing the generator.
- If `validator.cpp` exists, read it as the executable mirror of the statement and local input-policy choices made by `$create-validator`.
- When exact `testlib.h` generator behavior matters, inspect the vendored header at `third_party/testlib/testlib.h`.

## Workflow

1. Read the problem description and problem directory.
   - For local or remote PDFs, extract text and render pages when layout is ambiguous.
   - Do not copy problem descriptions into the repo.
2. Understand the valid input space from the problem statement and local problem artifacts when available:
   - `validator.cpp`;
   - `correct_*`;
   - existing `generator_*` and `singlegen_*`;
   - fixed testcase inputs and paired answers.
3. Write one C++ generator using `testlib.h` and `references/generator-guide.md`.
4. Run the quick generator check:

   ```bash
   .agents/skills/create-generator/scripts/check-generator.sh testcase/<type>/<id> generator_name.cpp 100
   ```

   The script builds the stresser Docker runtime when needed, compiles the generator inside that runtime, runs it once per seed, and fails if any run emits empty output. If `validator.cpp` exists, it also compiles the validator and validates every generated case. The generator filename may be omitted only when the problem directory has exactly one `generator*.cpp` candidate.

5. If verification fails, classify ownership:
   - Generator compile failure, runtime failure, empty output, or malformed output: fix the generator.
   - Validator rejection: fix the generator by default. Report a validator conflict only when `validator.cpp` clearly disagrees with the statement or local policy.
6. Iterate until there are no generator-owned verification failures.
7. In the final report, mention the generator file, the main coverage modes, verification commands run, and any provider conflicts or statement/validator disagreements.
