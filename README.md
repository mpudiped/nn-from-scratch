# nn-from-scratch

A neural network written from scratch in C, with no machine learning
libraries, then accelerated on Apple GPUs with Metal kernels I write myself.

The goal is not just a working model. It is to understand every layer of
the stack: how matrices sit in memory, how backpropagation is derived and
computed, why some loops are faster than others, and how a GPU actually
runs a matrix multiply.

## Rules for this project

- **No ML libraries.** Every operation, from matrix multiplication to
  softmax to the training loop, is implemented here.
- **No AI-generated code.** All code in this repository is written by hand.
- **Every gradient is derived on paper first**, then verified numerically
  with gradient checking before it is trusted.
- **Every phase has an exit criterion** that must be met before the next
  phase starts.

## Roadmap

- [x] **Phase 0: Build setup.** Makefile with debug (sanitizers) and release
      modes, automatic header dependencies, and a test target.
- [x] **Phase 1: Matrix library.** Every operation tested against
      hand-computed answers, including non-square shapes.
- [ ] **Phase 2: Single neuron.** Logistic regression on AND and OR, with
      gradient checking.
- [ ] **Phase 3: XOR.** First network with a hidden layer.
- [ ] **Phase 4: General layers.** A network of any depth.
- [ ] **Phase 5: MNIST.** Handwritten digit classification, target of at
      least 97% test accuracy.
- [ ] **Phase 6: CPU performance.** Loop ordering, cache blocking, NEON SIMD
      and threads, measured in GFLOPS.
- [ ] **Phase 7: Metal.** Training on the Apple GPU with hand-written compute
      kernels.

## Requirements

- A Mac with Apple Silicon
- Apple's Command Line Tools (`xcode-select --install`), which provide
  `clang`, `make`, `git` and `lldb`

## Building

```
make                  # debug build, with AddressSanitizer and UBSan
make MODE=release     # optimized build, used for timing
make test             # build and run the tests
make clean            # remove all build output
```

Build output goes to `build/debug/` or `build/release/`, depending on the mode.

## Layout

```
src/      library and program source
tests/    test programs; each prints PASS or FAIL and exits nonzero on failure
data/     datasets (not tracked by git)
build/    compiler output (not tracked by git)
```

## References

- Michael Nielsen, *Neural Networks and Deep Learning*
- Stanford CS231n course notes on backpropagation
- 3Blue1Brown, *Neural Networks* video series
- Apple, Metal documentation