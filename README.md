
# Safe Reinterpreted Casts with `std::bit_cast`

`std::bit_cast` is a powerful C++ feature introduced in C++20 that allows you to safely reinterpret-cast between types of the same size without invoking undefined behavior. However, it has one limitation – it only works for types with the same size. But what if you need to perform type conversions between types of different sizes? This is where our utility header comes into play.

## The Problem

When working with different-sized data types, the common approach is to use `reinterpret_cast`, which can lead to undefined behavior in some cases. This method is neither safe nor portable, making it a potential source of bugs and compatibility issues.

## The Solution

We have created a small utility header file that extends the capabilities of `std::bit_cast`. Our solution allows you to use `bit_cast` for almost any type, ensuring safety and avoiding undefined behavior.

## Example

Consider the following example where you want to reinterpret-cast a `float` to a `uint64_t`:

```cpp
float fx = 5.235;

// Old way with reinterpret_cast (unsafe)
auto ux = static_cast<uint64_t>(*reinterpret_cast<uint32_t*>(&fx));

// New way with our utility header (safe)
auto bx = bits::bit_cast<uint64_t>(fx);
```

With our utility header, you can perform this type conversion safely and efficiently without worrying about undefined behavior.

## Features

- **Safety**: Our `bit_cast` extension ensures that you can safely reinterpret-cast between types of different sizes, reducing the risk of undefined behavior in your code.

- **Constexpr**: `bit_cast` is marked as `constexpr`, allowing you to use it in compile-time expressions.

## Getting Started

To get started, simply include our utility header in your project:
```bash
cd safe_hash_source_dir
mkdir build
cmake ..
sudo make install
```

```cpp
#include "safe_cast/safe_cast.h"
```

Now, you can use `bits::bit_cast` to perform safe type conversions between different-sized types.

## Contributions

We welcome contributions from the community to improve and expand this utility. If you have any ideas, bug reports, or feature requests, please feel free to open an issue or submit a pull request.

## License

This utility is provided under the [APACHE License](LICENSE), so you are free to use it in your projects and contribute to its development.

---

Feel free to customize the README content to suit your project's specific details and structure.
