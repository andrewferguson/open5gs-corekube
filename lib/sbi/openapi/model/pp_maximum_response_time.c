
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pp_maximum_response_time.h"

OpenAPI_pp_maximum_response_time_t *OpenAPI_pp_maximum_response_time_create(
    int maximum_response_time,
    char *af_instance_id,
    int reference_id,
    char *validity_time,
    char *mtc_provider_information
    )
{
    OpenAPI_pp_maximum_response_time_t *pp_maximum_response_time_local_var = OpenAPI_malloc(sizeof(OpenAPI_pp_maximum_response_time_t));
    if (!pp_maximum_response_time_local_var) {
        return NULL;
    }
    pp_maximum_response_time_local_var->maximum_response_time = maximum_response_time;
    pp_maximum_response_time_local_var->af_instance_id = af_instance_id;
    pp_maximum_response_time_local_var->reference_id = reference_id;
    pp_maximum_response_time_local_var->validity_time = validity_time;
    pp_maximum_response_time_local_var->mtc_provider_information = mtc_provider_information;

    return pp_maximum_response_time_local_var;
}

void OpenAPI_pp_maximum_response_time_free(OpenAPI_pp_maximum_response_time_t *pp_maximum_response_time)
{
    if (NULL == pp_maximum_response_time) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(pp_maximum_response_time->af_instance_id);
    ogs_free(pp_maximum_response_time->validity_time);
    ogs_free(pp_maximum_response_time->mtc_provider_information);
    ogs_free(pp_maximum_response_time);
}

cJSON *OpenAPI_pp_maximum_response_time_convertToJSON(OpenAPI_pp_maximum_response_time_t *pp_maximum_response_time)
{
    cJSON *item = NULL;

    if (pp_maximum_response_time == NULL) {
        ogs_error("OpenAPI_pp_maximum_response_time_convertToJSON() failed [PpMaximumResponseTime]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddNumberToObject(item, "maximumResponseTime", pp_maximum_response_time->maximum_response_time) == NULL) {
        ogs_error("OpenAPI_pp_maximum_response_time_convertToJSON() failed [maximum_response_time]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "afInstanceId", pp_maximum_response_time->af_instance_id) == NULL) {
        ogs_error("OpenAPI_pp_maximum_response_time_convertToJSON() failed [af_instance_id]");
        goto end;
    }

    if (cJSON_AddNumberToObject(item, "referenceId", pp_maximum_response_time->reference_id) == NULL) {
        ogs_error("OpenAPI_pp_maximum_response_time_convertToJSON() failed [reference_id]");
        goto end;
    }

    if (pp_maximum_response_time->validity_time) {
        if (cJSON_AddStringToObject(item, "validityTime", pp_maximum_response_time->validity_time) == NULL) {
            ogs_error("OpenAPI_pp_maximum_response_time_convertToJSON() failed [validity_time]");
            goto end;
        }
    }

    if (pp_maximum_response_time->mtc_provider_information) {
        if (cJSON_AddStringToObject(item, "mtcProviderInformation", pp_maximum_response_time->mtc_provider_information) == NULL) {
            ogs_error("OpenAPI_pp_maximum_response_time_convertToJSON() failed [mtc_provider_information]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_pp_maximum_response_time_t *OpenAPI_pp_maximum_response_time_parseFromJSON(cJSON *pp_maximum_response_timeJSON)
{
    OpenAPI_pp_maximum_response_time_t *pp_maximum_response_time_local_var = NULL;
    cJSON *maximum_response_time = cJSON_GetObjectItemCaseSensitive(pp_maximum_response_timeJSON, "maximumResponseTime");
    if (!maximum_response_time) {
        ogs_error("OpenAPI_pp_maximum_response_time_parseFromJSON() failed [maximum_response_time]");
        goto end;
    }


    if (!cJSON_IsNumber(maximum_response_time)) {
        ogs_error("OpenAPI_pp_maximum_response_time_parseFromJSON() failed [maximum_response_time]");
        goto end;
    }

    cJSON *af_instance_id = cJSON_GetObjectItemCaseSensitive(pp_maximum_response_timeJSON, "afInstanceId");
    if (!af_instance_id) {
        ogs_error("OpenAPI_pp_maximum_response_time_parseFromJSON() failed [af_instance_id]");
        goto end;
    }


    if (!cJSON_IsString(af_instance_id)) {
        ogs_error("OpenAPI_pp_maximum_response_time_parseFromJSON() failed [af_instance_id]");
        goto end;
    }

    cJSON *reference_id = cJSON_GetObjectItemCaseSensitive(pp_maximum_response_timeJSON, "referenceId");
    if (!reference_id) {
        ogs_error("OpenAPI_pp_maximum_response_time_parseFromJSON() failed [reference_id]");
        goto end;
    }


    if (!cJSON_IsNumber(reference_id)) {
        ogs_error("OpenAPI_pp_maximum_response_time_parseFromJSON() failed [reference_id]");
        goto end;
    }

    cJSON *validity_time = cJSON_GetObjectItemCaseSensitive(pp_maximum_response_timeJSON, "validityTime");

    if (validity_time) {
        if (!cJSON_IsString(validity_time)) {
            ogs_error("OpenAPI_pp_maximum_response_time_parseFromJSON() failed [validity_time]");
            goto end;
        }
    }

    cJSON *mtc_provider_information = cJSON_GetObjectItemCaseSensitive(pp_maximum_response_timeJSON, "mtcProviderInformation");

    if (mtc_provider_information) {
        if (!cJSON_IsString(mtc_provider_information)) {
            ogs_error("OpenAPI_pp_maximum_response_time_parseFromJSON() failed [mtc_provider_information]");
            goto end;
        }
    }

    pp_maximum_response_time_local_var = OpenAPI_pp_maximum_response_time_create (
        maximum_response_time->valuedouble,
        ogs_strdup_or_assert(af_instance_id->valuestring),
        reference_id->valuedouble,
        validity_time ? ogs_strdup_or_assert(validity_time->valuestring) : NULL,
        mtc_provider_information ? ogs_strdup_or_assert(mtc_provider_information->valuestring) : NULL
        );

    return pp_maximum_response_time_local_var;
end:
    return NULL;
}

OpenAPI_pp_maximum_response_time_t *OpenAPI_pp_maximum_response_time_copy(OpenAPI_pp_maximum_response_time_t *dst, OpenAPI_pp_maximum_response_time_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_pp_maximum_response_time_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_pp_maximum_response_time_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_pp_maximum_response_time_free(dst);
    dst = OpenAPI_pp_maximum_response_time_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

