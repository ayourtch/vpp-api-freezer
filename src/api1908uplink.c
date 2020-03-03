
#include <vnet/vnet.h>
#include <vnet/plugin/plugin.h>
#include <api1908compat/api1908compat.h>

#include <vlibapi/api.h>
#include <vlibmemory/api.h>
#include <vpp/app/version.h>
#include <stdbool.h>


#include <vpp/api/vpe_msg_enum.h>
#include <vpp/api/types.h>

#define vl_typedefs             /* define message structures */
#include <vpp/api/vpe_all_api_h.h>
#undef vl_typedefs
#define vl_endianfun            /* define message structures */
#include <vpp/api/vpe_all_api_h.h>
#undef vl_endianfun
/* instantiate all the print functions we know about */
#define vl_print(handle, ...) vlib_cli_output (handle, __VA_ARGS__)
#define vl_printfun
#include <vpp/api/vpe_all_api_h.h>
#undef vl_printfun
#include <vlibapi/api_helper_macros.h>


void send_compat_ping(svm_queue_t *q, u32 client_index) {
vl_api_control_ping_t *mp;
                mp = vl_msg_api_alloc (sizeof (vl_api_control_ping_t));
                clib_memset (mp, 0, sizeof (*mp));
                mp->_vl_msg_id = ntohs (VL_API_CONTROL_PING);
                mp->client_index = clib_host_to_net_u32(client_index);
                mp->context = 0x41424344;
                vl_msg_api_send_shmem (q, (u8 *) & mp);
}

void send_keepalive_reply(svm_queue_t *q, void *data) {
	vl_api_memclnt_keepalive_t *mpreq = data;
	vl_api_memclnt_keepalive_reply_t *mp;
        mp = vl_msg_api_alloc (sizeof (vl_api_memclnt_keepalive_reply_t));
        clib_memset (mp, 0, sizeof (*mp));
        mp->_vl_msg_id = ntohs (VL_API_MEMCLNT_KEEPALIVE_REPLY);
        mp->context = mpreq->context;
	mp->retval = 0;
        vl_msg_api_send_shmem (q, (u8 *) & mp);
}

void handle_upstream_message(int index, void *data) {
      // u32 len = vl_msg_api_get_msg_length(data);
      u16 msg_id = clib_net_to_host_u16(*(u16 *)data);
      api_main_t *am = apicompat_api_1908_get_1908_main();
      // clib_warning("Message id: %d, len: %d", msg_id, len);
      if (msg_id == 21) {
      	send_keepalive_reply(am->shmem_hdr->vl_input_queue, data);
      } else {
	handle_reflect_message(index, data);
      }

}

