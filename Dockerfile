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

# create ``student`` user for container with password ``student``
RUN useradd -m student && \
    echo student:student | chpasswd

# create ``student-root`` user for container with pswd ``student-root``
RUN useradd -m student-root && \
    echo student-root:student-root | chpasswd && \
    echo 'student-root ALL=(root) ALL' >> /etc/sudoers

USER student
WORKDIR /home/student
