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

/// @file

#ifndef RCL__THREAD_ATTR_PARSE_H_
#define RCL__THREAD_ATTR_PARSE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

#include "rcl/types.h"
#include "rcl/visibility_control.h"
#include "rcl/allocator.h"
#include "rcl/macros.h"
#include "rcl_yaml_param_parser/types.h"

/// Parse an argument that may or may not be a thread attribute.
/**
 * \param[in] arg the argument to parse
 * \param[in,out] thread_attrs thread attribute structure to populate.
 *     This structure must have been initialized by the caller.
 * \return RCL_RET_OK if a valid rule was parsed, or
 * \return RCL_RET_INVALID_ARGUMENT if an argument is invalid, or
 * \return RCL_RET_INVALID_THREAD_ATTRS if the argument is not a valid rule
 */
rcl_ret_t
_rcl_parse_thread_attrs(
  const char * arg,
  rcl_thread_attrs_t * thread_attrs);

/// Parse an argument that may or may not be a thread attribute file.
/**
 * The syntax of the file name is not validated.
 * \param[in] path the argument to parse
 * \param[in,out] thread_attrs string that could be a thread attribute file name
 * \return RCL_RET_OK if the rule was parsed correctly, or
 * \return RCL_RET_INVALID_ARGUMENT if an argument is invalid, or
 * \return RCL_RET_INVALID_THREAD_ATTRS if the argument is not a valid rule
 */
rcl_ret_t
_rcl_parse_thread_attr_file(
  const char * path,
  rcl_thread_attrs_t * thread_attrs);

#ifdef __cplusplus
}
#endif

#endif  // RCL__THREAD_ATTR_PARSE_H_
