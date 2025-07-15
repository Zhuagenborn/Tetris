FROM ubuntu:latest

RUN apt-get update

RUN apt-get install -y g++

RUN apt-get install -y cmake

RUN apt-get install -y libgtest-dev && apt-get install -y libgmock-dev

RUN apt-get install -y libncurses5-dev && apt-get install -y libncursesw5-dev

ARG work_dir=/usr/src/tetris

RUN mkdir -p $work_dir

WORKDIR $work_dir

COPY . .

RUN mkdir build

WORKDIR $work_dir/build

RUN cmake -DTETRIS_BUILD_TESTS=ON ..

RUN cmake --build .

WORKDIR $work_dir/build/bin

ENTRYPOINT ["ctest", "--test-dir", "..", "-VV"]