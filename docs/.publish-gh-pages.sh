#!/bin/sh

# Rebuild Documentation
rm -rf /nes-rob/docs/html/
doxygen Doxyfile

# Prepare Git
git branch --delete --force gh-pages
git checkout -b gh-pages

# Scrub Repository
rm -f * docs/* .gitmodules
rm -rf docs/img/ examples/ src/ test/

# Promote HTML
mv docs/html/* .

# Publish API Documentation to gh-pages
git add .
git commit -m "\`gh-pages\` API Documentation"
git push origin gh-pages --force

# Restore Repository
git checkout main
git reset HEAD --hard
git clean -fdx
git submodule update
