
/* made on date: Fri Feb 28 14:30:22 UTC 2020 */
// #error Autosource: Fri Feb 28 14:30:22 UTC 2020


#include <vnet/vnet.h>
#include <vnet/plugin/plugin.h>
#include <api1908compat/api1908compat.h>

#include <vlibapi/api.h>
#include <vlibmemory/api.h>
#include <vpp/app/version.h>
#include <stdbool.h>

#include "src_1908/vlibapi_1908/api.h"

#include <vlibmemory/socket_client.h>

// downward apis
#include "api1908compat.h"

#include <vpp/api/vpe_msg_enum.h>

#define vl_typedefs
#include <vlibapi/api_types.h>
#include "all-headers-curr.h"
#include "plugin-headers-curr.h"

#include "src_1908/vlibapi_1908/api_types.h"
#include "all-headers-1908.h"
#include "plugin-headers-1908.h"
#undef vl_typedefs

#include "src_1908/vlibapi_1908/api_common.h"
#include "src_1908/vlibmemory_1908/memory_shared.h"

#include <vlibmemory/api.h>

// upward apis

#include "src_1908/vpp_1908/api/vpe_msg_enum.h"

// print handlers

#define vl_print(handle, ...) vlib_cli_output(handle, __VA_ARGS__)
#define vl_printfun
#include "src_1908/vnet_1908/vnet_all_api_h.h"
#include "src_1908/vpp_1908/api/vpe.api.h"
#undef vl_printfun
#include "src_1908/noop_print_handlers.h"


/* #inclide "all-headers-1908.h" */



void
api1908_compat_autosource_test (void)
{
  clib_warning ("Auto source was generated on Fri Feb 28 14:30:22 UTC 2020");
}

/*
 * "send new" handlers - their CRC changes automatically together with the master.
 * the vl_1908_api handlers reference hardcoded CRC of the original 1908 API.
 * If the CRC changes, then one will need to manually create a
 * "send_new_msgname_1908crc_handler" which would allocate
 * a copy of the new message, and then call the
 * new automatically generated handler with do_copy=0 to avoid extraneous alloc

if the new message is not being used, then the unused error needs to be suppressed like this:

#define send_new_new_ay_message_reply_e8d4e804_handler(...) __attribute__ ((unused)) send_new_new_ay_message_reply_e8d4e804_handler(__VA_ARGS__)
#define send_new_new_ay_message_51077d14_handler(...) __attribute__ ((unused)) send_new_new_ay_message_51077d14_handler(__VA_ARGS__)



 */
#define vl_msg_name_crc_list

#define _(a_id,a_msg,a_crc) \
        __attribute__ ((unused)) \
        static inline void send_new_ ## a_msg ## _ ## a_crc ## _handler(void *mp0, int do_copy) { \
                api_main_t *am = apicompat_api_1908_get_main(); \
                void *mp = mp0; \
                if (do_copy) { \
                  u32 len = vl_msg_api_get_msg_length(mp0); \
                  mp = vl_msg_api_alloc (len); \
                  clib_memcpy (mp, mp0, len); \
                } \
                svm_queue_t *q = am->shmem_hdr->vl_input_queue; \
                vl_msg_api_send_shmem (q, (u8 *) & mp); \
        }  \

#include "all-headers-curr.h"
#include "plugin-headers-curr.h"
#undef _
#undef vl_msg_name_crc_list

/* FIXME: needs a proper client translation */
static u32 last_client_index = 0;

extern void vl_reflect_api_set_handlers (int id, void *handler);


/* https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms */

/* Exceptions: the messages which do not have mp->context in them */


#define EXCEPTION_sw_interface_event DEFAULT_EXCEPTION
#define EXCEPTION_l2_macs_event DEFAULT_EXCEPTION
#define EXCEPTION_dhcp_compl_event DEFAULT_EXCEPTION
#define EXCEPTION_dhcp6_reply_event DEFAULT_EXCEPTION
#define EXCEPTION_dhcp6_pd_reply_event DEFAULT_EXCEPTION
#define EXCEPTION_ip4_arp_event DEFAULT_EXCEPTION
#define EXCEPTION_ip6_nd_event DEFAULT_EXCEPTION
#define EXCEPTION_ip6_ra_event DEFAULT_EXCEPTION

#define EXCEPTION_igmp_event DEFAULT_EXCEPTION
#define EXCEPTION_nat_ha_resync_completed_event DEFAULT_EXCEPTION


/* message ID conversions */

