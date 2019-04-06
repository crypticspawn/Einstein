// ==============================
// File:			TProteusMacros.h
// Project:			Einstein
//
// Copyright 2019 by Matthais Melcher (proteus@matthiasm.com).
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// ==============================
// $Id$
// ==============================


#ifndef PROTEUS_MACROS_H
#define PROTEUS_MACROS_H

// --- general includes

#include "TARMProcessor.h"
#include "TMemory.h"
#include "TEmulator.h"
#include "TInterruptManager.h"
#include "TJITGeneric_Macros.h"
#include "TJITGenericROMPatch.h"

namespace NewtOS {

extern TARMProcessor *CPU;
extern TMemory *MEM;
extern TInterruptManager *INT;

// --- macros

/** Accessing the Registers */
#define R0 CPU->mCurrentRegisters[0]
#define R1 CPU->mCurrentRegisters[1]
#define R2 CPU->mCurrentRegisters[2]
#define R3 CPU->mCurrentRegisters[3]
#define R4 CPU->mCurrentRegisters[4]
#define R5 CPU->mCurrentRegisters[5]
#define R6 CPU->mCurrentRegisters[6]
#define R7 CPU->mCurrentRegisters[7]
#define R8 CPU->mCurrentRegisters[8]
#define R9 CPU->mCurrentRegisters[9]
#define R10 CPU->mCurrentRegisters[10]
#define R11 CPU->mCurrentRegisters[11]
#define R12 CPU->mCurrentRegisters[12]
#define R13 CPU->mCurrentRegisters[13]
#define SP CPU->mCurrentRegisters[13]
#define R14 CPU->mCurrentRegisters[14]
#define LR CPU->mCurrentRegisters[14]
#define R15 CPU->mCurrentRegisters[15]
#define PC CPU->mCurrentRegisters[15]

/** Exit the native code to this address in the interpreter */
#define EXIT(addr) { R15 = addr+4; return nullptr; }

/** Push a value onto the stack (stmdb) */
#define PUSH(sp, w) { sp-=4; MEM->Write(sp, w); }

/** Pop a value from the stack (ldmia) */
#define POP(sp, w) { MEM->Read(sp, w); sp+=4; }

/** Reverse pop, (ldmdb) */
#define RPOP(sp, w) { sp-=4; MEM->Read(sp, w); }

/** Read a word from memory */
inline KUInt32 PEEK_W(KUInt32 addr) { KUInt32 w; MEM->Read(addr, w); return w; }

/** Write a word to memory */
#define POKE_W(addr, w) { MEM->Write(addr, w); }

/** Macro to define a getter for a global variable.
 \param addr address of globale variable in RAM
 \param type type of that variable
 \param name name of the variable without the leading 'g'
 */
#define GLOBAL_GETSET_W(addr, type, name) \
const TMemory::VAddr g##name = addr; \
type GetG##name() { KUInt32 w; MEM->Read(g##name, w); return (type)w; } \
void SetG##name(type v) { KUInt32 w=(KUInt32)v; MEM->Write(g##name, w); }

#define GLOBAL_GETSET_W_DECL(addr, type, name) \
extern const TMemory::VAddr g##name; \
extern type GetG##name(); \
extern void SetG##name(type v);

#define GLOBAL_GETSET_P(addr, type, name) \
const TMemory::VAddr g##name = addr; \
type GetG##name() { KUInt32 w; MEM->Read(g##name, w); return (type)(uintptr_t)w; } \
void SetG##name(type v) { KUInt32 w=(KUInt32)(uintptr_t)v; MEM->Write(g##name, w); }

#define GLOBAL_GETSET_P_DECL(addr, type, name) \
extern const TMemory::VAddr g##name; \
extern type GetG##name(); \
extern void SetG##name(type v);

/** Define a class memeber variable and its getter and setter */
#define	T_GETSET_MEMBER_W(offset, type, name) \
type Get##name() { KUInt32 w; MEM->Read(((KUInt32)(uintptr_t)this)+offset, w); return (type)w; } \
void Set##name(type w) { KUInt32 v = (KUInt32)w; MEM->Write(((KUInt32)(uintptr_t)this)+offset, v); }
#define	T_GETSET_MEMBER_P(offset, type, name) \
type Get##name() { KUInt32 w; MEM->Read(((KUInt32)(uintptr_t)this)+offset, w); return (type)(uintptr_t)w; } \
void Set##name(type w) { KUInt32 v = (KUInt32)(uintptr_t)w; MEM->Write(((KUInt32)(uintptr_t)this)+offset, v); }


} // namespace;


#endif /* PROTEUS_MACROS_H */

// ======================================================================= //
//                       - insert insane quote here -                      //
// ======================================================================= //
