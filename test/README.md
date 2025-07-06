# Backend Test Suite

This folder contains test cases for the BPM Programming System backend (OATPP).

## Running Tests

1. Build the test target (from the project root):
   ```sh
   mkdir -p build && cd build
   cmake .. && make
   ./test_suite_exe  # Replace with your actual test executable name
   ```

2. Example test files:
   - `MyControllerTest.cpp` — API endpoint tests
   - `app/` — Test components and helpers

## Adding Tests
- Add new test cases in this folder or subfolders.
- Use oatpp-test or your preferred C++ test framework.
- Ensure all new features are covered by at least one test.

## Notes
- See the main README for backend and frontend setup.
- For questions, contact the project maintainer. 