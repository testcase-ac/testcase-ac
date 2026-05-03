# testcase-ac

한국어 | [English](README.en.md)

`testcase-ac`는 testcase.ac의 오픈 소스 버전입니다.

틀린 알고리즘 문제의 반례를 찾아보세요. 반례를 찾을 수 있도록 정답 코드와 제너레이터 코드를 기여해보세요.

각 문제에는 정답 코드, 제너레이터, 선택적인 고정 테스트케이스가 있습니다.
사용자가 자신의 풀이를 제출하면, testcase.ac에서 이를 정답 코드와 비교하며
스트레스 테스트를 실행하고, 두 코드의 출력이 달라지는 입력을 찾습니다.
결과로 나온 반례는 그대로 복사해 다시 실행하고 디버깅할 수 있습니다.

## 데이터 흐름

```text
frontend -> backend API -> stresser
              |
              +-> testcase/
```

프론트엔드는 제출 코드를 백엔드 API로 보냅니다. API는 `testcase/`에서 선택한
문제를 읽고 stresser 요청을 만듭니다. stresser는 제출 코드, 정답 코드,
제너레이터를 컴파일하고 실행하며, 문제에 체커가 있으면 체커도 사용합니다.
출력이 다르면 stresser는 버그를 드러낸 입력값을 반환합니다.

## 구조

- `testcase/` - 문제 데이터입니다. 형식은 [testcase/FORMAT.md](testcase/FORMAT.md)를 확인하세요.
- `frontend/` - 문제를 보고 코드를 제출하는 Vite + React SPA입니다.
- `backend/` - 백엔드 Go 모듈입니다.
  - `api/` - 프론트엔드가 사용하는 HTTP API입니다.
  - `stresser/` - 알고리즘 솔루션을 실제로 실행하는 스트레스 테스트 로직입니다.
  - `contracts/` - API와 stresser가 공유하는 타입입니다.
- `deploy/` - 운영 배포 스크립트와 stresser용 Terraform을 담습니다.

## 로컬 개발

기본 실행:

```bash
./dev.sh
```

원격 API를 사용하는 프론트엔드만 실행:

```bash
./dev.sh frontend
```

전체 로컬 스택은 Docker, Go, Node를 사용합니다. 컴포넌트별 설명은 아래 문서를
확인하세요.

- [backend/README.md](backend/README.md)
- [frontend/README.md](frontend/README.md)

변경 사항을 검증할 때는 아래 명령을 사용하세요.

```bash
cd frontend && npm run typecheck
cd backend && go test ./api ./contracts
```

브라우저까지 포함한 기본 E2E 스모크 테스트:

```bash
./tests/e2e/run_smoke.sh
```

실제 Docker 내에서의 compile/run 동작 테스트:

```bash
./tests/dockertest/run_test.sh ./internal/executor
```

## 기여

[CONTRIBUTING.md](CONTRIBUTING.md)를 확인하세요.

## 라이선스

저장소의 인프라와 애플리케이션 코드는 MIT License로 배포됩니다.
[LICENSE](LICENSE)를 확인하세요.

`testcase/`에 기여된 정답 코드, 제너레이터, 체커는 파일에 별도 표기가 없는 한
같은 조건으로 배포됩니다. 일부 파일에는 출처가 표시된 작은 서드파티 알고리즘
스니펫이 포함될 수 있으며, 해당 스니펫은 표시된 경우 원래 조건을 따릅니다.
