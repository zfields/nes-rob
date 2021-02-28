# Container with dependencies necessary to generate documentation

# Build development environment
# $ docker build . --tag nes-rob-docs

# Launch development environment
# $ docker run --rm --volume $(pwd)/..:/nes-rob/ nes-rob-docs

# Base Image
FROM alpine

# Yarn Install Requirements
RUN ["ash", "-c", "\
    apk add --no-cache \
      doxygen \
      ttf-freefont \
      graphviz \
"]

WORKDIR /nes-rob/

# Remove and Rebuild Documentation
CMD ["ash", "-c", "\
    rm -rf /nes-rob/docs/html/ \
 && doxygen Doxyfile \
"]
