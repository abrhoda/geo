#ifndef GEO_FLOAT_H
#define GEO_FLOAT_H

#ifdef __cplusplus
extern "C" {
#endif

#define GEO_TMPL_TYPE float
#define GEO_TMPL_TYPE_FIXED int32_t
#define GEO_ABS_EPSILON 1e-9
#define GEO_REL_EPSILON 1e-6
#define GEO_MAX_ULPS 4
#include "geo_decimal_template.h"
#undef GEO_MAX_ULPS
#undef GEO_REL_EPSILON
#undef GEO_ABS_EPSILON
#undef GEO_TMPL_TYPE_FIXED
#undef GEO_TMPL_TYPE

#ifdef __cplusplus
}
#endif

#endif
