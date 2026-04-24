# Deploy

이 디렉터리의 스크립트와 Terraform은 testcase.ac에서 사용하는 프로덕션 배포
기본값입니다. 개인 포크나 다른 환경에서는 조정이 필요할 수 있습니다.

- `api.sh`는 백엔드 API를 빌드하고 testcase 데이터를 동기화한 뒤 blue/green 슬롯을
  전환합니다.
- `stresser.sh`는 stresser 런타임 이미지를 빌드해 ECR/Lambda 쪽 배포를 갱신합니다.
- `terraform/`은 stresser 배포 대상 인프라를 정의합니다.

플랫폼의 배포 방식이 바뀔 때는 가능하면 이 `deploy/` 디렉터리 안의 파일만 수정하는
것을 강하게 권장합니다. 애플리케이션 코드와 운영 배포 설정의 경계를 분명하게
유지하기 위함입니다.
