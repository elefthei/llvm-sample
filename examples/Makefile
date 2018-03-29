all: foo.bc

foo.bc: foo.c
	clang -O0 -emit-llvm -g -c $^

clean:
	-rm foo.bc
