all: gen_c gen_fasm

%: %.c posix_abi.h

.PHONY: all
