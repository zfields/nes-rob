# Container with dependencies necessary to run unit-tests and code coverage

# Build development environment
# $ docker build . --tag nes-rob-test

# Launch development environment
# $ docker run --rm --volume $(pwd)/..:/nes-rob/ nes-rob-test

# Base Image
FROM alpine

# Yarn Install Requirements
RUN ["ash", "-c", "\
    apk add --no-cache \
      gcovr \
      g++ \
      valgrind \
"]

WORKDIR /nes-rob/test/
CMD ["./run_all_tests.sh"]
