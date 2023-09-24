#include <stdio.h>

#define GEN_IMPLEMENTATION
#include "posix_abi.h"

int main()
{
	for (unsigned i = 0; i < gen_constants.count; ++i) {
		struct gen_constant constant = gen_constants.data[i];
		printf("#define %s %lld\n", constant.name, constant.sint);
	}

	puts("");

	for (unsigned i = 0; i < gen_syscalls.count; ++i) {
		struct gen_syscall syscall = gen_syscalls.data[i];
		printf("#define SYS_%s %d\n", syscall.name, syscall.number);
	}

	puts("");

	for (unsigned i = 0; i < gen_syscalls.count; ++i) {
		struct gen_syscall syscall = gen_syscalls.data[i];
		printf("int %s(", syscall.name);

		for (unsigned j = 0; j < syscall.signature.count; ++j) {
			// TODO: Generate implementation that calls given syscall

			switch (syscall.signature.data[j].kind) {
			break; case GEN_INT: printf("int");
			break; case GEN_PTR: printf("void*");
			}

			printf(" %s%s", syscall.signature.data[j].name, j+1 == syscall.signature.count ? ");" : ", ");
		}
		printf(" // %s", syscall.short_description);
		puts("");
	}
}
