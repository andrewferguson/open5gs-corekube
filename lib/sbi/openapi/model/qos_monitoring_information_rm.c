
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "qos_monitoring_information_rm.h"

OpenAPI_qos_monitoring_information_rm_t *OpenAPI_qos_monitoring_information_rm_create(
    int rep_thresh_dl,
    int rep_thresh_ul,
    int rep_thresh_rp
    )
{
    OpenAPI_qos_monitoring_information_rm_t *qos_monitoring_information_rm_local_var = OpenAPI_malloc(sizeof(OpenAPI_qos_monitoring_information_rm_t));
    if (!qos_monitoring_information_rm_local_var) {
        return NULL;
    }
    qos_monitoring_information_rm_local_var->rep_thresh_dl = rep_thresh_dl;
    qos_monitoring_information_rm_local_var->rep_thresh_ul = rep_thresh_ul;
    qos_monitoring_information_rm_local_var->rep_thresh_rp = rep_thresh_rp;

    return qos_monitoring_information_rm_local_var;
}

void OpenAPI_qos_monitoring_information_rm_free(OpenAPI_qos_monitoring_information_rm_t *qos_monitoring_information_rm)
{
    if (NULL == qos_monitoring_information_rm) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(qos_monitoring_information_rm);
}

cJSON *OpenAPI_qos_monitoring_information_rm_convertToJSON(OpenAPI_qos_monitoring_information_rm_t *qos_monitoring_information_rm)
{
    cJSON *item = NULL;

    if (qos_monitoring_information_rm == NULL) {
        ogs_error("OpenAPI_qos_monitoring_information_rm_convertToJSON() failed [QosMonitoringInformationRm]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (qos_monitoring_information_rm->rep_thresh_dl) {
        if (cJSON_AddNumberToObject(item, "repThreshDl", qos_monitoring_information_rm->rep_thresh_dl) == NULL) {
            ogs_error("OpenAPI_qos_monitoring_information_rm_convertToJSON() failed [rep_thresh_dl]");
            goto end;
        }
    }

    if (qos_monitoring_information_rm->rep_thresh_ul) {
        if (cJSON_AddNumberToObject(item, "repThreshUl", qos_monitoring_information_rm->rep_thresh_ul) == NULL) {
            ogs_error("OpenAPI_qos_monitoring_information_rm_convertToJSON() failed [rep_thresh_ul]");
            goto end;
        }
    }

    if (qos_monitoring_information_rm->rep_thresh_rp) {
        if (cJSON_AddNumberToObject(item, "repThreshRp", qos_monitoring_information_rm->rep_thresh_rp) == NULL) {
            ogs_error("OpenAPI_qos_monitoring_information_rm_convertToJSON() failed [rep_thresh_rp]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_qos_monitoring_information_rm_t *OpenAPI_qos_monitoring_information_rm_parseFromJSON(cJSON *qos_monitoring_information_rmJSON)
{
    OpenAPI_qos_monitoring_information_rm_t *qos_monitoring_information_rm_local_var = NULL;
    cJSON *rep_thresh_dl = cJSON_GetObjectItemCaseSensitive(qos_monitoring_information_rmJSON, "repThreshDl");

    if (rep_thresh_dl) {
        if (!cJSON_IsNumber(rep_thresh_dl)) {
            ogs_error("OpenAPI_qos_monitoring_information_rm_parseFromJSON() failed [rep_thresh_dl]");
            goto end;
        }
    }

    cJSON *rep_thresh_ul = cJSON_GetObjectItemCaseSensitive(qos_monitoring_information_rmJSON, "repThreshUl");

    if (rep_thresh_ul) {
        if (!cJSON_IsNumber(rep_thresh_ul)) {
            ogs_error("OpenAPI_qos_monitoring_information_rm_parseFromJSON() failed [rep_thresh_ul]");
            goto end;
        }
    }

    cJSON *rep_thresh_rp = cJSON_GetObjectItemCaseSensitive(qos_monitoring_information_rmJSON, "repThreshRp");

    if (rep_thresh_rp) {
        if (!cJSON_IsNumber(rep_thresh_rp)) {
            ogs_error("OpenAPI_qos_monitoring_information_rm_parseFromJSON() failed [rep_thresh_rp]");
            goto end;
        }
    }

    qos_monitoring_information_rm_local_var = OpenAPI_qos_monitoring_information_rm_create (
        rep_thresh_dl ? rep_thresh_dl->valuedouble : 0,
        rep_thresh_ul ? rep_thresh_ul->valuedouble : 0,
        rep_thresh_rp ? rep_thresh_rp->valuedouble : 0
        );

    return qos_monitoring_information_rm_local_var;
end:
    return NULL;
}

OpenAPI_qos_monitoring_information_rm_t *OpenAPI_qos_monitoring_information_rm_copy(OpenAPI_qos_monitoring_information_rm_t *dst, OpenAPI_qos_monitoring_information_rm_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_qos_monitoring_information_rm_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_qos_monitoring_information_rm_convertToJSON() failed");
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

    OpenAPI_qos_monitoring_information_rm_free(dst);
    dst = OpenAPI_qos_monitoring_information_rm_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

