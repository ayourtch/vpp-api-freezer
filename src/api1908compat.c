/*
 * api1908compat.c - skeleton vpp engine plug-in
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

#include <vnet/vnet.h>
#include <vnet/plugin/plugin.h>
#include <api1908compat/api1908compat.h>

#include <vlibapi/api.h>
#include <vlibmemory/api.h>
#include <vpp/app/version.h>
#include <stdbool.h>

#include <vlibmemory/socket_client.h>

#include <vlibmemory/vl_memory_msg_enum.h>

#define vl_typedefs		/* define message structures */
#include <vlibmemory/vl_memory_api_h.h>
#undef vl_typedefs

#define vl_endianfun		/* define message structures */
#include <vlibmemory/vl_memory_api_h.h>
#undef vl_endianfun

/* instantiate all the print functions we know about */
#define vl_print(handle, ...) clib_warning (__VA_ARGS__)
#define vl_printfun
#include <vlibmemory/vl_memory_api_h.h>
#undef vl_printfun

#include "src_1908/vlibmemory_1908/memory_api.h"
#include "src_1908/vlibapi_1908/api_helper_macros.h"
#include "src_1908/vpp_1908/api/vpe_msg_enum.h"


vpe_api_1908_main_t vpe_api_1908_main;

api1908compat_main_t api1908compat_main;

/* List of message types that this plugin understands */

#define foreach_api1908compat_plugin_api_msg                           \
_(API1908COMPAT_ENABLE_DISABLE, api1908compat_enable_disable)

/* Action function shared between message handler and debug CLI */

int
api1908compat_enable_disable (api1908compat_main_t * amp, u32 sw_if_index,
			      int enable_disable)
{
  vnet_sw_interface_t *sw;
  int rv = 0;

  /* Utterly wrong? */
  if (pool_is_free_index (amp->vnet_main->interface_main.sw_interfaces,
			  sw_if_index))
    return VNET_API_ERROR_INVALID_SW_IF_INDEX;

  /* Not a physical port? */
  sw = vnet_get_sw_interface (amp->vnet_main, sw_if_index);
  if (sw->type != VNET_SW_INTERFACE_TYPE_HARDWARE)
    return VNET_API_ERROR_INVALID_SW_IF_INDEX;

  api1908compat_create_periodic_process (amp);

  vnet_feature_enable_disable ("device-input", "api1908compat",
			       sw_if_index, enable_disable, 0, 0);

  /* Send an event to enable/disable the periodic scanner process */
  vlib_process_signal_event (amp->vlib_main,
			     amp->periodic_node_index,
			     API1908COMPAT_EVENT_PERIODIC_ENABLE_DISABLE,
			     (uword) enable_disable);
  return rv;
}



typedef struct
{
  u8 *name;
  u32 value;
} name_sort_t;

static int
value_sort_cmp (void *a1, void *a2)
{
  name_sort_t *n1 = a1;
  name_sort_t *n2 = a2;

  if (n1->value < n2->value)
    return -1;
  if (n1->value > n2->value)
    return 1;
  return 0;
}

api_1908_main_t *apicompat_api_1908_get_main() {
	return &api_1908_main;
}


static clib_error_t *
api1908_dump_table_command_fn (vlib_main_t * vm,
			       unformat_input_t * input,
			       vlib_cli_command_t * cmd)
{
  api_1908_main_t *am = apicompat_api_1908_get_main();
  name_sort_t *nses = 0, *ns;
  hash_pair_t *hp;
  int i;

  /* *INDENT-OFF* */
  hash_foreach_pair (hp, am->msg_index_by_name_and_crc,
  ({
    vec_add2 (nses, ns, 1);
    ns->name = (u8 *)(hp->key);
    ns->value = (u32) hp->value[0];
  }));
  /* *INDENT-ON* */

  vec_sort_with_function (nses, value_sort_cmp);

  for (i = 0; i < vec_len (nses); i++)
    vlib_cli_output (vm, " [%d]: %s", nses[i].value, nses[i].name);
  vec_free (nses);
  return 0;
}

static clib_error_t *
api1908_uplink_dump_table_command_fn (vlib_main_t * vm,
				      unformat_input_t * input,
				      vlib_cli_command_t * cmd)
{
  api_main_t *am = apicompat_api_1908_get_main();
  name_sort_t *nses = 0, *ns;
  hash_pair_t *hp;
  int i;

  /* *INDENT-OFF* */
  hash_foreach_pair (hp, am->msg_index_by_name_and_crc,
  ({
    vec_add2 (nses, ns, 1);
    ns->name = (u8 *)(hp->key);
    ns->value = (u32) hp->value[0];
  }));
  /* *INDENT-ON* */

  vec_sort_with_function (nses, value_sort_cmp);

  for (i = 0; i < vec_len (nses); i++)
    vlib_cli_output (vm, " [%d]: %s", nses[i].value, nses[i].name);
  vec_free (nses);
  return 0;
}


