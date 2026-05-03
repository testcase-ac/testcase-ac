# testcase-ac

[한국어](README.md) | English

`testcase-ac` is the open source version of testcase.ac.

Find counterexamples for incorrect algorithm solutions. Contribute reference
solutions and generators so others can find counterexamples too.

Each problem has reference code, generators, and optional fixed testcases.
When a user submits their own solution, testcase.ac stress-tests it against the
reference code and looks for an input where the two outputs differ. The
counterexample can be copied, rerun, and debugged directly.

## Data Flow

```text
frontend -> backend API -> stresser
              |
              +-> testcase/
```

The frontend sends submitted source code to the backend API. The API loads the
selected problem from `testcase/` and builds a stresser request. The stresser
compiles and runs the submitted solution, reference solution, and generators;
when a problem has a checker, the stresser uses it too. If outputs mismatch,
the stresser returns the input that exposed the bug.

## Project Structure

- `testcase/` - problem data. See
  [testcase/FORMAT.en.md](testcase/FORMAT.en.md).
- `frontend/` - Vite + React SPA for viewing problems and submitting code.
- `backend/` - backend Go module.
  - `api/` - HTTP API used by the frontend.
  - `stresser/` - stress-test logic that actually runs algorithm solutions.
  - `contracts/` - shared API/stresser types.
- `deploy/` - production deploy scripts and Terraform for the stresser.

## Local Development

Default local entrypoint:

```bash
./dev.sh
```

Frontend only, against the remote API:

```bash
./dev.sh frontend
```

The full local stack expects Docker, Go, and Node. See the component docs for
details.

- [backend/README.md](backend/README.md)
- [frontend/README.md](frontend/README.md)

Validation commands:

```bash
cd frontend && npm run typecheck
cd backend && go test ./api ./contracts
```

Run the basic browser-inclusive E2E smoke test from the repository root:

```bash
./tests/e2e/run_smoke.sh
```

`go test ./stresser` exercises the stresser locally and requires the full
stresser runtime environment. For reproducible stresser validation, run the
Docker-backed test from the repo root:

```bash
./tests/dockertest/run_test.sh ./stresser
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md).

## License

Repository infrastructure and application code are licensed under the MIT
License. See [LICENSE](LICENSE).

Contributions to problem data under `testcase/`, including reference solutions,
generators, and checkers, are licensed under the same terms unless a file notes
otherwise. Some files may include small attributed third-party algorithm snippets;
those snippets remain under their original terms where noted.
