# 백엔드

한국어 | [English](README.en.md)

API 서버와 stresser 런타임을 담은 Go 모듈입니다.

## 설정

```bash
cp .env.example .env
# 현재 체크아웃을 사용하는 로컬 개발:
#   TESTCASE_LOCAL_PATH=/absolute/path/to/testcase-ac

go mod download
go run ./api
```

API는 기본적으로 로컬 Lambda 런타임 엔드포인트의 stresser를 호출합니다.
배포된 Lambda를 사용하려면 `STRESSER_MODE=lambda`를 설정하세요.

## 엔드포인트

```
GET  /api/health
GET  /api/problems?q=&problemType=&limit=&cursor=
GET  /api/problems/{problemType}/{externalId}
POST /api/problems/{problemType}/{externalId}/stress
```

## Stresser

`backend/`에서 빌드합니다.

```bash
go build ./stresser
```

저장소 루트에서 Linux/컨테이너 테스트를 실행합니다.

```bash
./tests/dockertest/run_test.sh ./stresser
```

Lambda 런타임을 통해 로컬에서 실행합니다.

```bash
docker build -f deploy/stresser.Dockerfile -t testcase-ac-stresser .
docker run --rm -p 9000:8080 testcase-ac-stresser
```

## 알려진 제한

stresser는 실행 중인 컨테이너 내부의 `/tmp/compile` 아래에 컴파일된 프로그램을
캐시합니다. 이는 특히 warm Lambda 컨테이너에서 반복 호출 속도를 높이기 위한
의도적인 동작입니다.

warm 컨테이너는 재사용될 수 있으므로, 제출한 소스 코드는 컨테이너가 재활용될
때까지 같은 컨테이너 안에서 읽을 수 있는 상태로 남을 수 있습니다. 공개 서비스에
비공개 또는 민감한 소스 코드를 제출하지 마세요.

## 배포

운영 API 배포는 [deploy/api.sh](../deploy/api.sh)가 담당합니다. stresser 배포는
[deploy/stresser.sh](../deploy/stresser.sh)가 담당합니다.
