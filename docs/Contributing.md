# Contributing

Thanks for your interest in contributing!

Guidelines:
- Open an issue for proposed changes or bug reports.
- Use topic branches; name them like `feature/description` or `fix/issue-number`.
- Follow existing coding style. A clang-format file will be added; run `clang-format -i` before submitting PRs.
- Add unit tests for any behavior you change or add.
- CI will run builds and tests on PRs.

How to run unit tests locally:
- mkdir build && cd build
- cmake .. && cmake --build .
- ctest --output-on-failure

License and CLA:
- By contributing you agree to the project's MIT license.
