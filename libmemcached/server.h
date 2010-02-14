/* LibMemcached
 * Copyright (C) 2006-2009 Brian Aker
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license.  See
 * the COPYING file in the parent directory for full text.
 *
 * Summary: String structure used for libmemcached.
 *
 */

#ifndef __LIBMEMCACHED_SERVER_H__
#define __LIBMEMCACHED_SERVER_H__


struct memcached_server_st {
  struct {
    bool is_allocated MEMCACHED_BITFIELD;
    bool is_initialized MEMCACHED_BITFIELD;
    bool sockaddr_inited MEMCACHED_BITFIELD;
    bool is_shutting_down MEMCACHED_BITFIELD;
  } options;
  uint32_t number_of_hosts;
  uint32_t cursor_active;
  in_port_t port;
  int cached_errno;
  int fd;
  uint32_t io_bytes_sent; /* # bytes sent since last read */
  uint32_t server_failure_counter;
  uint32_t weight;
  struct { // Place any "state" sort variables in here.
    bool is_corked;
  } state;
  uint8_t major_version;
  uint8_t micro_version;
  uint8_t minor_version;
  memcached_connection_t type;
  char *read_ptr;
  char *cached_server_error;
  size_t read_buffer_length;
  size_t read_data_length;
  size_t write_buffer_offset;
  struct addrinfo *address_info;
  time_t next_retry;
  const memcached_st *root;
  uint64_t limit_maxbytes;
  char read_buffer[MEMCACHED_MAX_BUFFER];
  char write_buffer[MEMCACHED_MAX_BUFFER];
  char hostname[NI_MAXHOST];
};


#ifdef __cplusplus
extern "C" {
#endif

LIBMEMCACHED_API
memcached_return_t memcached_server_cursor(const memcached_st *ptr,
                                           const memcached_server_fn *callback,
                                           void *context,
                                           uint32_t number_of_callbacks);

LIBMEMCACHED_API
  memcached_server_instance_st *memcached_server_by_key(const memcached_st *ptr,
                                                        const char *key,
                                                        size_t key_length,
                                                        memcached_return_t *error);

LIBMEMCACHED_API
void memcached_server_error_reset(memcached_server_st *ptr);

LIBMEMCACHED_API
void memcached_server_free(memcached_server_st *ptr);

LIBMEMCACHED_LOCAL
memcached_server_st *memcached_server_clone(memcached_server_st *destination,
                                            const memcached_server_st *source);

LIBMEMCACHED_API
memcached_return_t memcached_server_remove(memcached_server_st *st_ptr);

LIBMEMCACHED_API
memcached_server_instance_st *memcached_server_get_last_disconnect(const memcached_st *ptr);


LIBMEMCACHED_API
memcached_return_t memcached_server_add_udp(memcached_st *ptr,
                                            const char *hostname,
                                            in_port_t port);
LIBMEMCACHED_API
memcached_return_t memcached_server_add_unix_socket(memcached_st *ptr,
                                                    const char *filename);
LIBMEMCACHED_API
memcached_return_t memcached_server_add(memcached_st *ptr,
                                        const char *hostname, in_port_t port);

LIBMEMCACHED_API
memcached_return_t memcached_server_add_udp_with_weight(memcached_st *ptr,
                                                        const char *hostname,
                                                        in_port_t port,
                                                        uint32_t weight);
LIBMEMCACHED_API
memcached_return_t memcached_server_add_unix_socket_with_weight(memcached_st *ptr,
                                                                const char *filename,
                                                                uint32_t weight);
LIBMEMCACHED_API
memcached_return_t memcached_server_add_with_weight(memcached_st *ptr, const char *hostname,
                                                    in_port_t port,
                                                    uint32_t weight);
/* Server List Public functions */

LIBMEMCACHED_API
void memcached_server_list_free(memcached_server_st *ptr);


LIBMEMCACHED_API
memcached_return_t memcached_server_push(memcached_st *ptr, const memcached_server_st *list);

LIBMEMCACHED_API
memcached_server_st *memcached_server_list_append(memcached_server_st *ptr,
                                                  const char *hostname,
                                                  in_port_t port,
                                                  memcached_return_t *error);
LIBMEMCACHED_API
memcached_server_st *memcached_server_list_append_with_weight(memcached_server_st *ptr,
                                                              const char *hostname,
                                                              in_port_t port,
                                                              uint32_t weight,
                                                              memcached_return_t *error);
LIBMEMCACHED_API
uint32_t memcached_server_list_count(const memcached_server_st *ptr);

LIBMEMCACHED_API
uint32_t memcached_server_count(const memcached_st *);


LIBMEMCACHED_LOCAL
uint32_t memcached_servers_set_count(memcached_server_st *servers, uint32_t count);

LIBMEMCACHED_API
memcached_server_st *memcached_server_list(memcached_st *);

LIBMEMCACHED_LOCAL
void memcached_server_list_set(memcached_st *self, memcached_server_st *list);

/**
  Operations on Single Servers.
*/
LIBMEMCACHED_API
uint32_t memcached_server_response_count(memcached_server_instance_st *self);

LIBMEMCACHED_API
const char *memcached_server_name(memcached_server_instance_st *self);

LIBMEMCACHED_API
in_port_t memcached_server_port(memcached_server_instance_st *self);

LIBMEMCACHED_API
const char *memcached_server_error(memcached_server_instance_st *ptr);



#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __LIBMEMCACHED_SERVER_H__ */
