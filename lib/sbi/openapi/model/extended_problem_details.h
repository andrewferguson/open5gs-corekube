/*
 * extended_problem_details.h
 *
 * Extends ProblemDetails to also include the acceptable service info.
 */

#ifndef _OpenAPI_extended_problem_details_H_
#define _OpenAPI_extended_problem_details_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "acceptable_service_info.h"
#include "extended_problem_details_all_of.h"
#include "invalid_param.h"
#include "problem_details.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_extended_problem_details_s OpenAPI_extended_problem_details_t;
typedef struct OpenAPI_extended_problem_details_s {
    char *type;
    char *title;
    int status;
    char *detail;
    char *instance;
    char *cause;
    OpenAPI_list_t *invalid_params;
    char *supported_features;
    char *target_scp;
    struct OpenAPI_acceptable_service_info_s *acceptable_serv_info;
} OpenAPI_extended_problem_details_t;

OpenAPI_extended_problem_details_t *OpenAPI_extended_problem_details_create(
    char *type,
    char *title,
    int status,
    char *detail,
    char *instance,
    char *cause,
    OpenAPI_list_t *invalid_params,
    char *supported_features,
    char *target_scp,
    OpenAPI_acceptable_service_info_t *acceptable_serv_info
    );
void OpenAPI_extended_problem_details_free(OpenAPI_extended_problem_details_t *extended_problem_details);
OpenAPI_extended_problem_details_t *OpenAPI_extended_problem_details_parseFromJSON(cJSON *extended_problem_detailsJSON);
cJSON *OpenAPI_extended_problem_details_convertToJSON(OpenAPI_extended_problem_details_t *extended_problem_details);
OpenAPI_extended_problem_details_t *OpenAPI_extended_problem_details_copy(OpenAPI_extended_problem_details_t *dst, OpenAPI_extended_problem_details_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_extended_problem_details_H_ */

