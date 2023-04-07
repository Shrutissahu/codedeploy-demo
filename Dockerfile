# base image
FROM public.ecr.aws/lts/ubuntu:18.04_stable
ENV DEBIAN_FRONTEND=noninteractive
# build as root
USER 0
# install required build tools via packet manager
RUN apt-get update -y && apt-get install -y ca-certificates curl build-essential git cmake libz-dev libssl-dev libcurl4-openssl-dev
RUN apt-get install --yes cmake
RUN cmake --version
# AWSCPPSDK we build s3 and transfer manager
RUN git clone --recurse-submodules https://github.com/aws/aws-sdk-cpp \
    && mkdir sdk_build && cd sdk_build \
    && cmake ../aws-sdk-cpp/ -DCMAKE_BUILD_TYPE=Release -DBUILD_ONLY="s3;transfer" -DENABLE_TESTING=OFF -DBUILD_SHARED_LIBS=OFF \
    && make -j $(nproc) && make install \
    && cd .. \
    && rm -rf sdk_build
# finalize the build
WORKDIR /