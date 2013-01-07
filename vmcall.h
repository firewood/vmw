/*
	vmcall.h
	VMware backdoor call header

	Copyright (c) 2006 Ken Kato
*/

#ifndef _VMCALL_H_
#define _VMCALL_H_

#include "vmint.h"

/*
	data struct for register values

	DO NOT change the order of members because it is hard-coded
	in the assembly portion of the code

	use uint8_t[4] for members instead of uint32_t in order to
	avoid dealing with compiler's struct alignment
*/

#ifdef __x86_64__

typedef union {
	unsigned long long value;
	struct {
		unsigned int low;
		unsigned int high;
	} r32;
} _reg;

#else

typedef union {
	unsigned int value;
	struct {
		unsigned int low;
	} r32;
} _reg;

#endif

typedef struct _reg_t {
	_reg eax;
	_reg ebx;
	_reg ecx;
	_reg edx;
	_reg ebp;
	_reg edi;
	_reg esi;
} reg_t;

/* member accessing macros */

#define R_EAX(r)	r.eax.value
#define R_EBX(r)	r.ebx.value
#define R_ECX(r)	r.ecx.value
#define R_EDX(r)	r.edx.value
#define R_EBP(r)	r.ebp.value
#define R_EDI(r)	r.edi.value
#define R_ESI(r)	r.esi.value

/*
	accesses VMware backdoor I/O ports
 */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*	access command port with 'in' instruction */
void vmcall_cmd(reg_t *reg);

/*	access enhanced rpc data port with 'ins' instruction */
void vmcall_rpc_ins(reg_t *reg);

/*	access enhanced rpc data port with 'outs' instruction */
void vmcall_rpc_outs(reg_t *reg);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* _VMCALL_H_ */
