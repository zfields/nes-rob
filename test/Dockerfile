# Container with dependencies necessary to run unit-tests and code coverage

# Build development environment
# $ docker build . --tag nes-rob

# Launch development environment
# $ docker run --interactive --rm --tty --volume $(pwd)/..:/nes-rob/ nes-rob

# Base Image
FROM alpine

# Yarn Install Requirements
RUN ["ash", "-c", "\
    apk add --no-cache \
      gcovr \
      g++ \
"]

WORKDIR /nes-rob/test/
CMD ["./run_all_tests.sh"]
