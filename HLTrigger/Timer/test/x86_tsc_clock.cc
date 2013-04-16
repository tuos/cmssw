#ifdef __x86_64__
// TSC is only available on x86

#include "x86_tsc.h"
#include "x86_tsc_clock.h"

const bool clock_rdtsc::is_available                = has_tsc() and tsc_allowed();
const bool clock_rdtsc::is_steady                   = has_invariant_tsc();

const bool clock_rdtsc_lfence::is_available         = has_tsc() and tsc_allowed();
const bool clock_rdtsc_lfence::is_steady            = has_invariant_tsc();

const bool clock_rdtsc_mfence::is_available         = has_tsc() and tsc_allowed();
const bool clock_rdtsc_mfence::is_steady            = has_invariant_tsc();

const bool clock_rdtscp::is_available               = has_rdtscp() and tsc_allowed();
const bool clock_rdtscp::is_steady                  = has_invariant_tsc();

const bool clock_rdtsc_native::is_available         = has_tsc() and tsc_allowed();
const bool clock_rdtsc_native::is_steady            = has_invariant_tsc();

const bool clock_rdtsc_lfence_native::is_available  = has_tsc() and tsc_allowed();
const bool clock_rdtsc_lfence_native::is_steady     = has_invariant_tsc();

const bool clock_rdtsc_mfence_native::is_available  = has_tsc() and tsc_allowed();
const bool clock_rdtsc_mfence_native::is_steady     = has_invariant_tsc();

const bool clock_rdtscp_native::is_available        = has_rdtscp() and tsc_allowed();
const bool clock_rdtscp_native::is_steady           = has_invariant_tsc();

#endif // __x86_64__