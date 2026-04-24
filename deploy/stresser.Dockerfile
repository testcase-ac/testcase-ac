FROM golang:1.25.9 AS build

WORKDIR /src/backend

COPY backend/go.mod backend/go.sum ./
RUN go mod download
COPY backend/contracts ./contracts
COPY backend/stresser ./stresser

ARG TARGETARCH
RUN CGO_ENABLED=0 GOOS=linux GOARCH=${TARGETARCH:-amd64} go build -o /out/bootstrap ./stresser

FROM mcr.microsoft.com/dotnet/sdk:8.0.420 AS dotnet-sdk

FROM --platform=$BUILDPLATFORM mcr.microsoft.com/dotnet/sdk:8.0.420 AS dotnet-prewarm

ARG TARGETARCH
ENV DOTNET_CLI_HOME=/tmp/dotnet
ENV DOTNET_NUGET_SIGNATURE_VERIFICATION=false
ENV DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1
ENV DOTNET_NOLOGO=1
RUN case "${TARGETARCH:-amd64}" in \
        amd64) DOTNET_RUNTIME=linux-x64 ;; \
        arm64) DOTNET_RUNTIME=linux-arm64 ;; \
        *) echo "Unsupported TARGETARCH for dotnet: ${TARGETARCH}" >&2; exit 1 ;; \
    esac \
    && mkdir -p /out \
    && dotnet new console -o /out/CsharpApp \
    && dotnet publish /out/CsharpApp --configuration Release --self-contained true --runtime "${DOTNET_RUNTIME}" \
    && rm -rf /out/CsharpApp/bin \
    && chmod -R 777 /tmp/dotnet/.nuget

FROM amazonlinux:2023.11.20260413.0 AS kotlin-fetch

RUN dnf install -y \
        unzip \
    && dnf clean all

ARG KOTLIN_VERSION=2.3.21
RUN curl -fsSL \
      "https://github.com/JetBrains/kotlin/releases/download/v${KOTLIN_VERSION}/kotlin-compiler-${KOTLIN_VERSION}.zip" \
      -o /tmp/kotlin.zip \
    && unzip -q /tmp/kotlin.zip -d /opt \
    && rm -f /tmp/kotlin.zip

FROM amazonlinux:2023.11.20260413.0

ARG TARGETARCH
RUN dnf install -y \
        ca-certificates \
        bzip2 \
        gcc \
        gcc-c++ \
        java-17-amazon-corretto-devel \
        libicu \
        nodejs \
        python3.13 \
        rust \
        tar \
    && dnf clean all

COPY --from=build /usr/local/go /usr/local/go
COPY --from=build /go/pkg/mod /go/pkg/mod
COPY --from=dotnet-sdk /usr/share/dotnet /usr/share/dotnet
COPY --from=kotlin-fetch /opt/kotlinc /opt/kotlinc

ENV PATH=/usr/local/go/bin:/opt/kotlinc/bin:${PATH}
ENV GOPATH=/go
ENV GOCACHE=/tmp/.cache/go-build
ENV DOTNET_ROOT=/usr/share/dotnet

RUN case "${TARGETARCH:-amd64}" in \
        amd64) PYPY_ARCH=linux64 ;; \
        arm64) PYPY_ARCH=aarch64 ;; \
        *) echo "Unsupported TARGETARCH for PyPy: ${TARGETARCH}" >&2; exit 1 ;; \
    esac \
    && PYPY_PYTHON=3.11 \
    && PYPY_VERSION=v7.3.21 \
    && curl -fsSL --retry 8 --retry-delay 2 --retry-all-errors \
      "https://downloads.python.org/pypy/pypy${PYPY_PYTHON}-${PYPY_VERSION}-${PYPY_ARCH}.tar.bz2" \
      -o /tmp/pypy.tar.bz2 \
    && tar xjf /tmp/pypy.tar.bz2 -C /opt \
    && mv /opt/pypy${PYPY_PYTHON}-${PYPY_VERSION}-${PYPY_ARCH} /opt/pypy \
    && rm -f /tmp/pypy.tar.bz2 \
    && ln -sf /opt/pypy/bin/pypy3 /usr/local/bin/pypy3

RUN ln -sf /usr/share/dotnet/dotnet /usr/local/bin/dotnet

ARG TESTLIB_COMMIT=1e4e8a24c79c6bad3becbdb5a332ffc352b7d5dd
RUN mkdir -p /opt/testlib && \
    curl -fsSL -o /opt/testlib/testlib.h \
        "https://raw.githubusercontent.com/MikeMirzayanov/testlib/${TESTLIB_COMMIT}/testlib.h"

ARG RIE_VERSION=v1.35
RUN ARCH=$(uname -m) && \
    if [ "$ARCH" = "aarch64" ]; then RIE_ARCH=arm64; else RIE_ARCH=x86_64; fi && \
    curl -fsSL -o /usr/local/bin/aws-lambda-rie \
      "https://github.com/aws/aws-lambda-runtime-interface-emulator/releases/download/${RIE_VERSION}/aws-lambda-rie-${RIE_ARCH}" && \
    chmod +x /usr/local/bin/aws-lambda-rie

WORKDIR /var/task
ENV DOTNET_CLI_HOME=/tmp/dotnet
ENV DOTNET_NUGET_SIGNATURE_VERIFICATION=false
ENV DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1
ENV DOTNET_NOLOGO=1
ENV NUGET_PACKAGES=/tmp/dotnet/.nuget/packages
COPY --from=dotnet-prewarm /out/CsharpApp /var/task/CsharpApp
COPY --from=dotnet-prewarm /tmp/dotnet/.nuget /var/task/dotnet-cache/.nuget
COPY --from=build /out/bootstrap /var/task/bootstrap
COPY backend/stresser/entry.sh /var/task/entry.sh
RUN mkdir -p /tmp/dotnet \
    && ln -sf /var/task/dotnet-cache/.nuget /tmp/dotnet/.nuget \
    && chmod +x /var/task/bootstrap /var/task/entry.sh

ENTRYPOINT ["/var/task/entry.sh"]
