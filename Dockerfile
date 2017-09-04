# Dockerfile for Programming Languages Auto-grader

FROM ubuntu:16.04
MAINTAINER Kevin Angstadt <kaa2nx@virginia.edu>

RUN apt-get update && \
    apt-get -y --no-install-recommends install \
        curl \
        gcc \
        gdb \
        less \
        m4 \
        nano \
        software-properties-common \
        sudo \
        wget \
        build-essential

WORKDIR /home/student
