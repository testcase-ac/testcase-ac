# Backend

[한국어](README.md) | English

Go module for the API server and stresser runtime.

## Setup

```bash
cp .env.example .env
# for local dev against the current checkout:
#   TESTCASE_LOCAL_PATH=/absolute/path/to/testcase-ac

go mod download
go run ./api
```

The API defaults to invoking the stresser at the local Lambda runtime endpoint.
Use `STRESSER_MODE=lambda` for the deployed Lambda.

## Endpoints

```
GET  /api/health
GET  /api/problems?q=&problemType=&limit=&cursor=
GET  /api/problems/{problemType}/{externalId}
POST /api/problems/{problemType}/{externalId}/stress
```

## Stresser

Build from `backend/`:

```bash
go build ./stresser
```

Run Linux/container tests from the repo root:

```bash
./tests/dockertest/run_test.sh ./stresser
```

Run locally through the Lambda runtime:

```bash
docker build -f deploy/stresser.Dockerfile -t testcase-ac-stresser .
docker run --rm -p 9000:8080 testcase-ac-stresser
```

## Known Limitation

The stresser caches compiled programs under `/tmp/compile` inside the running
container. This is intentional for speed, especially for repeated invocations on
warm Lambda containers.

Because warm containers can be reused, submitted source code may remain readable
inside that same container until it is recycled. Do not submit private or secret
source code to the public service.

## Deployment

Production API deploy is handled by [deploy/api.sh](../deploy/api.sh). The
stresser deploy is handled by [deploy/stresser.sh](../deploy/stresser.sh).
