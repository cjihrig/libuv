/* Copyright libuv contributors. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "uv.h"
#include "task.h"

#include <stdint.h>

TEST_IMPL(buf_large) {
#if defined(__MVS__)
  RETURN_SKIP("SIZE_MAX not defined on zOS");
#else
  uv_buf_t buf = uv_buf_init(NULL, SIZE_MAX);
  ASSERT(buf.len == SIZE_MAX);
#ifdef _WIN32
  WSABUF* wbuf = (WSABUF*)&buf;
  ASSERT(wbuf->len == buf.len);
#else
  struct iovec* iobuf = (struct iovec*)&buf;
  ASSERT(iobuf->iov_len == buf.len);
#endif

  return 0;
#endif
}
