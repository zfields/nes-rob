# Container with dependencies necessary to run unit-tests and code coverage

# Build development environment
# $ docker build . --tag nes-rob-test

# Launch development environment (mount source root as /nes-rob/)
# $ docker run --rm --volume $(pwd)/../../../:/nes-rob/ --workdir /nes-rob/ nes-rob-test

# Base Image
FROM alpine

# Testing Dependencies
RUN ["ash", "-c", "\
    apk add --no-cache \
      gcovr \
      g++ \
      valgrind \
"]

ENTRYPOINT ["./test/run_all_tests.sh"]
