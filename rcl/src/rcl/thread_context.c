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

#ifdef __cplusplus
extern "C"
{
#endif

#include "rcl/thread_context.h"

#include "./common.h"
#include "rcl/error_handling.h"
#include "rcutils/macros.h"
#include "rcutils/logging_macros.h"
#include "rcutils/strdup.h"
#include "rcl_yaml_param_parser/thread_attr.h"

thread_attr_context_t
thread_attr_get_zero_initialized_context(void)
{
  return (const thread_attr_context_t) {
           .thread_attrs = NULL,
  };  // NOLINT(readability/braces): false positive
}

rcl_ret_t
thread_attr_context_init(thread_attr_context_t * context, rcutils_allocator_t allocator)
{
  RCL_CHECK_ARGUMENT_FOR_NULL(context, RCL_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ALLOCATOR(&allocator, return RCL_RET_INVALID_ARGUMENT);
  if (NULL != context->thread_attrs) {
    RCL_SET_ERROR_MSG("expected zero-initialized context");
    return RCL_RET_INVALID_ARGUMENT;
  }
  context->thread_attrs = rcl_thread_attrs_struct_init(allocator);
  if (NULL == context->thread_attrs) {
    return RCL_RET_BAD_ALLOC;
  }
  return RCL_RET_OK;
}

rcl_ret_t
thread_attr_context_fini(thread_attr_context_t * context)
{
  RCL_CHECK_ARGUMENT_FOR_NULL(context, RCL_RET_INVALID_ARGUMENT);

  rcl_ret_t ret = RCL_RET_OK;

  if (NULL != context->thread_attrs) {
    ret = rcl_thread_attrs_fini(context->thread_attrs);
  }

  *context = thread_attr_get_zero_initialized_context();
  return ret;
}

#ifdef __cplusplus
}
#endif
