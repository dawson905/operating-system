# ubuntu image
FROM ubuntu:22.04

# stop prompts
ENV DEBIAN_FRONTEND=noninteractive

# install tools
RUN apt-get update && apt-get install -y git lynx python3 build-essential && rm -rf /var/lib/apt/lists/*

# work folder
WORKDIR /workspace

# clone repo
RUN git clone https://github.com/mit-pdos/xv6-public.git

# copy file
COPY hello.py /workspace/hello.py

# run program
CMD ["python3", "/workspace/hello.py"]
