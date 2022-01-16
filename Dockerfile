FROM ubuntu:20.04

ENV TZ=Europe/Paris
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y clang make pkg-config check

WORKDIR /build/cvector

CMD make build