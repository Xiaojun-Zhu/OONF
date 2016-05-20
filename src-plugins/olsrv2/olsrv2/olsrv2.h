
/*
 * The olsr.org Optimized Link-State Routing daemon version 2 (olsrd2)
 * Copyright (c) 2004-2015, the olsr.org team - see HISTORY file
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of olsr.org, olsrd nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Visit http://www.olsr.org for more information.
 *
 * If you find this software useful feel free to make a donation
 * to the project. For more information see the website or contact
 * the copyright holders.
 *
 */

/**
 * @file
 */

#ifndef OLSRV2_H_
#define OLSRV2_H_

#include "common/common_types.h"
#include "common/netaddr.h"
#include "common/netaddr_acl.h"
#include "core/oonf_subsystem.h"

#include "nhdp/nhdp_domain.h"

/*! subsystem identifier */
#define OONF_OLSRV2_SUBSYSTEM "olsrv2"

/*! configuration section for OLSRv2 */
#define CFG_OLSRV2_SECTION OONF_OLSRV2_SUBSYSTEM

/*! routable IPv4 addresses (default configuration) */
#define OLSRV2_ROUTABLE_IPV4 "-169.254.0.0/16\0-127.0.0.0/8\0-224.0.0.0/12\0"

/*! routable IPv6 addresses (default configuration) */
#define OLSRV2_ROUTABLE_IPV6 "-fe80::/10\0-::1\0-ff00::/8\0"

/*! default IPv4 originator addresses */
#define OLSRV2_ORIGINATOR_IPV4 "-127.0.0.0/8\0-224.0.0.0/12\0"

/*! default IPv6 originator addresses */
#define OLSRV2_ORIGINATOR_IPV6 "-::1\0-ff00::/8\0"

/**
 * Creates a cfg_schema_entry for a locally attached network
 * @param p_name parameter name
 * @param p_def parameter default value
 * @param p_help help text for configuration entry
 * @param args variable list of additional arguments
 */
#define CFG_VALIDATE_LAN(p_name, p_def, p_help, args...)         _CFG_VALIDATE(p_name, p_def, p_help, .cb_validate = olsrv2_validate_lan, .validate_param = {{.i8 = {AF_INET, AF_INET6, -1,-1, -1}}, {.b = true}}, ##args )

EXPORT uint64_t olsrv2_get_tc_interval(void);
EXPORT uint64_t olsrv2_get_tc_validity(void);
EXPORT bool olsrv2_is_nhdp_routable(struct netaddr *addr);
EXPORT bool olsrv2_is_routable(struct netaddr *addr);
EXPORT bool olsrv2_mpr_shall_process(
    struct rfc5444_reader_tlvblock_context *, uint64_t vtime);
EXPORT bool olsrv2_mpr_shall_forwarding(
    struct rfc5444_reader_tlvblock_context *context,
    struct netaddr *source_address, uint64_t vtime);
EXPORT uint16_t olsrv2_get_ansn(void);
EXPORT uint16_t olsrv2_update_ansn(void);
EXPORT int olsrv2_validate_lan(const struct cfg_schema_entry *entry,
    const char *section_name, const char *value, struct autobuf *out);

/**
 * @return validity time of former originator IDs
 */
static INLINE uint64_t
olsrv2_get_old_originator_validity(void) {
  return olsrv2_get_tc_validity() * 2;
}

#endif /* OLSRV2_H_ */
