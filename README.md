# CVector

An implementation of vectors in C.
Vectors are sequence containers representing arrays that can change in size.

## Build the library

Run the following command to build the library in `build/libcvector.a`:

```shell
$ make build
```

If you want to build it in a docker container:
```shell
$ make docker_build
```

## How it works

CVector is composed of two parts, the **header** and the **body**. The headers contains privates information
such as the length and capacity of the vector. The body contains inserted data.

The headers and body are laid out next two each other as follow:

```
0x00                                         0xFF
┌───────────┬──────────────────────────────────┐
│  Headers  │               Body               │
└───────────┴──────────────────────────────────┘
```

Therefore, when the vector needs to grow, it allocate a new vector with a capacity twice as big and copy all elements from the old vector.  
When a vector **grow** (e.g. `vector_push` and `vector_unshift`), it also free the old one.  
Thus, to **avoid** double free error or **segmentation fault** you must not
copy vector pointers and add a level of indirection instead.

## Documentation

Functions are commented in [header file](./inc/vector.h).
## :stars: Show your support

Please give a :star: if this project helped you!

## :scroll: License

MIT © [Alexandre Negrel](https://www.negrel.dev/)