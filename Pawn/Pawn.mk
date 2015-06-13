PATH_PAWN := $(dir $(lastword $(MAKEFILE_LIST)))


# Virtual Machine
AMX_SRCS += amx.c
# amxexec_thumb2_gas.s
INC_PATH += $(PATH_PAWN) $(PATH_PAWN)/amx
SOURCES_AMX += $(AMX_SRCS:%=$(PATH_PAWN)/amx/%)


# amx
DEFINES += AMX_ANSIONLY
# DEFINES += AMX_ALTCORE
# DEFINES += AMX_ASM
# DEFINES += AMX_JIT
# DEFINES += AMX_NATIVECALL
DEFINES += AMX_NATIVETABLE=vm_natives
DEFINES += AMX_NODYNALOAD
DEFINES += AMX_NO_MACRO_INSTR
DEFINES += AMX_NO_OVERLAY
DEFINES += AMX_NO_PACKED_OPC
DEFINES += AMX_NOPROPLIST
DEFINES += AMX_NORANDOM
# DEFINES += AMX_TERMINAL
# DEFINES += AMX_TOKENTHREADING
# DEFINES += NDEBUG

DEFINES += FLOATPOINT


# DEFINES += AMX_ALIGN
# DEFINES += AMX_ALLOT
DEFINES += AMX_CLEANUP
# DEFINES += AMX_CLONE
DEFINES += AMX_DEFCALLBACK
DEFINES += AMX_EXEC
# DEFINES += AMX_FLAGS
DEFINES += AMX_INIT
# DEFINES += AMX_MEMINFO
# DEFINES += AMX_NAMELENGTH
# DEFINES += AMX_NATIVEINFO
# DEFINES += AMX_PUSHXXX
# DEFINES += AMX_RAISEERROR
# DEFINES += AMX_REGISTER
# DEFINES += AMX_SETCALLBACK
# DEFINES += AMX_SETDEBUGHOOK
# DEFINES += AMX_UTF8XXX
# DEFINES += AMX_XXXNATIVES
# DEFINES += AMX_XXXPUBLICS
# DEFINES += AMX_XXXPUBVARS
# DEFINES += AMX_XXXSTRING
# DEFINES += AMX_XXXTAGS
# DEFINES += AMX_XXXUSERDATA
