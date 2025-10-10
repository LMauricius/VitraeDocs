# Compiled size reduction

## Static compilation
While shared libraries have their pros,
with the amount of meta-programming and auto-generated code in VitraeEngine and its plugins,
there can be a lot of bloat when keeping the libraries in separate files.

Additionally, static linking could enable some smart whole program optimizations,
which might increase performance.

### Comparison
For example, lets look at one random anegdotal case
(the numbers are handwaved because I forgot to write some of them down):
|                                      | Shared | Static |
| ------------------------------------ | ------ | ------ |
| Release mode - uncompressed total    | 4.3MB  | 2.1MB  |
| Release mode - compressed            | 1.3MB  | ~700kB |
| MinSizeRel mode - uncompressed total | 4.0MB  | 1.1MB  |
| MinSizeRel mode - compressed         | 1.1MB  | ~500kB |

### How to do it
Simply set `VITRAE_LINKING` CMake variable to `STATIC`. This is now the default.
For example, add `-DVITRAE_LINKING=STATIC` to the CMake command when configuring.