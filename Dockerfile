FROM alpine:3.3
MAINTAINER Lars Tingelstad <lars.tingelstad@ntnu.no>

RUN apk update && \
    apk upgrade && \
    apk add cmake gcc g++ make && \
    rm -rf /var/cache/apk/*

RUN mkdir -p /usr/src/ \
    && curl -SL https://bitbucket.org/eigen/eigen/get/3.2.8.tar.gz \
    | tar -xvzC /usr/src/ \
    && mkdir -p /usr/src/eigen-eigen-07105f7124f9/build \
    && cd /usr/src/eigen-eigen-07105f7124f9/build/ \
    && cmake .. \
    && make install

RUN mkdir -p /usr/src/vahlen
VOLUME /usr/src/vahlen
