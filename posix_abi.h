#ifndef POSIX_ABI_GEN_H
#define POSIX_ABI_GEN_H

/************************************************************************
 * This file contains POSIX ABI generated from mix of values defined in
 * libraries and predefined information (like parameter names).
 *
 * To use it iterate over `gen_constants` and `gen_syscalls` arrays
 * and emit whatever your language or assembler can parse.
 */

struct gen_constant
{
	char const* name;
	signed long long sint;
};

struct gen_constants
{
	struct gen_constant *data;
	unsigned count;
} extern gen_constants;


struct gen_parameter
{
	char const* name;
	enum { GEN_PTR, GEN_INT } kind;
};

struct gen_signature
{
	struct gen_parameter *data;
	unsigned count;
};

struct gen_syscall
{
	int number;
	char const* name;
	struct gen_signature signature;
};

struct gen_syscalls
{
	struct gen_syscall *data;
	unsigned count;
} extern gen_syscalls;

#endif // POSIX_ABI_GEN_H

#ifdef GEN_IMPLEMENTATION

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

#define GEN_INITIALIZE_WITH_STORAGE(storage) { .data = storage, .count = sizeof(storage) / sizeof(*storage) }
// TODO: Not only ints
#define GEN_CONSTANT(constant) { .name = #constant, .sint = constant }

struct gen_constant gen_constants_storage[] = {
	GEN_CONSTANT(STDIN_FILENO),
	GEN_CONSTANT(STDOUT_FILENO),
	GEN_CONSTANT(STDERR_FILENO),

	GEN_CONSTANT(AF_UNIX),
	GEN_CONSTANT(AF_LOCAL),
	GEN_CONSTANT(AF_INET),
	GEN_CONSTANT(AF_AX25),
	GEN_CONSTANT(AF_IPX),
	GEN_CONSTANT(AF_APPLETALK),
	GEN_CONSTANT(AF_X25),
	GEN_CONSTANT(AF_INET6),
	GEN_CONSTANT(AF_DECnet),
	GEN_CONSTANT(AF_KEY),
	GEN_CONSTANT(AF_NETLINK),
	GEN_CONSTANT(AF_PACKET),
	GEN_CONSTANT(AF_RDS),
	GEN_CONSTANT(AF_PPPOX),
	GEN_CONSTANT(AF_LLC),
	GEN_CONSTANT(AF_IB),
	GEN_CONSTANT(AF_MPLS),
	GEN_CONSTANT(AF_CAN),
	GEN_CONSTANT(AF_TIPC),
	GEN_CONSTANT(AF_BLUETOOTH),
	GEN_CONSTANT(AF_ALG),
	GEN_CONSTANT(AF_VSOCK),
	GEN_CONSTANT(AF_KCM),
	GEN_CONSTANT(AF_XDP),
	GEN_CONSTANT(SOCK_STREAM),
	GEN_CONSTANT(SOCK_DGRAM),
	GEN_CONSTANT(SOCK_SEQPACKET),
	GEN_CONSTANT(SOCK_RAW),
	GEN_CONSTANT(SOCK_RDM),
	GEN_CONSTANT(SOCK_PACKET),
};

struct gen_constants gen_constants = GEN_INITIALIZE_WITH_STORAGE(gen_constants_storage);

#define GEN_SYSCALL(syscall) { \
	.number = SYS_ ## syscall, \
	.name = #syscall, \
	.signature = GEN_INITIALIZE_WITH_STORAGE(gen_ ## syscall ## _syscall_parameters_storage), \
	}

struct gen_parameter gen_socket_syscall_parameters_storage[] = {
	{ .name = "domain",   .kind = GEN_INT, },
	{ .name = "type",     .kind = GEN_INT, },
	{ .name = "protocol", .kind = GEN_INT, },
};

struct gen_parameter gen_exit_syscall_parameters_storage[] = {
	{ .name = "status", .kind = GEN_INT }
};

struct gen_parameter gen_write_syscall_parameters_storage[] = {
	{ .name = "fd",    .kind = GEN_INT, },
	{ .name = "buf",   .kind = GEN_PTR, },
	{ .name = "count", .kind = GEN_INT },
};

struct gen_parameter gen_read_syscall_parameters_storage[] = {
	{ .name = "fd",    .kind = GEN_INT, },
	{ .name = "buf",   .kind = GEN_PTR, },
	{ .name = "count", .kind = GEN_INT },
};

struct gen_syscall gen_syscalls_storage[] = {
	GEN_SYSCALL(exit),
	GEN_SYSCALL(read),
	GEN_SYSCALL(socket),
	GEN_SYSCALL(write),
};

struct gen_syscalls gen_syscalls = GEN_INITIALIZE_WITH_STORAGE(gen_syscalls_storage);

#endif
