#ifndef GEO_DOUBLE_H
#define GEO_DOUBLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define TMPL_TYPE double
#define TMPL_TYPE_FIXED int64_t
#define ABS_EPSILON 1e-12
#define REL_EPSILON 1e-9
#define MAX_ULPS 4
#include "geo_decimal_template.h"
#undef MAX_ULPS
#undef REL_EPSILON
#undef ABS_EPSILON
#undef TMPL_TYPE_FIXED
#undef TMPL_TYPE

#ifdef __cplusplus
}
#endif

#endif
