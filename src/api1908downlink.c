
#include <vnet/vnet.h>
#include <vnet/plugin/plugin.h>
#include <api1908compat/api1908compat.h>

#include <vlibapi/api.h>
#include <vpp/app/version.h>
#include <stdbool.h>


// #include <vpp/api/types.h>

#include <vlibmemory_1908/api.h>

void
api1908compat_send_to_client(int client_index, void *msg) {
	// clib_warning("Client: %d, message: %p", client_index, msg);
	vl_1908_api_registration_t * rp = vl_1908_api_client_index_to_registration(client_index);
	vl_1908_api_send_msg(rp, msg);
}

