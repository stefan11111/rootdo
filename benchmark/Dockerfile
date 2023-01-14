# syntax=docker/dockerfile-upstream:master-labs
FROM debian:bookworm-slim as base

ADD https://codeberg.org/sw1tchbl4d3/stdinify.git#main /stdinify

ENV DEBIAN_FRONTEND noninteractive

# install build dependencies and benchmarked programs
RUN apt-get update
RUN apt-get -y upgrade
RUN apt-get -y --no-install-recommends install make gcc libc6-dev time sudo=1.9.11p3-2 doas=6.8.2-1+b1
RUN apt-get clean
RUN rm -rf /var/lib/apt/lists/*

# create normal user
RUN useradd -m rdo
RUN printf "rdo123\nrdo123" | passwd rdo
RUN groupadd wheel
RUN usermod -a -G wheel rdo

WORKDIR /rdo

# build rdo
RUN --mount=type=bind,target=/rdo,rw \
    make -j "$(nproc)" && \
    make install

WORKDIR /stdinify

# build stdinify
RUN make -j "$(nproc)"
RUN make install

COPY --link benchmark/doas.conf /etc
COPY --link --chown=0:0 --chmod=440 benchmark/sudoers /etc
COPY --link benchmark/run benchmark/whoami-test /usr/local/bin/

USER rdo

WORKDIR /home/rdo

ENTRYPOINT ["run", "sudo", "doas", "rdo"]
