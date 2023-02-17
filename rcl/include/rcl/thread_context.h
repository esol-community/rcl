// Copyright 2023 eSOL Co.,Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RCL__THREAD_CONTEXT_H_
#define RCL__THREAD_CONTEXT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#include "rcl/types.h"
#include "rcl/macros.h"
#include "rcl/visibility_control.h"
#include "rcl_yaml_param_parser/types.h"

/// thread attribute from enviroment value.
typedef struct thread_attr_context_s
{
  /// thread attribute.
  rcl_thread_attrs_t * thread_attrs;
} thread_attr_context_t;

/// Return a zero initialization thread attribute context object.
RCL_PUBLIC
RCL_WARN_UNUSED
thread_attr_context_t
thread_attr_get_zero_initialized_context(void);

/// Finalize a thread attribute context.
/**
 * \param[inout] context object to be finalized.
 * \return #RCL_RET_OK if successful, or
 * \return #RCL_RET_INVALID_ARGUMENT if any arguments are invalid, or
 * \return #RCL_RET_BAD_ALLOC if allocating memory failed
 */
RCL_PUBLIC
RCL_WARN_UNUSED
rcl_ret_t
thread_attr_context_init(thread_attr_context_t * context, rcutils_allocator_t allocator);

/// Initialize a thread attribute context.
/**
 * \param[inout] context object to be finalized.
 * \return #RCL_RET_OK if the shutdown was completed successfully, or
 * \return #RCL_RET_INVALID_ARGUMENT if any arguments are invalid
 */
RCL_PUBLIC
RCL_WARN_UNUSED
rcl_ret_t
thread_attr_context_fini(thread_attr_context_t * context);

#ifdef __cplusplus
}
#endif

#endif  // RCL__THREAD_CONTEXT_H_
