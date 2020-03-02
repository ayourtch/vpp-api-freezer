
/*
 * api1908compat.h - skeleton vpp engine plug-in header file
 *
 * Copyright (c) <current-year> <your-organization>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __included_api1908compat_h__
#define __included_api1908compat_h__

#include <vnet/vnet.h>
#include <vnet/ip/ip.h>
#include <vnet/ethernet/ethernet.h>

#include <vppinfra/hash.h>
#include <vppinfra/error.h>
#include <svm/queue.h>

void handle_upstream_message (int my_index, void *data);

typedef struct
{
  u32 my_client_index;
  svm_queue_t *vl_input_queue;
  u32 downstream_client_index;
} api1908_compat_client_t;

typedef struct
{
  /* on/off switch for the periodic function */
  u8 periodic_timer_enabled;
  /* Node index, non-zero if the periodic process has been created */
  u32 periodic_node_index;

  /* convenience */
  vlib_main_t *vlib_main;
  vnet_main_t *vnet_main;
  ethernet_main_t *ethernet_main;

  api1908_compat_client_t *up_clients;

  int signal_pending;
} api1908compat_main_t;

extern api1908compat_main_t api1908compat_main;

extern vlib_node_registration_t api1908compat_node;
extern vlib_node_registration_t api1908compat_periodic_node;

/* Periodic function events */
#define API1908COMPAT_EVENT1 1
#define API1908COMPAT_EVENT2 2
#define API1908COMPAT_EVENT_PERIODIC_ENABLE_DISABLE 3

void api1908compat_create_periodic_process (api1908compat_main_t *);

void api1908compat_send_to_client (int client_index, void * msg);
clib_error_t *api_downward_hookup_api1908compat (vlib_main_t * vm);
void handle_reflect_message (u32 index, u8 * data);

u32 get_api1908compat_upclient_index (u32 downward_index);


#endif /* __included_api1908compat_h__ */

/*
 * fd.io coding-style-patch-verification: ON
 *
 * Local Variables:
 * eval: (c-set-style "gnu")
 * End:
 */
