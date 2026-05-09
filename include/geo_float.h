#ifndef GEO_FLOAT_H
#define GEO_FLOAT_H

#ifdef __cplusplus
extern "C" {
#endif

#define GEO_TMPL_TYPE float
#define GEO_TMPL_TYPE_SIZE 32
#include "geo_decimal_template.h"
#undef GEO_TMPL_TYPE_SIZE
#undef GEO_TMPL_TYPE

#ifdef __cplusplus
}
#endif

#endif
