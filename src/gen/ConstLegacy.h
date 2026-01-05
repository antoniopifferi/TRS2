#pragma once

// Minimal legacy macros used by Globals.ixx (values mirror src/gen/Const.ixx)

#define STRLEN 128
#define PATHLEN 128
#define MAX_LOOP 5
#define LABEL_MAX 16
#define LABEL_NAMELEN 12
#define LABEL_CONTENTLEN 22
#define D2 2
#define MAX_ROI_SUB 4
#define MAX_ACQ 1024
#define MOXY_NUM_SWITCH 2
#define MAX_ROW_FIBER 16
#define STRLEN_FIBER 64
#define MAX_ROW_SOURCE 16
#define MAMM_NUM_BOARD 2
#define MAMM_NUM_LAMBDA 7
#define MAX_SWITCH 10
#define MAX_STEP 6
#define MAX_TRIM 10
#define MAXPOS 10000
#define MHARP_MAX_DET 16
#define MAX_BOARD 4
#define MAX_DET 256
#define MAX_PLOT 16
#define MAX_ROW_PROT 16
#define STRLEN_PROT 128
#define MAX_ROW_PRES_BLOCK 18
#define MAX_ROW_PRES_LOOP 5
#define MAX_ROW_OSCILL 2
#define MAX_PAGE (256*32)
#define MAX_FIBER 64
#define MAX_SOURCE 16

#define MONO_TCP_STRLEN 256
#define N_BIT_DELAYER_GATE 8
#define N_BIT_DELAYER_GATE_COMMAND 8

// Additional missing legacy macros
#define NIRS_REGLEN 128
#define LUCA_REGLEN 128
#define STRLEN_LONG 1024
#define BCD_MAXPIX 2048
#define SWAB_MAX_DET 18
#define MAX_ROW_ROI 32
#define DOSTEP_MAX 3

// simple placeholders for Windows types used in headers (avoid including Windows headers)
#ifndef HANDLE
typedef void* HANDLE;
#endif
#ifndef CRITICAL_SECTION
struct CRITICAL_SECTION {};
#endif
#ifndef CONDITION_VARIABLE
struct CONDITION_VARIABLE {};
#endif

// integer types
#include <cstdint>
#ifndef uint32_t
using uint32_t = std::uint32_t;
#endif
#ifndef uint64_t
using uint64_t = std::uint64_t;
#endif
#ifndef int32_t
using int32_t = std::int32_t;
#endif
#ifndef int64_t
using int64_t = std::int64_t;
#endif

// Placeholder types for external libraries referenced by old headers
typedef void CNVWriter;
typedef void CNVBufferedSubscriber;
typedef void CNVData;
typedef void Swab_TimeTag_TimeTagger;
typedef void Swab_TimeTag_TimeTaggerVirtual;
typedef void Swab_TimeTag_FrequencyMultiplier;
typedef void Swab_TimeTag_TimeTaggerBase;
typedef void Swab_TimeTag_HistogramLogBins;
typedef void Swab_TimeTag_Histogram;
typedef void Swab_TimeTag_FileWriter;
typedef void CDotNetHandle;

// This legacy header provides only minimal definitions to allow compilation of Globals.ixx
