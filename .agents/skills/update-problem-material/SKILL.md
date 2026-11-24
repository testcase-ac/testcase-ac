---
name: update-problem-material
description: Reproduce testcase.ac verdicts for supplied submissions and repair problem material that misses bugs or flags correct solutions.
---

# Update Problem Material

Start with the repo problem path and one or more target submissions. Use the submission language when it is known.

1. Run each submission against the current material with the problem's configured limits and the original selections when known. Record the verdict and check whether it is fair against the problem statement. Look for a valid failing input when a faulty submission gets through. When an intended correct submission is flagged, check the input and expected output independently. If the evidence is inconclusive, say so.
2. If the material can explain an unfair verdict, make the smallest useful repair. Follow the [testcase selection guidance](../create-generator/references/generator-guide.md#choosing-testcases) when adding coverage.
   - Add or update a `generator_*` for a family of small failing inputs that benefits from random variation. Preserve variety across the rest of the generator's cases.
   - Add a fixed text testcase for a small, specific edge case. Give rare cases guaranteed coverage without spending many random iterations on them.
   - Add a `singlegen_*` for a large failing input that should run once.
   - Patch `validator.cpp` or a `correct_*` solution when the statement or an independently checked case shows a defect.
3. Replay the target submissions and run `./tests/verify/run_problems.sh <problem path>` to check the updated material. Report the verdict before and after for each submission. Keep private submission source out of the repo.