static clib_error_t *
api1908compat_enable_disable_command_fn (vlib_main_t * vm,
					 unformat_input_t * input,
					 vlib_cli_command_t * cmd)
{
  int enable_disable = 0;

  while (unformat_check_input (input) != UNFORMAT_END_OF_INPUT)
    {
      if (unformat (input, "disable"))
	enable_disable = 1;
      else
	break;
    }

  vl_1908_mem_api_enable_disable (vm, !enable_disable);

  return 0;
}

/* *INDENT-OFF* */
VLIB_CLI_COMMAND (api1908compat_enable_disable_command, static) =
{
  .path = "api1908compat",
  .short_help =
  "api1908compat [disable]",
  .function = api1908compat_enable_disable_command_fn,
};

VLIB_CLI_COMMAND (api1908_dump_table_command, static) =
{
  .path = "show api 1908 table-dump",
  .short_help =
  "show api 1908 table-dump",
  .function = api1908_dump_table_command_fn,
};

VLIB_CLI_COMMAND (api1908_uplink_dump_table_command, static) =
{
  .path = "show api table-dump",
  .short_help =
  "show api table-dump",
  .function = api1908_uplink_dump_table_command_fn,
};


clib_error_t *vpe_api_1908_init(vlib_main_t *vm);
clib_error_t *map_api_1908_segment_init(vlib_main_t *vm);
clib_error_t *vlibmemory_1908_init(vlib_main_t *vm);


void (*queue_signal_callback_old) (struct vlib_main_t *);
void (*queue_signal_callback_new) (struct vlib_main_t *);

char *svm_name = "/vpe-api";


u8 *data = 0;

static uword
vl_api_reply_process (vlib_main_t * vm, vlib_node_runtime_t * node,
		     vlib_frame_t * f)
{
  // svm_queue_t *q;
  f64 sleep_time, start_time;
  f64 vector_rate;
  uword event_type;
  uword *event_data = 0;
  api1908compat_main_t *amp = &api1908compat_main;

  // f64 now;

  // q = compat_main.vl_input_queue;

  sleep_time = 1.0;

  /* $$$ pay attention to frame size, control CPU usage */
  while (1)
    {
      vector_rate = (f64) vlib_last_vectors_per_main_loop (vm);
      start_time = vlib_time_now (vm);
      while (1)
	{
		api1908_compat_client_t *up_client;
	        sleep_time = 1.0;
		vec_foreach(up_client, amp->up_clients) {
        		int qstatus = svm_queue_sub (up_client->vl_input_queue, (u8 *) & data,
				   SVM_Q_NOWAIT, 0);
			if (qstatus == 0) {
				// clib_warning("Read some bytes:\n%U", format_hex_bytes, data, 64);
				handle_upstream_message(up_client - amp->up_clients, data);
				sleep_time = 0.0;
			}
		}
		if (sleep_time == 1.0) {
			break;
		}

	  /* Allow no more than 10us without a pause */
	  if (vlib_time_now (vm) > start_time + 10e-6)
	    {
	      int index = SLEEP_400_US;
	      if (vector_rate > 40.0)
		sleep_time = 400e-6;
	      else if (vector_rate > 20.0)
		{
		  index = SLEEP_200_US;
		  sleep_time = 200e-6;
		}
	      else if (vector_rate >= 1.0)
		{
		  index = SLEEP_100_US;
		  sleep_time = 100e-6;
		}
	      else
		{
		  index = SLEEP_10_US;
		  sleep_time = 10e-6;
		}
	      vector_rate_histogram[index] += 1;
	      break;
	    }
	}

      vlib_process_wait_for_event_or_clock (vm, sleep_time);
      if (sleep_time > 0.5) {
	      // send_compat_ping(compat_main.vl_input_queue, compat_main.my_client_index);
	      // send_compat_ping(api_main.shmem_hdr->vl_input_queue, compat_main.my_client_index);
      }
      vec_reset_length (event_data);
      event_type = vlib_process_get_events (vm, &event_data);
      // now = vlib_time_now (vm);
      amp->signal_pending = 0;
      switch (event_type)
	{
	case -1:
	  break;
	case 1:
	  break;

	default:
	  clib_warning ("unknown event type %d", event_type);
	  break;
	}

    }

  return 0;
}
/* *INDENT-OFF* */
VLIB_REGISTER_NODE (vl_1908_api_reply_node) =
{
  .function = vl_api_reply_process,
  .type = VLIB_NODE_TYPE_PROCESS,
  .name = "api-1908-reply-handler",
  .state = VLIB_NODE_STATE_DISABLED,
};
/* *INDENT-ON* */

