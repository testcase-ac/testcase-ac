#!/usr/bin/env python3
"""Remove exact duplicate legacy fixed testcases after statement samples are canonicalized."""

from __future__ import annotations

import argparse
from pathlib import Path


def normalized_text(path: Path) -> str:
    text = path.read_text()
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    return text.rstrip("\n") + "\n"


def is_fixed_testcase(path: Path) -> bool:
    name = path.name
    return name.startswith("testcase") or ".in" in name


def answer_paths_for(input_path: Path) -> list[Path]:
    name = input_path.name
    candidates: list[Path] = []
    if ".in" not in name:
        candidates.append(input_path.with_name(f"{input_path.stem}.out{input_path.suffix}"))
        candidates.append(input_path.with_name(name + ".out"))
        return candidates
    candidates.append(input_path.with_name(name.replace(".in", ".out", 1)))
    return candidates


def canonical_samples(problem_path: Path) -> list[Path]:
    return sorted(problem_path.glob("sample_*.in"))


def duplicate_removals(problem_path: Path) -> list[Path]:
    removals: list[Path] = []
    samples = canonical_samples(problem_path)
    sample_inputs = {sample: normalized_text(sample) for sample in samples}
    sample_outputs = {
        sample: normalized_text(sample.with_suffix(".out"))
        for sample in samples
        if sample.with_suffix(".out").exists()
    }

    for candidate in sorted(problem_path.iterdir()):
        if not candidate.is_file() or candidate in sample_inputs:
            continue
        if not is_fixed_testcase(candidate):
            continue

        candidate_text = normalized_text(candidate)
        matched_sample = next(
            (sample for sample, text in sample_inputs.items() if text == candidate_text),
            None,
        )
        if matched_sample is None:
            continue

        old_answer = next((path for path in answer_paths_for(candidate) if path.exists()), None)
        if old_answer is None:
            removals.append(candidate)
            continue

        sample_output = sample_outputs.get(matched_sample)
        if sample_output is None:
            print(
                f"skip {candidate}: duplicate input has answer {old_answer.name}, "
                f"but {matched_sample.with_suffix('.out').name} does not exist"
            )
            continue
        if normalized_text(old_answer) != sample_output:
            print(
                f"skip {candidate}: duplicate input has non-duplicate answer "
                f"{old_answer.name}"
            )
            continue
        removals.extend([candidate, old_answer])

    return removals


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("problem_path", type=Path)
    parser.add_argument("--apply", action="store_true", help="delete exact duplicates")
    args = parser.parse_args()

    problem_path = args.problem_path
    if not problem_path.is_dir():
        parser.error(f"problem path does not exist: {problem_path}")

    removals = duplicate_removals(problem_path)
    if not removals:
        print("No exact duplicate statement samples found.")
        return 0

    action = "Removing" if args.apply else "Would remove"
    for path in removals:
        print(f"{action} {path}")
        if args.apply:
            path.unlink()
    if not args.apply:
        print("Rerun with --apply to delete these exact duplicates.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
