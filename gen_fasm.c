#include <stdio.h>

#define GEN_IMPLEMENTATION
#include "posix_abi.h"

void print_used_syscall_macros();

int main()
{
	for (unsigned i = 0; i < gen_constants.count; ++i) {
		struct gen_constant constant = gen_constants.data[i];
		printf("%s equ %lld\n", constant.name, constant.sint);
	}
	puts("");

	for (unsigned i = 0; i < gen_syscalls.count; ++i) {
		struct gen_syscall syscall = gen_syscalls.data[i];
		printf("SYS_%s equ %d\n", syscall.name, syscall.number);
	}
	puts("");

	print_used_syscall_macros();
	puts("");

	for (unsigned i = 0; i < gen_syscalls.count; ++i) {
		struct gen_syscall syscall = gen_syscalls.data[i];
		printf("macro %s", syscall.name);
		for (unsigned j = 0; j < syscall.signature.count; ++j) {
			printf(" %s%s", syscall.signature.data[j].name, j+1 == syscall.signature.count ? "" : ",");
		}
		printf(" ;; %s\n{\n", syscall.short_description);
		printf("  syscall%u SYS_%s", syscall.signature.count, syscall.name);
		for (unsigned j = 0; j < syscall.signature.count; ++j) {
			printf(", %s", syscall.signature.data[j].name);
		}
		puts("\n}");
	}
}

void print_used_syscall_macros()
{
	unsigned syscall_present[6] = {};
	for (unsigned i = 0; i < gen_syscalls.count; ++i) {
		syscall_present[gen_syscalls.data[i].signature.count]++;
	}

	for (unsigned i = 0; i < sizeof(syscall_present)/sizeof(*syscall_present); ++i) {
		if (syscall_present[i] == 0) { continue; }

		printf("macro syscall%u nr", i);

		for (unsigned arg = 1; arg <= i; ++arg) { printf(", _%u", arg); }
		puts("\n{");
		static char const* register_names[] = { "rax", "rdi", "rsi", "rdx", "r10", "r8", "r9" };
		printf("  mov %s, nr\n", register_names[0]);
		for (unsigned arg = 1; arg <= i; ++arg) { printf("  mov %s, _%u\n", register_names[arg], arg); }
		puts("  syscall");
		puts("}");
	}
}
