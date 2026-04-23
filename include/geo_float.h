#ifndef GEO_FLOAT_H
#define GEO_FLOAT_H

#ifdef __cplusplus
extern "C" {
#endif

#define TMPL_TYPE float
#define TMPL_TYPE_FIXED_SIZE 32
#define ABS_EPSILON 1e-9
#define REL_EPSILON 1e-6
#include "geo_decimal_template.h"
#undef REL_EPSILON
#undef ABS_EPSILON
#undef TMPL_TYPE_FIXED_SIZE
#undef TMPL_TYPE

#ifdef __cplusplus
}
#endif

#endif
