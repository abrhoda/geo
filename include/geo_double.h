#ifndef GEO_DOUBLE_H
#define GEO_DOUBLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define GEO_TMPL_TYPE double
#define GEO_TMPL_TYPE_SIZE 64
#include "geo_decimal_template.h"
#undef GEO_TMPL_TYPE_SIZE
#undef GEO_TMPL_TYPE

#ifdef __cplusplus
}
#endif

#endif