static void
combo_queue_signal_callback (vlib_main_t * vm)
{
  api1908compat_main_t *amp = &api1908compat_main;

  queue_signal_callback_old (vm);
  queue_signal_callback_new (vm);

  int send_signal = 0;

  api1908_compat_client_t *up_client;
  vec_foreach (up_client, amp->up_clients)
  {
    if (up_client->vl_input_queue->cursize > 0)
      {
	send_signal = 1;
      }
  }
  if (send_signal)
    {
      amp->signal_pending = 1;

      vlib_process_signal_event (vm, vl_1908_api_reply_node.index,
				 /* event_type */ QUEUE_SIGNAL_EVENT,
				 /* event_data */ 0);
    }

}

void
vl_reply_handler_enable_disable (vlib_main_t * vm, int enable)
{
  vlib_node_set_state (vm, vl_1908_api_reply_node.index,
		       (enable
			? VLIB_NODE_STATE_POLLING
			: VLIB_NODE_STATE_DISABLED));
}


void vl_msg_api_send_shmem (svm_queue_t * q, u8 * elem);
int
my_vl_client_connect (vlib_main_t * vm, const char *name, int ctx_quota,
		      int input_queue_size)
{
  svm_region_t *svm;
  vl_api_memclnt_create_t *mp;
  vl_api_memclnt_create_reply_t *rp;
  svm_queue_t *vl_input_queue;
  vl_shmem_hdr_t *shmem_hdr;
  int rv = 0;
  void *oldheap;
  api_main_t *am = apicompat_api_1908_get_main();
  api1908compat_main_t *amp = &api1908compat_main;

  api1908_compat_client_t myclient;


  if (am->my_registration)
    {
      clib_warning ("client %s already connected...", name);
      return -1;
    }

  if (am->vlib_rp == 0)
    {
      clib_warning ("am->vlib_rp NULL");
      return -1;
    }

  svm = am->vlib_rp;
  shmem_hdr = am->shmem_hdr;

  if (shmem_hdr == 0 || shmem_hdr->vl_input_queue == 0)
    {
      clib_warning ("shmem_hdr / input queue NULL");
      return -1;
    }

  pthread_mutex_lock (&svm->mutex);
  oldheap = svm_push_data_heap (svm);
  vl_input_queue = svm_queue_alloc_and_init (input_queue_size, sizeof (uword),
					     getpid ());
  svm_pop_heap (oldheap);
  pthread_mutex_unlock (&svm->mutex);

  myclient.my_client_index = ~0;
  // vam->my_registration = 0;
  myclient.vl_input_queue = vl_input_queue;

  mp = vl_msg_api_alloc (sizeof (vl_api_memclnt_create_t));
  clib_memset (mp, 0, sizeof (*mp));
  mp->_vl_msg_id = ntohs (VL_API_MEMCLNT_CREATE);
  mp->ctx_quota = ctx_quota;
  mp->input_queue = (uword) vl_input_queue;
  strncpy ((char *) mp->name, name, sizeof (mp->name) - 1);

  vl_msg_api_send_shmem (shmem_hdr->vl_input_queue, (u8 *) & mp);

  while (1)
    {
      int qstatus;
      int i;

      /* Wait up to 10 seconds */
      for (i = 0; i < 1000; i++)
	{
	  qstatus = svm_queue_sub (vl_input_queue, (u8 *) & rp,
				   SVM_Q_NOWAIT, 0);
	  clib_warning ("qstatus: %d", qstatus);
	  if (qstatus == 0)
	    goto read_one_msg;
	  vlib_process_wait_for_event_or_clock (vm, 0.01);
	}
      /* Timeout... */
      clib_warning ("memclnt_create_reply timeout");
      return -1;

    read_one_msg:
      if (ntohs (rp->_vl_msg_id) != VL_API_MEMCLNT_CREATE_REPLY)
	{
	  clib_warning ("unexpected reply: id %d", ntohs (rp->_vl_msg_id));
	  continue;
	}
      rv = clib_net_to_host_u32 (rp->response);
      if (rv == 0)
	{
	  myclient.my_client_index = rp->index;
	  //   am->my_registration = (vl_api_registration_t *) (uword) mp->handle;
	  vec_add1 (amp->up_clients, myclient);
	}

      // vl_msg_api_handler ((void *) rp);
      break;
    }
  return (rv);
}