#define vl_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
	enum { MSG_ID_CURR_FOR_ ## a_msg = a_id };
#include "all-headers-curr.h"
#undef _
#undef vl_msg_name_crc_list

#define vl_1908_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
	enum { MSG_ID_1908_FOR_ ## a_msg = a_id };
#include "all-headers-1908.h"
#undef _
#undef vl_1908_msg_name_crc_list

/* plugin messages. They are not constants, because they can change depending on plugins loaded */

#define vl_compat_api_version(name, crc) \
        static u16 name## _curr_base_msg_id = 0;
#define vl_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
	static u16 CLIB_UNUSED(MSG_ID_CURR_FOR_ ## a_msg) = 0;
#include "plugin-headers-curr.h"
#undef _
#undef vl_msg_name_crc_list
#undef vl_compat_api_version

#define vl_1908_compat_api_version(name, crc) \
        static u16 name ##_1908_base_msg_id = 0;
#define vl_1908_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
	static u16 CLIB_UNUSED(MSG_ID_1908_FOR_ ## a_msg) = 0;
#include "plugin-headers-1908.h"
#undef _
#undef vl_1908_msg_name_crc_list
#undef vl_1908_compat_api_version



//char *compat1908_auto_source_version = __DATE__ __TIME__;

/*
 * "send_old" handlers - these handlers contain the message name and
 * the CRC from 1908 API, and do a no-op sending of the argument,
 * possibly with copy, to the 1908 API side.
 *
		  clib_warning("HEAP: %p, msg: %p, omsg: %p", am->vlib_rp, mp, mp0); \
	          api_1908_main_t *am = apicompat_api_1908_get_1908_main(); \
	          pthread_mutex_lock (&am->vlib_rp->mutex); \
	          void *oldheap = svm_push_data_heap (am->vlib_rp); \
	          svm_pop_heap (oldheap); \
	          pthread_mutex_unlock (&am->vlib_rp->mutex); \

 */


/*
 * "vl_1908_api" handlers - their job in life is simply to redirect the calls to
 * "send_new_msgname_1908crc_handler" function, with do_copy=1.
 */

#include "handler-old-to-new.h"

#define vl_1908_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
	static void vl_1908_api_ ## a_msg ## _ ## a_crc ## _handler(vl_1908_api_ ## a_msg ## _t *om) { \
		/* clib_warning("OLD " #a_msg "_" #a_crc " called"); */ \
		char *e = strrchr(#a_msg, '_'); \
                CLIB_UNUSED (vl_1908_api_control_ping_reply_t * mp1) = (void *)om; \
		mp1->_vl_1908_msg_id = clib_net_to_host_u16(MSG_ID_CURR_FOR_ ## a_msg); \
		if (e && strcmp(e, "_reply") && strcmp(e, "_details")) {\
			vl_1908_api_control_ping_t *pm = (void *)om; \
			/* FIXME */ \
			last_client_index = pm->client_index; \
			pm->client_index = get_api1908compat_upclient_index(pm->client_index); \
		} \
		send_new_ ## a_msg ## _ ## a_crc ## _handler(om, 1); \
	}  \

#include "all-headers-1908.h"
#include "plugin-headers-1908.h"
#undef _
#undef vl_1908_msg_name_crc_list

#define vl_1908_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
	static void vl_1908_api_ ## a_msg ## _ ## a_crc ## _t_print_handler(vl_1908_api_ ## a_msg ## _t *om) { \
		CLIB_UNUSED (vlib_main_t * vm) = vlib_get_main (); \
		/* FIXME vl_1908_api_ ## a_msg ## _t_print(om, vm); */ \
	}  \

#include "all-headers-1908.h"
#undef _
#undef vl_1908_msg_name_crc_list

clib_error_t *
api_hookup_api1908compat (vlib_main_t * vm)
{
  api_1908_main_t *am = apicompat_api_1908_get_1908_main();
#define vl_1908_msg_name_crc_list
#define _(N,A_MSG, A_CRC)                                                  \
    vl_1908_msg_api_set_handlers(N, (#A_MSG),                     \
                           vl_1908_api_## A_MSG ##_ ## A_CRC ## _handler,              \
                           vl_1908_noop_handler,                     \
                           vl_1908_noop_handler,                     \
                           vl_1908_api_##A_MSG## _ ## A_CRC ## _t_print_handler,                \
                           sizeof(vl_1908_api_## A_MSG ##_t), 1 /* trace */); \
	vl_1908_msg_api_add_msg_name_crc(am, #A_MSG "_" #A_CRC, N); \

#include "all-headers-1908.h"
#undef _
#undef vl_1908_msg_name_crc_list

  return 0;
}

clib_error_t *
api_hookup_plugins_api1908compat (vlib_main_t * vm)
{

  return 0;
}

/**** plugins ***/


#define vl_1908_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
        static void inline send_old_ ## a_msg ## _ ## a_crc ## _handler(u32 index, void *mp0, int do_copy) { \
		api1908compat_main_t *amp = &api1908compat_main; \
		api1908_compat_client_t *ucp = vec_elt_at_index(amp->up_clients, index); \
                void *mp = mp0; \
                if (do_copy) { \
                  u32 len = vl_1908_msg_api_get_msg_length(mp0); \
                  mp = vl_1908_msg_api_alloc (len); \
                  clib_memcpy (mp, mp0, len); \
                } \
                /* CLIB_UNUSED(vl_api_ ## a_msg ## _t *mp2_curr) = mp; */ \
                CLIB_UNUSED(vl_1908_api_ ## a_msg ## _t *mp2) = mp; \
                mp2->_vl_1908_msg_id = clib_net_to_host_u16(MSG_ID_1908_FOR_ ## a_msg); \
		u32 client_index = ucp->downstream_client_index; \
                api1908compat_send_to_client(client_index, (u8 *) mp); \
        };  \

#include "all-headers-1908.h"
#include "plugin-headers-1908.h"
#undef _
#undef vl_1908_msg_name_crc_list




/*
 * "vl_reflect_api" handlers: they are merely used to reflect the messages received
 * from the master side to 1908 API side, possibly with adaptation. If the initial
 * 1908 CRC changes, this causes the error requiring to define
 * "send_old_messagename_mastercrc_handler" function, which will allocate
 * the modified reply, and then call the "send_old_messagename_1908crc_handler" with
 * do_copy = 0 and this argument.
 */

#include "handler-new-to-old.h"

#define vl_1908_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
        \
	__attribute__ ((unused)) \
        static void \
        vl_reflect_api_ ## a_msg ## _ ## a_crc ## _handler(u32 index, void *om) { \
                /* clib_warning("REFLECT " #a_msg "_" #a_crc " called"); */ \
                send_old_ ## a_msg ## _ ## a_crc ## _handler(index, om, 1); \
		vl_msg_api_free(om); \
        };  \
        \

#include "all-headers-1908.h"
#include "plugin-headers-1908.h"
#undef _
#undef vl_1908_msg_name_crc_list

#include "custom-codegen.h"
/* this is a bit involved...
 * we define the macro that returns the #define corresponding to the 19.08 version of the message,
 * and check if it is define (empty) or not defined (nonempty).
 * the CCG_TEST_EMPTY_CB2 then calls back one of the two callbacks, passing through the arguments.
 * thus either triggering the registration or not.
 */

#define CCG_1908_SYM(x) _vl_1908_api_defined_ ## x
#define CCG_EA(a_msg, a_handler) vl_reflect_api_set_handlers(MSG_ID_CURR_FOR_ ## a_msg, a_handler);
#define CCG_NEA(a_msg, a_handler)
#define TEST_IF_EMPTY(a_msg, a_handler) CCG_TEST_EMPTY_CB2(CCG_1908_SYM(a_msg), CCG_EA, CCG_NEA, a_msg, a_handler)

#define vl_compat_api_version(name, crc) \
        static void inline api_try_hookup_api_ ## name ## _plugin_curr(vlib_main_t * vm) {   \
              CLIB_UNUSED(api_main_t *am) = apicompat_api_1908_get_main(); \
              CLIB_UNUSED(u16 this_msg_number) = name ## _curr_base_msg_id; \
                if (this_msg_number == 0 || this_msg_number == 65535) { return ; } \

#define vl_msg_name_crc_list
#define _(N,A_MSG, A_CRC)                                                  \
    MSG_ID_CURR_FOR_ ##A_MSG = this_msg_number++; \
    TEST_IF_EMPTY(A_MSG , vl_reflect_api_## A_MSG ##_ ## A_CRC ## _handler);\

#define vl_compat_api_version_trailer(name, crc) \
        }

#include "plugin-headers-curr.h"
#undef CCG_EA
#undef CCG_NEA
#undef CCG_1908_SYM
#undef TEST_IF_EMPTY

#undef vl_compat_api_version
#undef vl_compat_api_version_trailer
#undef _
#undef vl_msg_name_crc_list

static void
api_hookup_plugins_api_curr (vlib_main_t * vm)
{
#define vl_compat_api_version(name, crc)     api_try_hookup_api_ ## name ## _plugin_curr(vm);
#include "plugin-headers-curr.h"
#undef vl_compat_api_version
}



clib_error_t *
api_downward_hookup_api1908compat (vlib_main_t * vm)
{

#define vl_msg_name_crc_list
#define _(N,A_MSG, A_CRC)                                                  \
    vl_reflect_api_set_handlers(N, vl_reflect_api_## A_MSG ##_ ## A_CRC ## _handler);
#include "all-headers-curr.h"
#undef _
#undef vl_msg_name_crc_list

  return 0;
}

clib_error_t *
api_downward_hookup_plugins_api1908compat (vlib_main_t * vm)
{

  return 0;
}

/**** upward direction ******/

/* get the first message id */
#define vl_compat_api_version(name, crc) \
    static void api_try_get_api_first_msg_ ## name ## _plugin_curr(vlib_main_t * vm) { \
                u8 * full_name = format (0, #name "_%08x%c", crc, 0); \
                u16 first_id = vl_client_get_first_plugin_msg_id((void *)full_name); \
                clib_warning("First message for %s: %d", full_name, first_id); \
                vec_free(full_name); \
                name ## _curr_base_msg_id = first_id; \
    }
#include "plugin-headers-curr.h"
#undef vl_compat_api_version

static void
api_try_get_api_first_msg_plugins_curr (vlib_main_t * vm)
{
#define vl_compat_api_version(name, crc) \
    api_try_get_api_first_msg_ ## name ## _plugin_curr(vm);
#include "plugin-headers-curr.h"
#undef vl_compat_api_version
}



/**** old ***/
__attribute__ ((unused))
     static void try_register_message_1908 (char *msg)
{
}

#define vl_1908_compat_api_version(name, crc) \
        void api_try_hookup_api_ ## name ## _plugin_1908(vlib_main_t * vm) {   \
              CLIB_UNUSED(api_1908_main_t *am) = apicompat_api_1908_get_1908_main(); \
              CLIB_UNUSED(u16 this_msg_number) = name ## _1908_base_msg_id; \
                if (this_msg_number == 0 || this_msg_number == 65535) { return ; } \

#define vl_1908_msg_name_crc_list
#define _(N,A_MSG, A_CRC)                                                  \
    MSG_ID_1908_FOR_ ##A_MSG = this_msg_number++; \
    vl_1908_msg_api_set_handlers(MSG_ID_1908_FOR_ ##A_MSG, (#A_MSG),                     \
                           vl_1908_api_## A_MSG ##_ ## A_CRC ## _handler,              \
                           vl_1908_noop_handler,                     \
                           vl_1908_noop_handler,                     \
                           vl_1908_noop_handler,  /* FIXME PRINTING */              \
                           sizeof(vl_1908_api_## A_MSG ##_t), 1 /* trace */); \
    vl_1908_msg_api_add_msg_name_crc(am, #A_MSG "_" #A_CRC, MSG_ID_1908_FOR_ ##A_MSG); \


#define vl_1908_compat_api_version_trailer(name, crc) \
        }

#include "plugin-headers-1908.h"
#undef vl_1908_compat_api_version
#undef vl_1908_compat_api_version_trailer
#undef _
#undef vl_1908_msg_name_crc_list

static void
api_hookup_plugins_api_1908 (vlib_main_t * vm)
{

#define vl_1908_compat_api_version(name, crc) \
    api_try_hookup_api_ ## name ## _plugin_1908(vm);
#include "plugin-headers-1908.h"
#undef vl_1908_compat_api_version

}

/* get the first message id */
#define vl_1908_compat_api_version(name, crc) \
    static void api_try_get_api_first_msg_ ## name ## _plugin_1908(vlib_main_t * vm) { \
                if (name ## _curr_base_msg_id == 65535) { return; } \
                u8 * full_name = format (0, #name "_%08x%c", crc, 0); \
                u16 msg_count = 0; \
                u16 first_id = 0;

#define vl_1908_msg_name_crc_list
#define _(a_id,a_msg,a_crc) \
                msg_count++; \

#define vl_1908_compat_api_version_trailer(name, crc) \
                first_id = vl_1908_msg_api_get_msg_ids((void *)full_name, msg_count); \
                clib_warning("First message for 1908 %s: %d", full_name, first_id); \
                vec_free(full_name); \
                name ## _1908_base_msg_id = first_id; \
    }
#include "plugin-headers-1908.h"
#undef vl_1908_compat_api_version
#undef vl_1908_compat_api_version_trailer
#undef _
#undef vl_1908_msg_name_crc_list

static void
api_try_get_api_first_msg_plugins_1908 (vlib_main_t * vm)
{
#define vl_1908_compat_api_version(name, crc) \
    api_try_get_api_first_msg_ ## name ## _plugin_1908(vm);
#include "plugin-headers-1908.h"
#undef vl_1908_compat_api_version
}



/*** tie it all together *****/

void
api_hookup_plugins_api (vlib_main_t * vm)
{
  api_try_get_api_first_msg_plugins_curr (vm);
  api_try_get_api_first_msg_plugins_1908 (vm);
  api_hookup_plugins_api_1908 (vm);
  api_hookup_plugins_api_curr (vm);

  api_hookup_plugins_api1908compat (vm);
  api_downward_hookup_plugins_api1908compat (vm);

}
