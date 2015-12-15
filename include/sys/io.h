/*
 * Copyright (c) 2008-2015 Travis Geiselbrecht
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <compiler.h>
#include <list.h>
#include <sys/types.h>

/* LK specific calls to register to get input/output of the main console */

__BEGIN_CDECLS

typedef struct __print_callback print_callback_t;
struct __print_callback {
    struct list_node entry;
    void (*print)(print_callback_t *cb, const char *str, size_t len);
};

/* register callback to receive debug prints */
void register_print_callback(print_callback_t *cb);
void unregister_print_callback(print_callback_t *cb);

/* the underlying handle to talk to io devices */
typedef struct io_handle {
    ssize_t (*write)(void *ctx, const char *buf, size_t len);
    ssize_t (*read)(void *ctx, char *buf, size_t len);

    void *ctx;
} io_handle_t;

/* the main console io handle */
extern io_handle_t console_io;

/* convenience routines for the above */
static inline ssize_t io_write(const io_handle_t *io, const char *buf, size_t len)
{
    return io->write(io->ctx, buf, len);
}

static inline ssize_t io_read(const io_handle_t *io, char *buf, size_t len)
{
    return io->read(io->ctx, buf, len);
}

__END_CDECLS
