# Container with dependencies necessary to generate documentation

# Build development environment
# $ docker build . --tag nes-rob-docs

# Launch development environment
# $ docker run --rm --volume $(pwd)/..:/nes-rob/ nes-rob-docs

# Restore ownership
# $ sudo chown -R <user>:<group> ..

# Base Image
FROM alpine

# Configure Git
COPY .gitconfig /root/
COPY .netrc /root/

# Yarn Install Requirements
RUN ["ash", "-c", "\
    apk add --no-cache \
      doxygen \
      git \
      graphviz \
      ttf-freefont \
"]

WORKDIR /nes-rob/

# Remove and Rebuild Documentation
CMD ["/nes-rob/docs/.publish-gh-pages.sh"]