int
connect_to_vpe (vlib_main_t * vm, char *name)
{
  if (my_vl_client_connect (vm, name, 0, 32) < 0)
    return 0;

  return 0;
}

u32
get_api1908compat_upclient_index (u32 downclient_index)
{
  api1908compat_main_t *amp = &api1908compat_main;
  api1908_compat_client_t *upclient;

  vec_foreach (upclient, amp->up_clients)
  {
    if (upclient->downstream_client_index == downclient_index)
      {
	return upclient->my_client_index;
      }
  }
  connect_to_vpe (amp->vlib_main, "api1908compat");
  upclient =
    vec_elt_at_index (amp->up_clients, vec_len (amp->up_clients) - 1);
  upclient->downstream_client_index = downclient_index;
  return upclient->my_client_index;
}

extern void api1908_compat_autosource_test (void);

clib_error_t *api_hookup_api1908compat (vlib_main_t * vm);

static clib_error_t *
api1908compat_init (vlib_main_t * vm)
{
  api1908compat_main_t *amp = &api1908compat_main;
  clib_error_t *error = 0;

  amp->vlib_main = vm;
  amp->vnet_main = vnet_get_main ();
  amp->up_clients = 0;

  /* capture the old queue signal callback */
  queue_signal_callback_old = vm->queue_signal_callback;

  error = vpe_api_1908_init (vm);
  if (error == 0)
    {
      error = vlibmemory_1908_init (vm);
    }
  if (error == 0)
    {
      error = map_api_1908_segment_init (vm);
    }

  /* the new handler has surely installed the queue signal CB */
  queue_signal_callback_new = vm->queue_signal_callback;

  /* install ours that will call both */
  vm->queue_signal_callback = combo_queue_signal_callback;


  api_hookup_api1908compat (vm);
  api_downward_hookup_api1908compat (vm);
  vl_reply_handler_enable_disable (vm, 1);
  /* Set up the plugin message ID allocator right now... */
  vl_1908_msg_api_set_first_available_msg_id (VL_1908_MSG_FIRST_AVAILABLE);


  return error;
}

VLIB_INIT_FUNCTION (api1908compat_init) =
{
  // .runs_after = VLIB_INITS("avf_init"),
};

extern void api_hookup_plugins_api (vlib_main_t * vm);


static clib_error_t *
api_1908_compat_config_fn (vlib_main_t * vm, unformat_input_t * input)
{

  vl_api_msg_range_t *r;
  //connect_to_vpe (vm, "1908-compat-client");
  api_main_t *am = apicompat_api_1908_get_main();

  api1908_compat_autosource_test ();
  clib_warning ("API1908COMPAT uplink msg ranges: %d",
		vec_len (am->msg_ranges));

  vec_foreach (r, api_main->msg_ranges)
  {
    clib_warning ("'%s' %d-%d", r->name, r->first_msg_id, r->last_msg_id);
  }
  api_hookup_plugins_api (vm);
  // api_plugins_hookup_api1908compat(vm);
  return 0;
}

VLIB_CONFIG_FUNCTION (api_1908_compat_config_fn, "api1908compat");



/* *INDENT-OFF* */
VLIB_PLUGIN_REGISTER () =
{
  .version = VPP_BUILD_VER,
  .description = "19.08 API compatibility layer",
//  .default_disabled = 1,

};
/* *INDENT-ON* */

/******** downward handlers - reflect the messages arriving on the client end 
 * of our current-api connection, into the 1908 server end.
 */

typedef struct
{
  /** Message handler vector  */
  void (**msg_handlers) (u32, void *);
} api_reflect_main_t;

api_reflect_main_t api_reflect_main;



void
handle_reflect_message (u32 index, u8 * data)
{
  // u32 len = vl_msg_api_get_msg_length(data);
  u16 msg_id = clib_net_to_host_u16 (*(u16 *) data);

  api_reflect_main_t *arm = &api_reflect_main;
  if (msg_id < vec_len (arm->msg_handlers))
    {
      if (*vec_elt_at_index (arm->msg_handlers, msg_id))
	(*vec_elt_at_index (arm->msg_handlers, msg_id)) (index, data);
      else
	clib_warning ("No reflect handler for msg %d", msg_id);
    }
  else
    clib_warning ("No reflect handler for msg %d", msg_id);
}

void
vl_reflect_api_set_handlers (int id, void *handler)
{
  api_reflect_main_t *arm = &api_reflect_main;
  vec_validate (arm->msg_handlers, id);
  *vec_elt_at_index (arm->msg_handlers, id) = handler;
}




/*
 * fd.io coding-style-patch-verification: ON
 *
 * Local Variables:
 * eval: (c-set-style "gnu")
 * End:
 */
