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



static void
vl_reflect_api_nat44_forwarding_enable_disable_bbb24748_handler(vl_api_nat44_forwarding_enable_disable_t *om) {
    // This message is not used in this direction, so a no-op
    clib_warning("REFLECT vl_reflect_api_nat44_forwarding_enable_disable_bbb24748_handler called");
    send_old_nat44_forwarding_enable_disable_b3e225d2_handler(om, 1);
};

*/

