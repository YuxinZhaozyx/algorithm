FROM ubuntu

ENV LANG=C.UTF-8 LC_ALL=C.UTF-8

# set apt source
RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list \
    && apt-get update -y 

RUN apt-get install build-essential
