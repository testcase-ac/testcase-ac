# Deploy

이 디렉터리의 스크립트와 Terraform은 testcase.ac에서 사용하는 프로덕션 배포
기본값입니다. 개인 포크나 다른 환경에서는 조정이 필요할 수 있습니다.

- `api.sh`는 백엔드 API를 빌드하고 testcase 데이터를 동기화한 뒤 blue/green 슬롯을
  전환합니다. GitHub Actions는 AWS OIDC로 인증한 뒤 임시 Lightsail SSH 자격 증명을
  요청하며, Lambda 호출 자격 증명은 호스트의 root 전용 영구 환경 파일에 둡니다.
- `stresser.sh`는 stresser 런타임 이미지를 빌드해 ECR/Lambda 쪽 배포를 갱신합니다.
- `stresser-release.sh`는 테스트된 로컬 이미지를 게시하고 인프라 변경 없이 기존
  Lambda를 갱신합니다. 관련 변경이 `main`에 반영되면 GitHub Actions가 이 경로를
  사용합니다.
- `terraform/`은 stresser 배포 대상 인프라를 정의합니다.

stresser의 OS 이미지와 제출 코드용 도구 버전은 `stresser.Dockerfile`에서 별도로
고정합니다. `contestant-rpms` 단계는 기존 Amazon Linux 저장소에서 언어 패키지를
다운로드합니다. 최종 이미지는 새 OS에 같은 RPM 버전을 설치하고 빌드 중 설치된
버전을 검사합니다. Go, .NET, Kotlin, PyPy도 각각 버전을 고정합니다. 대상 저지와
비교할 수 있을 때까지 패치 릴리스를 포함해 제출 코드용 버전을 유지합니다.
플랫폼 빌드용 Go 컴파일러는 `contestant-go` 단계와 독립적으로 업그레이드할 수
있습니다. Boost 헤더도 C++ 컴파일러와 별도로 업그레이드합니다.

플랫폼의 배포 방식이 바뀔 때는 가능하면 이 `deploy/` 디렉터리 안의 파일만 수정하는
것을 강하게 권장합니다. 애플리케이션 코드와 운영 배포 설정의 경계를 분명하게
유지하기 위함입니다.
