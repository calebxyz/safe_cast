# safe_cast
safe reinterpreted casts with std::bit_cast 

Af you know std::bit_cast is great but it has its problems. 
you may cast only types with the same size, but what if you want to use it for all types, its safer doesnt create UB like reinterpret_cast do for some cases and its constexpr. 
I have created this small utility header file so that this will be possible. 

You may use bit_cast from this header almost for any type 

Example:

```
float fx = 5.235;
```
old way:

```
auto ux = static_cast<uint64_t>(*reinterpret_cast<uint32_t*>(&fx));
auto ux2 = *reinterpret_cast<uint64_t*>(&dx);
```

New Way:

```
auto bx = bits::bit_cast<uint64_t>(fx);
```
