/*
 * amf3_gpp_access_registration.h
 *
 *
 */

#ifndef _OpenAPI_amf3_gpp_access_registration_H_
#define _OpenAPI_amf3_gpp_access_registration_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "backup_amf_info.h"
#include "context_info.h"
#include "eps_interworking_info.h"
#include "guami.h"
#include "ims_vo_ps.h"
#include "rat_type.h"
#include "vgmlc_address.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_amf3_gpp_access_registration_s OpenAPI_amf3_gpp_access_registration_t;
typedef struct OpenAPI_amf3_gpp_access_registration_s {
    char *amf_instance_id;
    char *supported_features;
    int purge_flag;
    char *pei;
    OpenAPI_ims_vo_ps_e ims_vo_ps;
    char *dereg_callback_uri;
    char *amf_service_name_dereg;
    char *pcscf_restoration_callback_uri;
    char *amf_service_name_pcscf_rest;
    int initial_registration_ind;
    struct OpenAPI_guami_s *guami;
    OpenAPI_list_t *backup_amf_info;
    int dr_flag;
    OpenAPI_rat_type_e rat_type;
    int urrp_indicator;
    char *amf_ee_subscription_id;
    struct OpenAPI_eps_interworking_info_s *eps_interworking_info;
    int ue_srvcc_capability;
    char *registration_time;
    struct OpenAPI_vgmlc_address_s *vgmlc_address;
    struct OpenAPI_context_info_s *context_info;
    int no_ee_subscription_ind;
} OpenAPI_amf3_gpp_access_registration_t;

OpenAPI_amf3_gpp_access_registration_t *OpenAPI_amf3_gpp_access_registration_create(
    char *amf_instance_id,
    char *supported_features,
    int purge_flag,
    char *pei,
    OpenAPI_ims_vo_ps_e ims_vo_ps,
    char *dereg_callback_uri,
    char *amf_service_name_dereg,
    char *pcscf_restoration_callback_uri,
    char *amf_service_name_pcscf_rest,
    int initial_registration_ind,
    OpenAPI_guami_t *guami,
    OpenAPI_list_t *backup_amf_info,
    int dr_flag,
    OpenAPI_rat_type_e rat_type,
    int urrp_indicator,
    char *amf_ee_subscription_id,
    OpenAPI_eps_interworking_info_t *eps_interworking_info,
    int ue_srvcc_capability,
    char *registration_time,
    OpenAPI_vgmlc_address_t *vgmlc_address,
    OpenAPI_context_info_t *context_info,
    int no_ee_subscription_ind
    );
void OpenAPI_amf3_gpp_access_registration_free(OpenAPI_amf3_gpp_access_registration_t *amf3_gpp_access_registration);
OpenAPI_amf3_gpp_access_registration_t *OpenAPI_amf3_gpp_access_registration_parseFromJSON(cJSON *amf3_gpp_access_registrationJSON);
cJSON *OpenAPI_amf3_gpp_access_registration_convertToJSON(OpenAPI_amf3_gpp_access_registration_t *amf3_gpp_access_registration);
OpenAPI_amf3_gpp_access_registration_t *OpenAPI_amf3_gpp_access_registration_copy(OpenAPI_amf3_gpp_access_registration_t *dst, OpenAPI_amf3_gpp_access_registration_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_amf3_gpp_access_registration_H_ */

