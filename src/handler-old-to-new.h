/*
 *
 * If you add a new field to existing message, for example like this:
 *

@@ -1024,6 +1030,7 @@ autoreply define nat44_del_session {
 autoreply define nat44_forwarding_enable_disable {
   u32 client_index;
   u32 context;
+  u32 some_value;
   bool enable;
 };
 

Then you ought to define here the translation function
from old format to new format. The compiler will prompt
for the exact name.....


static void inline
send_new_nat44_forwarding_enable_disable_b3e225d2_handler (void *mp_orig,
							   int do_copy)
{
  void *mp = mp_orig;
  if (do_copy)
    {
      u32 len = vl_msg_api_get_msg_length (mp_orig);
      mp = vl_msg_api_alloc (len);
      clib_memcpy (mp, mp_orig, len);
      vl_api_nat44_forwarding_enable_disable_t *mp1 = mp;
      vl_1908_api_nat44_forwarding_enable_disable_t *mp0 = mp_orig;
      mp1->enable = mp0->enable;
      mp1->some_value = 0;
    }
  send_new_nat44_forwarding_enable_disable_bbb24748_handler(mp, 0);
}

On the other hand, deleting the acl_plugin_get_version message will cause compilation errors,
which can be fixed as follows:

u32 MSG_ID_CURR_FOR_acl_plugin_get_version = ~0;
u32 MSG_ID_CURR_FOR_acl_plugin_get_version_reply = ~0;

static void inline
send_new_acl_plugin_get_version_51077d14_handler(void *mp_orig,
							   int do_copy)
{
  vl_1908_api_acl_plugin_get_version_t *mp0 = mp_orig;
  vl_1908_api_acl_plugin_get_version_reply_t *rmp;
  u32 len = sizeof(*rmp);
  rmp = vl_1908_msg_api_alloc (len);
  rmp->_vl_1908_msg_id = clib_net_to_host_u16(MSG_ID_1908_FOR_acl_plugin_get_version_reply);
  rmp->context = mp0->context;
  rmp->major = clib_net_to_host_u32(42); // some bogus version
  rmp->minor = 0;
  api1908compat_send_to_client(last_client_index, rmp);
}

static void inline
send_new_acl_plugin_get_version_reply_9b32cf86_handler (void *mp_orig,
                                                           int do_copy)
{
	// this message is not sent from the 1908api side - so no-op
}

*/
