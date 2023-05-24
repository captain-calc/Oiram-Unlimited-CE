; Name:    Captain Calc
; Date:    May 23, 2023
; File:    asmutil.asm
; Purpose: Provides the definitions of the functions declared in asmutil.h.
;          Also defines any internal routines used by the public functions.

assume ADL=1

section .text

	public _asm_GetCSC
_asm_GetCSC:
; Arguments:
;   None
; Returns:
;   A == os_GetCSC keycode if key pressed; A == 0 if no key pressed
; Destroys:
;   BC and HL


	ld	hl,$f50010
	xor	a,a
	ld	b,0
.scanGroup:
	inc	b
	bit	3,b
	jr	nz,.notFound
	inc	hl
	inc	hl
	or	a,(hl)
	jr	z,.scanGroup

	ld	c,255
.getKey:
	inc	c
	srl	a
	jr	nz,.getKey
	ld	a,c

; Return 57 - 8 * B + A
	ld	c,8
	mlt	bc
	add	a,57
	sub	a,c
	ret

.notFound:
	xor a,a
	ret
