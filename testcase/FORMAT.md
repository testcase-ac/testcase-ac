# 문제 데이터 형식

한국어 | [English](FORMAT.en.md)

문제는 `testcase/<problemType>/<externalId>/` 디렉터리 하나로 구성됩니다.
`problemType` 네임스페이스는 열려 있습니다. 기여자가 추가한 값이 그대로
존재하는 문제 유형이 됩니다.

## 파일

문제 디렉터리의 파일은 모두 선택 사항입니다. 단, 실행 가능한 문제로 만들려면
`correct_*` 정답 코드가 하나 이상 필요합니다. 실제 스트레스 실행을 허용하려면
`generator_*`, `singlegen_*`, `testcase_*.txt` 중 하나 이상도 필요합니다.

### `metadata.yaml` (선택)

```yaml
title: "A+B"
externalLink: "https://www.acmicpc.net/problem/1000"
authors:                  # 파일별 작성자/출처 덮어쓰기
  correct_reference.cpp: "problem source or reference-code author"
  testcase_sample_1.txt: "problem source"
timeLimitMs: 2000
memoryLimitMb: 256
isSpecialJudge: false
codes:                    # 파일별 언어 태그 덮어쓰기
  correct_legacy.cpp: cpp14
```

- `title`: 사람이 읽을 문제 제목입니다.
- `externalLink`: 원문 문제로 연결되는 URL입니다.
- `authors`: 파일별 작성자 또는 출처를 덮어쓰는 선택 맵입니다. 값이 있으면
  해당 파일에 한해서 git 커밋 작성자보다 우선 표시됩니다. 외부 대회나 기관에서
  제공한 공식 코드나 샘플 입력처럼 저작권 표시가 필요한 파일에만 명시하세요.
- `timeLimitMs`: 테스트케이스별 시간 제한입니다. 단위는 밀리초입니다.
- `memoryLimitMb`: 테스트케이스별 메모리 제한입니다. 단위는 MB입니다.
- `isSpecialJudge`: 원문 문제가 스페셜 저지인지 나타냅니다. 프론트엔드가
  체커 관련 UI를 보여줄지 결정할 때 사용합니다.
- `codes`: 파일 이름에서 추론한 언어 태그를 덮어쓰는 선택 맵입니다. 예를 들어
  `.cpp` 파일의 기본값인 `cpp23` 대신 특정 파일을 `cpp14`로 고정할 수 있습니다.

### `type_metadata.yaml` (문제 유형 디렉터리에서 선택)

`testcase/<problemType>/type_metadata.yaml`은 해당 문제 유형의 프론트엔드 탐색
라벨과 정렬을 정의합니다. 문제 자체의 존재 여부는 여전히 파일시스템의 문제
디렉터리에서 결정되며, 이 파일은 표시용 메타데이터입니다.

예: [koi/type_metadata.yaml](koi/type_metadata.yaml)

```yaml
schemaVersion: 1
label: KOI
segments:
  - label: "{}년"
  - label: "{}차대회"
  - labels:
      elem: "초등부"
      mid: "중등부"
      high: "고등부"
  - label: "{}번"
```

- `schemaVersion`: 현재 `1`만 지원합니다.
- `label`: 루트 문제 유형 라벨입니다. 예를 들어 `/koi`에서 `KOI`로 표시됩니다.
- `segments`: `externalId`를 `/`로 나눈 각 깊이의 표시 규칙입니다.
- `segments[].label`: `{}` 자리에 실제 경로 조각을 넣어 표시합니다.
- `segments[].labels`: 특정 경로 조각을 라벨로 매핑합니다. YAML에 적힌 순서가
  프론트엔드 정렬 순서로도 사용됩니다. 이 값이 없으면 숫자로 해석 가능한 값은
  숫자순, 나머지는 사전순으로 정렬합니다.

### `description.md` (선택)

Markdown 문제 설명입니다. 원문 문제 설명의 저작권을 가지고 있지 않다면
추가하지 않습니다. 예를 들어 외부 저지의 문제를 미러링하는 경우에는 생략합니다.

### `correct_*` (실행 가능한 문제에는 하나 이상 필요)

정답 코드입니다. 파일 이름이 `correct`로 시작해야 정답 코드로 읽힙니다.
예: `correct_basic.cpp`, `correct.py`. 언어는 확장자에서 추론하며,
`metadata.yaml`에서 덮어쓸 수 있습니다.

`correct_*` 파일이 여러 개 있으면 모두 사용자에게 표시되고, 스트레스 요청에서
하나를 선택할 수 있습니다. 기본 순서는 파일 이름의 사전순입니다.

### `generator_*` (선택)

파라미터를 받는 랜덤 테스트 제너레이터입니다. 파일 이름이 `generator`로
시작해야 제너레이터로 읽힙니다. 예: `generator_random.cpp`. 실행 파일은
첫 번째 위치 인자로 시드를 받아야 하며, 같은 시드에 대해 바이트 단위로 동일한
출력을 만들어야 합니다.

### `singlegen_*` (선택)

시드를 읽지 않고 고정 출력을 만드는 1회성 제너레이터입니다. 출력이 너무 커서
텍스트로 커밋하기 어렵지만 생성 로직은 결정적인 경우에 유용합니다. 파일 이름이
`singlegen`으로 시작해야 단일 제너레이터로 읽힙니다. 예:
`singlegen_large.py`.

### `testcase_*.txt` (선택)

고정 입력 텍스트입니다. 파일 이름이 `testcase`로 시작하고 `.txt`로 끝나야
고정 입력으로 읽힙니다. 예: `testcase_sample.txt`. UTF-8 텍스트여야 합니다.

### `validator.cpp` (필수)

`testlib.h`를 사용하는 입력 벨리데이터 입니다. 파일 이름은 정확히 이 이름이어야
합니다. 커밋된 모든 제너레이터 / 테스트케이스의 출력은 이 밸리데이터를 통과해야 합니다.

### `checker.cpp` (선택)

`testlib.h`를 사용하는 스페셜 저지 체커입니다. 파일 이름은 정확히 이 이름이어야
합니다. 파일이 있으면 stresser는 제출 코드의 출력이 허용되는지 판단할 때
체커를 사용합니다. 파일이 없으면 기본 출력 비교를 사용하며, 일반적인 정답 출력
형식이면 충분합니다.

## 지원 언어

API와 stresser가 받는 언어 태그입니다.

- `cpp23`
- `cpp20`
- `cpp17`
- `cpp14`
- `c11`
- `c99`
- `python3`
- `pypy3`
- `java`
- `nodejs`
- `golang`
- `kotlin`
- `rust2021`
- `csharp`

저장소의 파일은 확장자에 따라 아래 기본 태그를 추론합니다.

| 확장자 | 기본 태그 |
|--------|-----------|
| `.cpp` | `cpp23`   |
| `.c`   | `c11`     |
| `.py`  | `python3` |
| `.java` | `java`   |
| `.js`  | `nodejs`  |
| `.go`  | `golang`  |
| `.kt`  | `kotlin`  |
| `.rs`  | `rust2021` |
| `.cs`  | `csharp`  |

파일별 언어 태그를 고정하려면 `metadata.yaml`의 `codes` 맵을 사용합니다.

## 결정성

제너레이터는 결정적이어야 합니다. 같은 시드로 두 번 실행했을 때 바이트 단위로
동일한 출력을 만들어야 합니다. `time(NULL)`, `std::random_device` 등
재현할 수 없는 입력원은 사용하지 않습니다.
