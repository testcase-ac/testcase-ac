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

Host-local checks cover packages whose tests either avoid testcase program execution or stub it through the executor seam:

- Run frontend typechecking with `cd frontend && npm run typecheck`.
- Run backend host-safe validation with `cd backend && go test ./api ./contracts ./internal/loader ./internal/verify ./stresser`.

Docker runtime checks are required for executor compile/run behavior and real problem verification. Run these commands from the repo root, and do not treat host-only runtime failures as sufficient verification:

- Executor: `./tests/dockertest/run_test.sh ./internal/executor`
- Real problem verification: `./tests/verify/run_problems.sh testcase/<type>/<id>`
- All runtime-backed package tests: `./tests/dockertest/run_test.sh`, covering `./internal/executor`.

## Deployment

- Deploy the backend API with `./deploy/api.sh`. It builds the Go API binary, builds the testcase author index, syncs `testcase/` to the server, writes the backend environment and systemd/Caddy files, health-checks the inactive blue/green slot, then switches Caddy to it.
- Deploy the stresser with `./deploy/stresser.sh`. It initializes/applies Terraform, builds the stresser Docker image with the production language runtime environment, pushes it to ECR, updates the Lambda, and prints the backend environment values needed by `./deploy/api.sh`.
