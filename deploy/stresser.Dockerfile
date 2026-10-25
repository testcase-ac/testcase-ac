FROM golang:1.27.3 AS build

WORKDIR /src/backend

COPY backend/go.mod backend/go.sum ./
RUN go mod download
COPY backend/contracts ./contracts
COPY backend/internal ./internal
COPY backend/stresser ./stresser

ARG TARGETARCH
RUN CGO_ENABLED=0 GOOS=linux GOARCH=${TARGETARCH:-amd64} go build -o /out/bootstrap ./stresser

FROM golang:1.27.3 AS contestant-go

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

# Keep contestant toolchains on their existing repository while updating the OS.
FROM amazonlinux:2023.11.20260413.0 AS contestant-rpms

RUN dnf install -y dnf-plugins-core gcc gcc-c++ java-17-amazon-corretto-devel nodejs python3.13 rust \
    && mkdir /rpms \
    && rpm -qa --qf '%{NAME} %{NEVRA}\n' \
      | awk '$1 ~ /^(gcc.*|cpp|annobin.*|libgcc|libgomp|libstdc\+\+.*|java-17-amazon-corretto.*|nodejs.*|python3\.13.*|rust.*)$/ {print $2}' \
      | sort > /rpms/versions.txt \
    && xargs dnf download --destdir=/rpms < /rpms/versions.txt

FROM amazonlinux:2023.12.20261021.0 AS kotlin-fetch

RUN dnf install -y \
        unzip \
    && dnf clean all

ARG KOTLIN_VERSION=2.3.21
RUN curl -fsSL \
      "https://github.com/JetBrains/kotlin/releases/download/v${KOTLIN_VERSION}/kotlin-compiler-${KOTLIN_VERSION}.zip" \
      -o /tmp/kotlin.zip \
    && unzip -q /tmp/kotlin.zip -d /opt \
    && rm -f /tmp/kotlin.zip

FROM amazonlinux:2023.12.20261021.0

ARG TARGETARCH
COPY --from=contestant-rpms /rpms/versions.txt /opt/contestant-runtime-rpms.txt
RUN --mount=type=bind,from=contestant-rpms,source=/rpms,target=/tmp/contestant-rpms \
    dnf install -y \
        ca-certificates \
        bzip2 \
        libicu \
        tar \
        /tmp/contestant-rpms/*.rpm \
    && rpm -qa --qf '%{NEVRA}\n' | sort > /tmp/installed-rpms.txt \
    && ! comm -23 /opt/contestant-runtime-rpms.txt /tmp/installed-rpms.txt | grep . \
    && rm /tmp/installed-rpms.txt \
    && dnf clean all

# Pin submitted Go independently from the platform build toolchain.
COPY --from=contestant-go /usr/local/go /usr/local/go
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

ARG BOOST_VERSION=1.92.0
ARG BOOST_DIR=boost_1_92_0
ARG BOOST_TARBALL_SHA256=5c1d40cb8e19adbf740a4ec2da35b3e58f3f5804b1dce44deb53df72193cbc6c

RUN mkdir -p /opt/testlib
COPY third_party/testlib/testlib.h /opt/testlib/testlib.h

RUN curl -fsSL --retry 8 --retry-delay 2 --retry-all-errors \
      "https://archives.boost.io/release/${BOOST_VERSION}/source/${BOOST_DIR}.tar.bz2" \
      -o /tmp/boost.tar.bz2 \
    && echo "${BOOST_TARBALL_SHA256}  /tmp/boost.tar.bz2" | sha256sum -c - \
    && tar xjf /tmp/boost.tar.bz2 -C /tmp \
    && mkdir -p /opt/boost \
    && cp -a "/tmp/${BOOST_DIR}/boost" /opt/boost/boost \
    && cp "/tmp/${BOOST_DIR}/LICENSE_1_0.txt" /opt/boost/LICENSE_1_0.txt \
    && rm -rf /tmp/boost.tar.bz2 "/tmp/${BOOST_DIR}"

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
