# ZOND*
Allows to **trace memory** dynamically (*prototype, alpha version*).

\**The project named after the Soviet ["Zond"](https://en.wikipedia.org/wiki/Zond_3) mission*

This is a part of *huntl* code-based test generation project.

## Limitations
* Works only with **LLVM-IR** code, translated from **C** (by **clang**).
* Tracks only variables allocated in the **stack**, not in the *heap* (via malloca/free).
* Supports only **integer** scalars (char, short, int, long) single-dimensional **integer arrays**.
* No global variables support.

## Example
Note, this project isn't supposed to be a industrial-level application.
It's purposed only for tracing arrays involved in the following sorting algorithms:
* quick-sort
* bubble-sort
* selection-sort
All the test drivers are produced by *huntl* test generator.