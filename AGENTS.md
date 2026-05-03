# AGENTS.md

`testcase-ac` is the open continuation of testcase.ac: a counterexample-finding platform for competitive programming problems.

## Basic Data Flow

The repository contains code to help find counterexamples for each problem: `correct_*` is the reference answer. `generator_*`, `singlegen_*`, and `testcase_*.txt` provide inputs to test against it.

The frontend sends user code to the API to find counterexamples, the API loads the problem and calls the stresser, and the stresser runs everything and returns any mismatching input as a counterexample to the frontend.


## Project Structure

- `testcase/` is the source of truth for problem data. Contributors should add new problems / change existing correct code / generator / checker here.
- `frontend/` is a Vite + React SPA for viewing and submitting source code to find counterexamples.
- `backend/` is a Go module containing:
  - `api/` for the HTTP API used by the frontend.
  - `stresser/` for execution/stress logic
  - `internal/loader/` for loading testcase problem directories, metadata, source files, and fixed testcase files into structured problem data.
  - `internal/executor/` for compiling and running source programs with language runtimes, limits, validators, and checkers.
  - `internal/verify/` for repository problem verification used by CI and testcase contribution checks; it builds on `loader` and `executor`.
  - `contracts/` for shared types
- `deploy/` contains production deploy scripts and Terraform for the stresser stack. Ideally, if deployment infrastructure is changed, only this folder should be edited.


## Local Development

- Default local entrypoint is `./dev.sh`.
- `./dev.sh frontend` runs only the SPA against a remote API.
- Frontend shared API contracts in `frontend/src/generated/contracts.ts` are generated from `backend/contracts`; after editing backend contracts, run `cd frontend && npm run generate:contracts`.

## Local Testing

Host-local checks are for packages that do not compile or execute testcase programs:

- Run frontend typechecking with `cd frontend && npm run typecheck`.
- Run backend host-safe validation with `cd backend && go test ./api ./contracts ./internal/loader`.
- Host-only `backend/internal/verify` tests do not validate verifier execution behavior.

Docker runtime checks are required for packages that compile or execute testcase programs. Run these commands from the repo root, and do not treat host-only runtime failures as sufficient verification:

- Stresser: `./tests/dockertest/run_test.sh ./stresser`
- Verifier: `./tests/dockertest/run_test.sh ./internal/verify`
- Executor: `./tests/dockertest/run_test.sh ./internal/executor`
- All runtime-backed packages: `./tests/dockertest/run_test.sh`, covering `./stresser`, `./internal/executor`, and `./internal/verify`
- Pass normal Go test flags through the Docker wrapper, for example `./tests/dockertest/run_test.sh ./internal/verify -run TestMissingCorrectWarnsAndSkips -count=1`.

## Deployment

- Deploy the backend API with `./deploy/api.sh`. It builds the Go API binary, builds the testcase author index, syncs `testcase/` to the server, writes the backend environment and systemd/Caddy files, health-checks the inactive blue/green slot, then switches Caddy to it.
- Deploy the stresser with `./deploy/stresser.sh`. It initializes/applies Terraform, builds the stresser Docker image with the production language runtime environment, pushes it to ECR, updates the Lambda, and prints the backend environment values needed by `./deploy/api.sh`.
