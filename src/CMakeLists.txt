
# Copyright (c) <current-year> <your-organization>
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include_directories(src_1908)
add_vpp_plugin(api1908compat
  SOURCES
  api1908compat.c 
  api1908uplink.c 
  api1908downlink.c
  api1908compat.h
  all-handlers.c
  src_1908/vlibapi_1908/api_shared.c
  src_1908/vlibapi_1908/node_serialize.c
  src_1908/vpp_1908/api/api.c
  src_1908/vlibmemory_1908/vlib_api.c
  src_1908/vpp_1908/api/types.c
  src_1908/vlibmemory_1908/vlib_api_cli.c
  src_1908/vlibmemory_1908/memory_api.c
  src_1908/vlibmemory_1908/memory_shared.c
  src_1908/vlibmemory_1908/socket_api.c
  src_1908/vlibmemory_1908/socket_api.h
  src_1908/vpp_1908/api/custom_dump.c

  COMPONENT
  vpp-plugin-apicompat

)

add_dependencies(api1908compat_plugin abf_plugin acl_plugin avf_plugin cdp_plugin crypto_ipsecmb_plugin crypto_openssl_plugin ct6_plugin dns_plugin dpdk_plugin flowprobe_plugin gbp_plugin gtpu_plugin hs_apps_plugin http_static_plugin igmp_plugin ikev2_plugin ila_plugin ioam_plugin l2e_plugin l3xc_plugin lacp_plugin lb_plugin mactime_plugin map_plugin memif_plugin nat_plugin nsh_plugin nsim_plugin oddbuf_plugin perfmon_plugin ping_plugin pppoe_plugin quic_plugin rdma_plugin stn_plugin svs_plugin tlsmbedtls_plugin tlsopenssl_plugin unittest_plugin vmxnet3_plugin)

