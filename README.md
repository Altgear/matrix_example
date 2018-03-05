[![Build Status](https://travis-ci.org/Alttgear/matrix_example.svg?branch=test)](https://travis-ci.org/Altgear/matrix_example)

```
cmake -H. -B_builds -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON
cmake --build _builds
cmake --build _builds --target test -- ARGS=--verbose
_builds/example
```
