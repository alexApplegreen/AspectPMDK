# AspectPMDK
## A aspect-oriented abstraction of PMDK features for Data Structures in C++

AspectPMDK is a aspect-oriented abstraction of the Intel PMDK: (https://pmem.io/pmdk/),
using AspectC++ (https://www.aspectc.org).
It aims to make datastructures written in C++ work on persistent memory like Intel's Optane.
Therefore it encapsulates the PMDK transactional API and write operations to the datastructure's member variables.

## Dependencies:
* daxctl
* ndctl

https://docs.pmem.io/ndctl-user-guide/installing-ndctl/installing-ndctl-packages-on-linux

## About
This Repository contains 2 datastructures (stack and queue) in 3 flavours:
* vanilla
* persistent (manual with PMDK/libpmemobj++)
* aspect-oriented persistent

For vanilla and AOP variants there is a test- / example program.
The Tests for stack and queue are written using catch2 (https://github.com/catchorg/Catch2).
These test's purpose is to demonstrate the datastructures are operating as one would expect.
Vanilla datastructure's tests can be built with make target stack and queue.

The src/example directory contains several *Example.cpp files.
Those files are supposed to show usage of the AOP variants of the datastructures.
For every datastructure there are 2 examples.
One will initialize a memory pool and instantiate the datastructure while setting it as the pool's root-object.
The tests will then proceed to put elements into the datastructure.

The second example-program will then reference the datastructure from persistent memory and read it's contents.
