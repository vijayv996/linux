/* SPDX-License-Identifier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2011 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __CONFIG_DOT_H__
#define __CONFIG_DOT_H__

#define DLM_MAX_SOCKET_BUFSIZE	4096

struct dlm_config_node {
	int nodeid;
	int weight;
	int new;
	uint32_t comm_seq;
};

extern const struct rhashtable_params dlm_rhash_rsb_params;

#define DLM_MAX_ADDR_COUNT 3

#define DLM_PROTO_TCP	0
#define DLM_PROTO_SCTP	1

struct dlm_config_info {
	int ci_tcp_port;
	int ci_buffer_size;
	int ci_rsbtbl_size;
	int ci_recover_timer;
	int ci_toss_secs;
	int ci_scan_secs;
	int ci_log_debug;
	int ci_log_info;
	int ci_protocol;
	int ci_mark;
	int ci_new_rsb_count;
	int ci_recover_callbacks;
	char ci_cluster_name[DLM_LOCKSPACE_LEN];
};

extern struct dlm_config_info dlm_config;

int dlm_config_init(void);
void dlm_config_exit(void);
int dlm_config_nodes(char *lsname, struct dlm_config_node **nodes_out,
		     int *count_out);
int dlm_comm_seq(int nodeid, uint32_t *seq);
int dlm_our_nodeid(void);
int dlm_our_addr(struct sockaddr_storage *addr, int num);

#endif				/* __CONFIG_DOT_H__ */

