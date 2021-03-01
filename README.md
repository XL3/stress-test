# stress-test
Stress-testing wrapper for problem solving purposes.

## Usage
- Instantiate the parameters for your algorithm
  ```cpp
  Stress::Discrete_Parameter dice(1, 6);
  Stress::Discrete_Parameter coin(0, 1);
  ```
- Instantiate the testing object with:
  - The two algorithms
  - Any default return value
  - All the parameters
  ```cpp
  auto multiply_incorrect = [](int a, int b) { return a; };
  auto multiply = [](int a, int b) { return a * b; };
  // This test should fail approximately 50% of the time
  Stress::Test test(multiply_incorrect, multiply, 0, dice, coin);
  ```
- Run the test
  ```cpp
  test.run();
  ```
- On failure the testing object prints a log in the format
  ```
  N trials (parameters)
  -> First result
  -> Second result
  ```