
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "upf_cond.h"

OpenAPI_upf_cond_t *OpenAPI_upf_cond_create(
    OpenAPI_list_t *smf_serving_area,
    OpenAPI_list_t *tai_list
    )
{
    OpenAPI_upf_cond_t *upf_cond_local_var = OpenAPI_malloc(sizeof(OpenAPI_upf_cond_t));
    if (!upf_cond_local_var) {
        return NULL;
    }
    upf_cond_local_var->smf_serving_area = smf_serving_area;
    upf_cond_local_var->tai_list = tai_list;

    return upf_cond_local_var;
}

void OpenAPI_upf_cond_free(OpenAPI_upf_cond_t *upf_cond)
{
    if (NULL == upf_cond) {
        return;
    }
    OpenAPI_lnode_t *node;
    OpenAPI_list_for_each(upf_cond->smf_serving_area, node) {
        ogs_free(node->data);
    }
    OpenAPI_list_free(upf_cond->smf_serving_area);
    OpenAPI_list_for_each(upf_cond->tai_list, node) {
        OpenAPI_tai_free(node->data);
    }
    OpenAPI_list_free(upf_cond->tai_list);
    ogs_free(upf_cond);
}

cJSON *OpenAPI_upf_cond_convertToJSON(OpenAPI_upf_cond_t *upf_cond)
{
    cJSON *item = NULL;

    if (upf_cond == NULL) {
        ogs_error("OpenAPI_upf_cond_convertToJSON() failed [UpfCond]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (upf_cond->smf_serving_area) {
        cJSON *smf_serving_area = cJSON_AddArrayToObject(item, "smfServingArea");
        if (smf_serving_area == NULL) {
            ogs_error("OpenAPI_upf_cond_convertToJSON() failed [smf_serving_area]");
            goto end;
        }

        OpenAPI_lnode_t *smf_serving_area_node;
        OpenAPI_list_for_each(upf_cond->smf_serving_area, smf_serving_area_node)  {
            if (cJSON_AddStringToObject(smf_serving_area, "", (char*)smf_serving_area_node->data) == NULL) {
                ogs_error("OpenAPI_upf_cond_convertToJSON() failed [smf_serving_area]");
                goto end;
            }
        }
    }

    if (upf_cond->tai_list) {
        cJSON *tai_listList = cJSON_AddArrayToObject(item, "taiList");
        if (tai_listList == NULL) {
            ogs_error("OpenAPI_upf_cond_convertToJSON() failed [tai_list]");
            goto end;
        }

        OpenAPI_lnode_t *tai_list_node;
        if (upf_cond->tai_list) {
            OpenAPI_list_for_each(upf_cond->tai_list, tai_list_node) {
                cJSON *itemLocal = OpenAPI_tai_convertToJSON(tai_list_node->data);
                if (itemLocal == NULL) {
                    ogs_error("OpenAPI_upf_cond_convertToJSON() failed [tai_list]");
                    goto end;
                }
                cJSON_AddItemToArray(tai_listList, itemLocal);
            }
        }
    }

end:
    return item;
}

OpenAPI_upf_cond_t *OpenAPI_upf_cond_parseFromJSON(cJSON *upf_condJSON)
{
    OpenAPI_upf_cond_t *upf_cond_local_var = NULL;
    cJSON *smf_serving_area = cJSON_GetObjectItemCaseSensitive(upf_condJSON, "smfServingArea");

    OpenAPI_list_t *smf_serving_areaList;
    if (smf_serving_area) {
        cJSON *smf_serving_area_local;
        if (!cJSON_IsArray(smf_serving_area)) {
            ogs_error("OpenAPI_upf_cond_parseFromJSON() failed [smf_serving_area]");
            goto end;
        }
        smf_serving_areaList = OpenAPI_list_create();

        cJSON_ArrayForEach(smf_serving_area_local, smf_serving_area) {
            if (!cJSON_IsString(smf_serving_area_local)) {
                ogs_error("OpenAPI_upf_cond_parseFromJSON() failed [smf_serving_area]");
                goto end;
            }
            OpenAPI_list_add(smf_serving_areaList, ogs_strdup_or_assert(smf_serving_area_local->valuestring));
        }
    }

    cJSON *tai_list = cJSON_GetObjectItemCaseSensitive(upf_condJSON, "taiList");

    OpenAPI_list_t *tai_listList;
    if (tai_list) {
        cJSON *tai_list_local_nonprimitive;
        if (!cJSON_IsArray(tai_list)) {
            ogs_error("OpenAPI_upf_cond_parseFromJSON() failed [tai_list]");
            goto end;
        }

        tai_listList = OpenAPI_list_create();

        cJSON_ArrayForEach(tai_list_local_nonprimitive, tai_list ) {
            if (!cJSON_IsObject(tai_list_local_nonprimitive)) {
                ogs_error("OpenAPI_upf_cond_parseFromJSON() failed [tai_list]");
                goto end;
            }
            OpenAPI_tai_t *tai_listItem = OpenAPI_tai_parseFromJSON(tai_list_local_nonprimitive);

            OpenAPI_list_add(tai_listList, tai_listItem);
        }
    }

    upf_cond_local_var = OpenAPI_upf_cond_create (
        smf_serving_area ? smf_serving_areaList : NULL,
        tai_list ? tai_listList : NULL
        );

    return upf_cond_local_var;
end:
    return NULL;
}

OpenAPI_upf_cond_t *OpenAPI_upf_cond_copy(OpenAPI_upf_cond_t *dst, OpenAPI_upf_cond_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_upf_cond_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_upf_cond_convertToJSON() failed");
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

    OpenAPI_upf_cond_free(dst);
    dst = OpenAPI_upf_cond_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

