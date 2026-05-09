#!/usr/bin/env python3
# Keep the old browser extension working after testcase.ac moved from the
# legacy Vercel app to the static GitHub Pages frontend. Installed extensions
# still fetch /api/extension/problems from testcase.ac, so the Pages artifact
# needs to include a static response at that exact path.
import argparse
import json
import re
from pathlib import Path


def is_role_file(path: Path, role: str) -> bool:
    return path.stem == role or path.stem.startswith(f"{role}_")


def has_role_file(problem_dir: Path, role: str) -> bool:
    return any(path.is_file() and is_role_file(path, role) for path in problem_dir.iterdir())


def has_testcase_file(problem_dir: Path) -> bool:
    return any(
        path.is_file() and is_role_file(path, "testcase") and path.suffix.lower() == ".txt"
        for path in problem_dir.iterdir()
    )


def is_special_judge(problem_dir: Path) -> bool:
    metadata = problem_dir / "metadata.yaml"
    if not metadata.exists():
        return False

    return any(
        re.match(r"^\s*isSpecialJudge\s*:\s*true\s*(#.*)?$", line)
        for line in metadata.read_text(encoding="utf-8").splitlines()
    )


def is_runnable_problem(problem_dir: Path) -> bool:
    has_correct = has_role_file(problem_dir, "correct")
    has_provider = (
        has_role_file(problem_dir, "generator")
        or has_role_file(problem_dir, "singlegen")
        or has_testcase_file(problem_dir)
    )
    has_required_checker = not is_special_judge(problem_dir) or (
        problem_dir / "checker.cpp"
    ).is_file()
    return has_correct and has_provider and has_required_checker


def main() -> None:
    repo_root = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(
        description="Write static runnable-problem data for the legacy testcase.ac extension."
    )
    parser.add_argument(
        "output",
        nargs="?",
        default=repo_root / "frontend/dist/api/extension/problems",
        type=Path,
        help="Output path. Defaults to frontend/dist/api/extension/problems.",
    )
    parser.add_argument(
        "--testcase-boj-dir",
        default=repo_root / "testcase/boj",
        type=Path,
        help="BOJ testcase directory. Defaults to testcase/boj.",
    )
    args = parser.parse_args()

    testcase_boj_dir = args.testcase_boj_dir
    if not testcase_boj_dir.is_dir():
        raise SystemExit(f"Missing BOJ testcase directory: {testcase_boj_dir}")

    problem_ids = sorted(
        (
            problem_dir.name
            for problem_dir in testcase_boj_dir.iterdir()
            if problem_dir.is_dir()
            and problem_dir.name.isdigit()
            and is_runnable_problem(problem_dir)
        ),
        key=int,
    )

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(
        json.dumps(
            {"existProblemIds": problem_ids},
            ensure_ascii=False,
            separators=(",", ":"),
        )
        + "\n",
        encoding="utf-8",
    )
    print(f"Wrote {len(problem_ids)} runnable BOJ problem ids to {args.output}")


if __name__ == "__main__":
    main()
