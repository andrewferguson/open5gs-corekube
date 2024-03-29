/*
 * events_notification.h
 *
 * describes the notification of a matched event
 */

#ifndef _OpenAPI_events_notification_H_
#define _OpenAPI_events_notification_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "acc_net_charging_address.h"
#include "access_net_charging_identifier.h"
#include "access_type.h"
#include "accumulated_usage.h"
#include "af_event_notification.h"
#include "an_gw_address.h"
#include "out_of_credit_information.h"
#include "plmn_id.h"
#include "port_management_container.h"
#include "qos_monitoring_report.h"
#include "qos_notification_control_info.h"
#include "ran_nas_rel_cause.h"
#include "rat_type.h"
#include "resources_allocation_info.h"
#include "tsn_bridge_info.h"
#include "user_location.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_events_notification_s OpenAPI_events_notification_t;
typedef struct OpenAPI_events_notification_s {
    OpenAPI_access_type_e access_type;
    struct OpenAPI_acc_net_charging_address_s *an_charg_addr;
    OpenAPI_list_t *an_charg_ids;
    struct OpenAPI_an_gw_address_s *an_gw_addr;
    char *ev_subs_uri;
    OpenAPI_list_t *ev_notifs;
    OpenAPI_list_t *failed_resourc_alloc_reports;
    int no_net_loc_supp;
    OpenAPI_list_t *out_of_cred_reports;
    struct OpenAPI_plmn_id_s *plmn_id;
    OpenAPI_list_t *qnc_reports;
    OpenAPI_list_t *qos_mon_reports;
    OpenAPI_list_t *ran_nas_rel_causes;
    OpenAPI_rat_type_e rat_type;
    struct OpenAPI_user_location_s *ue_loc;
    char *ue_time_zone;
    struct OpenAPI_accumulated_usage_s *usg_rep;
    struct OpenAPI_tsn_bridge_info_s *tsn_bridge_info;
    struct OpenAPI_port_management_container_s *tsn_port_man_cont_dstt;
    OpenAPI_list_t *tsn_port_man_cont_nwtts;
} OpenAPI_events_notification_t;

OpenAPI_events_notification_t *OpenAPI_events_notification_create(
    OpenAPI_access_type_e access_type,
    OpenAPI_acc_net_charging_address_t *an_charg_addr,
    OpenAPI_list_t *an_charg_ids,
    OpenAPI_an_gw_address_t *an_gw_addr,
    char *ev_subs_uri,
    OpenAPI_list_t *ev_notifs,
    OpenAPI_list_t *failed_resourc_alloc_reports,
    int no_net_loc_supp,
    OpenAPI_list_t *out_of_cred_reports,
    OpenAPI_plmn_id_t *plmn_id,
    OpenAPI_list_t *qnc_reports,
    OpenAPI_list_t *qos_mon_reports,
    OpenAPI_list_t *ran_nas_rel_causes,
    OpenAPI_rat_type_e rat_type,
    OpenAPI_user_location_t *ue_loc,
    char *ue_time_zone,
    OpenAPI_accumulated_usage_t *usg_rep,
    OpenAPI_tsn_bridge_info_t *tsn_bridge_info,
    OpenAPI_port_management_container_t *tsn_port_man_cont_dstt,
    OpenAPI_list_t *tsn_port_man_cont_nwtts
    );
void OpenAPI_events_notification_free(OpenAPI_events_notification_t *events_notification);
OpenAPI_events_notification_t *OpenAPI_events_notification_parseFromJSON(cJSON *events_notificationJSON);
cJSON *OpenAPI_events_notification_convertToJSON(OpenAPI_events_notification_t *events_notification);
OpenAPI_events_notification_t *OpenAPI_events_notification_copy(OpenAPI_events_notification_t *dst, OpenAPI_events_notification_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_events_notification_H_ */

