# AGENTS.md

`testcase-ac` is the open continuation of testcase.ac: a counterexample-finding platform for competitive programming problems.

## Basic Data Flow

The repository contains code to help find counterexamples for each problem: `correct_*` is the reference solution. `generator_*`, `singlegen_*`, and fixed testcases provide inputs to test against it. Optional answer files provide expected outputs for selected fixed testcases and singlegens.

The frontend sends user code to the API to find counterexamples, the API loads the problem and calls the stresser, and the stresser runs everything and returns any mismatching input as a counterexample to the frontend.


## Project Structure

- `testcase/` is the source of truth for problem data. Contributors should add new problems / change existing correct code / generator / checker here.
- `frontend/` is a Vite + React SPA for viewing and submitting source code to find counterexamples.
- `backend/` is a Go module containing:
  - `api/` for the HTTP API used by the frontend.
  - `stresser/` for execution/stress logic
  - `internal/loader/` for loading testcase problem directories, metadata, source files, fixed testcases, and answer files into structured problem data.
  - `internal/executor/` for compiling and running source programs with language runtimes, limits, validators, and checkers.
  - `internal/verify/` for repository problem verification used by CI and testcase contribution checks; it builds on `loader` and `executor`.
  - `contracts/` for shared types
- `deploy/` contains production deploy scripts and Terraform for the stresser stack. Ideally, if deployment infrastructure is changed, only this folder should be edited.
- `third_party/testlib/` contains the vendored `testlib.h` header used by validators, generators, and checkers.
- C++ source files under `testcase/` can include `testlib.h` and Boost headers in the Docker runtime. Prefer `testlib.h` for validators and checkers, and use Boost algorithms or data structures when they make validation or checking simpler and more reliable.


## Local Development

- Default local entrypoint is `./dev.sh`.
- `./dev.sh frontend` runs only the SPA against a remote API.
- Frontend shared API contracts in `frontend/src/generated/contracts.ts` are generated from `backend/contracts`; after editing backend contracts, run `cd frontend && npm run generate:contracts`.

## Local Testing

Run checks for the affected area. Prefer affected packages over `./...` unless the change is broad.

Frontend:

- `cd frontend && npm test`
- `cd frontend && npm run typecheck`

Backend Go, from `backend/`:

- Test: `go test ./path/to/package` (Tests for `backend/internal/executor` require the Linux runtime environment: use `./tests/dockertest/run_test.sh` instead of direct `go test`.)
- Static Analysis: `go vet ./path/to/package`
- Modernization suggestion: `go fix -diff ./path/to/package`

## Problem Verification

Check that a problem folder is valid and its solutions, testcases, generators, validators, and checkers work together correctly in the Docker runtime:

- `./tests/verify/run_problems.sh testcase/<type>/<id>`

## Deployment

- Deploy the backend API with `./deploy/api.sh`. It builds the Go API binary, builds the testcase author index, syncs `testcase/` to the server, writes the backend environment and systemd/Caddy files, health-checks the inactive blue/green slot, then switches Caddy to it.
- Deploy the stresser with `./deploy/stresser.sh`. It initializes/applies Terraform, builds the stresser Docker image with the production language runtime environment, pushes it to ECR, updates the Lambda, and prints the backend environment values needed by `./deploy/api.sh`.
