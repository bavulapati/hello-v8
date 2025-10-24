# Simple project to interact with `V8` JavaScript Engine

If you are curious about `NodeJS` internals or the `Chromium` browser internals,`V8` is a good place to start exploring.

This simple project is a good playground to understand how `V8` empowers `NodeJS`, `Chromium`, etc.,

There are two samples `hello and logger`.

`hello` is classic `Hello World` example of interacting with `V8` and `logger` exposes a custom `function` that can be consumed from JavaScript.

This project is only tested on `MacOS`.

## Prerequisites

This project needs `cmake and a c++ compiler`

## How to use

- Install `v8` using `homebrew`

```
brew install v8
```

- Build the project

```
cmake -B build
cmake --build build
```

- Run the hello world sample

```
./build/hello
```

- Run the logger sample

```
./build/logger script.js
```

## References

- `V8` [documentation](https://v8.dev/docs/embed)
