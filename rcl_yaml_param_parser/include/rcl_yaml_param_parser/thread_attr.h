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

#ifndef RCL_YAML_PARAM_PARSER__THREAD_ATTR_H_
#define RCL_YAML_PARAM_PARSER__THREAD_ATTR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

#include "rcutils/types.h"
#include "rcutils/visibility_control.h"
#include "rcutils/allocator.h"
#include "rcutils/macros.h"
#include "rcl_yaml_param_parser/types.h"

extern const char * const ROS_THREAD_ATTR_SETTING_ENV_VAR;

/// \brief Initialize thread attribute structure
/// \param[in] allocator memory allocator to be used
/// \return a pointer to thread attribute structure on success or NULL on failure
RCUTILS_PUBLIC
RCUTILS_WARN_UNUSED
rcl_thread_attrs_t *
rcl_thread_attrs_struct_init(rcutils_allocator_t allocator);

/// \brief Initialize thread attribute structure with a capacity
/// \param[in] allocator memory allocator to be used
/// \param[in] capacity a capacity to thread attribute structure
/// \return a pointer to thread attribute structure on success or NULL on failure
rcl_thread_attrs_t *
rcl_thread_attrs_struct_init_with_capacity(rcutils_allocator_t allocator, size_t capacity);

/// \brief Free parameter structure
/// \param[in] rcl_thread The structure to be deallocated.
/// \return #RCUTILS_RET_OK if the memory was successfully freed, or
/// \return #RCUTILS_RET_INVALID_ARGUMENT if any function arguments are invalid
RCUTILS_PUBLIC
RCUTILS_WARN_UNUSED
rcutils_ret_t
rcl_thread_attrs_fini(rcl_thread_attrs_t * rcl_thread);

/// \brief Initialize thread attribute structure
/// \param[in] src The structure to be copied.
/// \param[out] dst A zero-initialized rcl_thread_attrs_t structure to be copied into.
/// \return #RCUTILS_RET_OK if the structure was copied successfully, or
/// \return #RCUTILS_RET_INVALID_ARGUMENT if any function arguments are invalid, or
/// \return #RCL_RET_BAD_ALLOC if allocating memory failed
RCUTILS_PUBLIC
RCUTILS_WARN_UNUSED
rcutils_ret_t
rcl_thread_attrs_copy(
  const rcl_thread_attrs_t * src,
  rcl_thread_attrs_t * dst);

/// Determine the default thread attribute from string, based on the environment.
/// \param[out] thread_attr Must not be NULL.
/// \param[in] allocator memory allocator to be used
/// \return #RCUTILS_RET_INVALID_ARGUMENT if an argument is invalid, or,
/// \return #RCUTILS_RET_ERROR in case of an unexpected error, or,
/// \return #RCUTILS_RET_BAD_ALLOC if allocating memory failed, or
/// \return #RCUTILS_RET_OK.
RCUTILS_PUBLIC
rcutils_ret_t
rcl_get_default_thread_attrs(char ** thread_attr, rcutils_allocator_t allocator);

/// Determine the default thread attribute from file path, based on the environment.
/// \param[out] thread_attr_file_path Must not be NULL.
/// \param[in] allocator memory allocator to be used
/// \return #RCUTILS_RET_INVALID_ARGUMENT if an argument is invalid, or,
/// \return #RCUTILS_RET_ERROR in case of an unexpected error, or,
/// \return #RCUTILS_RET_BAD_ALLOC if allocating memory failed, or
/// \return #RCUTILS_RET_OK.
RCUTILS_PUBLIC
rcutils_ret_t
rcl_get_default_thread_attr_file_path(
  char ** thread_attr_file_path,
  rcutils_allocator_t allocator);

#ifdef __cplusplus
}
#endif

#endif  // RCL_YAML_PARAM_PARSER__THREAD_ATTR_H_
