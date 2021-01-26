# AspectPMDK
## A aspect-oriented abstraction of PMDK features for Data Structures in C++

AspectPMDK is a aspect-oriented abstraction of the Intel PMDK: (https://pmem.io/pmdk/),
using AspectC++ (https://www.aspectc.org).
It aims to make datastructures written in C++ work on persistent memory like Intel's Optane.
Therefore it encapsulates the PMDK transacional API and write operations to the datastructre's member variables.
