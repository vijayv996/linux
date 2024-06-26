#!/bin/sh
# Copyright (C) 2018, Red Hat Inc, Arnaldo Carvalho de Melo <acme@redhat.com>
# SPDX-License-Identifier: LGPL-2.1

[ $# -eq 1 ] && beauty_x86_arch_asm_uapi_dir=$1 || beauty_x86_arch_asm_uapi_dir=tools/perf/trace/beauty/arch/x86/include/uapi/asm/

prctl_arch_header=${beauty_x86_arch_asm_uapi_dir}/prctl.h

print_range () {
	idx=$1
	prefix=$2
	first_entry=$3

	printf "#define x86_arch_prctl_codes_%d_offset %s\n" $idx $first_entry
	printf "static const char *x86_arch_prctl_codes_%d[] = {\n" $idx
	regex=`printf '^[[:space:]]*#[[:space:]]*define[[:space:]]+ARCH_([[:alnum:]_]+)[[:space:]]+(%s[[:xdigit:]]+).*' ${prefix}`
	fmt="\t[%#x - ${first_entry}]= \"%s\",\n"
	grep -E -q $regex ${prctl_arch_header} && \
	(grep -E $regex ${prctl_arch_header} | \
		sed -r "s/$regex/\2 \1/g"	| \
		xargs printf "$fmt")
	printf "};\n\n"
}

print_range 1 0x1 0x1001
print_range 2 0x2 0x2001
print_range 3 0x4 0x4001
