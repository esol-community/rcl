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

#include "./thread_attr_parse.h"  // NOLINT

#include <errno.h>
#include <limits.h>

#include "rcutils/strdup.h"
#include "rcutils/allocator.h"

#include "rcl/error_handling.h"
#include "rcl/types.h"

#include "rcl_yaml_param_parser/parser.h"

rcl_ret_t
_rcl_parse_thread_attrs(
  const char * arg,
  rcl_thread_attrs_t * thread_attrs)
{
  RCL_CHECK_ARGUMENT_FOR_NULL(arg, RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_ARGUMENT_FOR_NULL(thread_attrs, RCL_RET_INVALID_ARGUMENT);

  if (!rcl_parse_yaml_thread_attr_value(arg, thread_attrs)) {
    return RCL_RET_INVALID_THREAD_ATTRS;
  }
  return RCL_RET_OK;
}

rcl_ret_t
_rcl_parse_thread_attr_file(
  const char * path,
  rcl_thread_attrs_t * thread_attrs)
{
  RCL_CHECK_ARGUMENT_FOR_NULL(path, RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_ARGUMENT_FOR_NULL(thread_attrs, RCL_RET_INVALID_ARGUMENT);

  if (!rcl_parse_yaml_thread_attr_file(path, thread_attrs)) {
    return RCL_RET_INVALID_THREAD_ATTRS;
  }
  return RCL_RET_OK;
}
