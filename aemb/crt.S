/*
	FreeRTOS AEMB Port
    Copyright (C) 2011 Aeste Works (M) Sdn Bhd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/
	.global	_vector_reset
	.global	_split
	.global	_start2

	.section	.reset
	.text	0x00
	.org	0x00
_vector_reset:
	brai	_split

	/* TODO: Make it thread safe. */
	.text
	.func	_split
_split:
	msrset	r15, 16			/* Use Div-0 as SEMAPHORE */
	andi	r15, r15, 16	/* MASK (1 << 6) */
	beqid	r15, 0x50
	msrclr	r0,	16
_wait:	/* infinite loop for now */
	brai	_wait
	.endfunc

_start2:
	brai	_split
