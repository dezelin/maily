/* meta.h --- Prototypes for internally visible symbols from meta.c.
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010  Simon Josefsson
 *
 * This file is part of the Generic Security Service (GSS).
 *
 * GSS is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * GSS is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GSS; if not, see http://www.gnu.org/licenses or write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef META_H
#define META_H

#include <gss/api.h>

#define MAX_NT 5

typedef struct _gss_mech_api_struct
{
  gss_OID mech;
  const char *sasl_name;
  const char *mech_name;
  const char *mech_description;
  gss_OID name_types[MAX_NT];
    OM_uint32 (*init_sec_context)
    (OM_uint32 * minor_status,
     const gss_cred_id_t initiator_cred_handle,
     gss_ctx_id_t * context_handle,
     const gss_name_t target_name,
     const gss_OID mech_type,
     OM_uint32 req_flags,
     OM_uint32 time_req,
     const gss_channel_bindings_t input_chan_bindings,
     const gss_buffer_t input_token,
     gss_OID * actual_mech_type,
     gss_buffer_t output_token, OM_uint32 * ret_flags, OM_uint32 * time_rec);
    OM_uint32 (*canonicalize_name)
    (OM_uint32 * minor_status,
     const gss_name_t input_name,
     const gss_OID mech_type, gss_name_t * output_name);
    OM_uint32 (*export_name)
    (OM_uint32 * minor_status,
     const gss_name_t input_name, gss_buffer_t exported_name);
    OM_uint32 (*wrap)
    (OM_uint32 * minor_status,
     const gss_ctx_id_t context_handle, int conf_req_flag,
     gss_qop_t qop_req,
     const gss_buffer_t input_message_buffer,
     int *conf_state, gss_buffer_t output_message_buffer);
    OM_uint32 (*unwrap)
    (OM_uint32 * minor_status,
     const gss_ctx_id_t context_handle,
     const gss_buffer_t input_message_buffer,
     gss_buffer_t output_message_buffer, int *conf_state,
     gss_qop_t * qop_state);
    OM_uint32 (*get_mic)
    (OM_uint32 * minor_status,
     const gss_ctx_id_t context_handle,
     gss_qop_t qop_req,
     const gss_buffer_t message_buffer, gss_buffer_t message_token);
    OM_uint32 (*verify_mic)
    (OM_uint32 * minor_status,
     const gss_ctx_id_t context_handle,
     const gss_buffer_t message_buffer,
     const gss_buffer_t token_buffer, gss_qop_t * qop_state);
    OM_uint32 (*display_status)
    (OM_uint32 * minor_status,
     OM_uint32 status_value, int status_type,
     const gss_OID mech_type,
     OM_uint32 * message_context, gss_buffer_t status_string);
    OM_uint32 (*acquire_cred)
    (OM_uint32 * minor_status,
     const gss_name_t desired_name,
     OM_uint32 time_req,
     const gss_OID_set desired_mechs,
     gss_cred_usage_t cred_usage,
     gss_cred_id_t * output_cred_handle,
     gss_OID_set * actual_mechs, OM_uint32 * time_rec);
    OM_uint32 (*release_cred)
    (OM_uint32 * minor_status, gss_cred_id_t * cred_handle);
    OM_uint32 (*accept_sec_context)
    (OM_uint32 * minor_status,
     gss_ctx_id_t * context_handle,
     const gss_cred_id_t acceptor_cred_handle,
     const gss_buffer_t input_token_buffer,
     const gss_channel_bindings_t input_chan_bindings,
     gss_name_t * src_name,
     gss_OID * mech_type,
     gss_buffer_t output_token,
     OM_uint32 * ret_flags,
     OM_uint32 * time_rec, gss_cred_id_t * delegated_cred_handle);
    OM_uint32 (*delete_sec_context)
    (OM_uint32 * minor_status,
     gss_ctx_id_t * context_handle, gss_buffer_t output_token);
    OM_uint32 (*context_time)
    (OM_uint32 * minor_status,
     const gss_ctx_id_t context_handle, OM_uint32 * time_rec);
    OM_uint32 (*inquire_cred)
    (OM_uint32 * minor_status,
     const gss_cred_id_t cred_handle,
     gss_name_t * name, OM_uint32 * lifetime,
     gss_cred_usage_t * cred_usage, gss_OID_set * mechanisms);
    OM_uint32 (*inquire_cred_by_mech)
    (OM_uint32 * minor_status,
     const gss_cred_id_t cred_handle,
     const gss_OID mech_type,
     gss_name_t * name,
     OM_uint32 * initiator_lifetime,
     OM_uint32 * acceptor_lifetime, gss_cred_usage_t * cred_usage);
} _gss_mech_api_desc, *_gss_mech_api_t;

_gss_mech_api_t _gss_find_mech (const gss_OID oid);
_gss_mech_api_t _gss_find_mech_no_default (const gss_OID oid);
_gss_mech_api_t _gss_find_mech_by_saslname (const char *saslname);
OM_uint32 _gss_indicate_mechs1 (OM_uint32 * minor_status,
				gss_OID_set * mech_set);

#endif /* META_H */
