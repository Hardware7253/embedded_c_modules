# Math Helpers Module

## Typical usage
```c
// Map -50 from a range of [-100, 100] to [0, 100]
int32_t mapped_num = map(-50, -100, 100, 0, 100); // Output = 25

// Convert a float into engineering notation
eng_float_t eng_notation = convert_to_eng_notation(1.54e-10);

// Result:
// eng_notation.val = 154.0
// eng_notation.unit_prefix = 'p'
```