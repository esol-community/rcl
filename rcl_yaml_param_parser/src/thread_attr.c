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

#include "rcl_yaml_param_parser/thread_attr.h"

#include <errno.h>
#include <limits.h>

#include "rcutils/env.h"
#include "rcutils/strdup.h"
#include "rcutils/error_handling.h"

#define INIT_NUM_THREAD_ATTRIBUTE 16U

rcl_thread_attrs_t *
rcl_thread_attrs_struct_init(rcutils_allocator_t allocator)
{
  return rcl_thread_attrs_struct_init_with_capacity(allocator, INIT_NUM_THREAD_ATTRIBUTE);
}

rcl_thread_attrs_t *
rcl_thread_attrs_struct_init_with_capacity(rcutils_allocator_t allocator, size_t capacity)
{
  rcl_thread_attrs_t * rcl_thread;
  rcl_thread = allocator.zero_allocate(1, sizeof(rcl_thread_attrs_t), allocator.state);
  if (NULL == rcl_thread) {
    RCUTILS_SET_ERROR_MSG("Failed to allocate memory for rcl thread attr");
    return NULL;
  }
  rcl_thread->allocator = allocator;
  rcl_thread->num_attributes = 0U;
  rcl_thread->capacity_attributes = capacity;
  rcl_thread->attributes =
    allocator.zero_allocate(
    capacity, sizeof(rcl_thread_attr_t),
    allocator.state);
  if (NULL == rcl_thread->attributes) {
    allocator.deallocate(rcl_thread, allocator.state);
    rcl_thread = NULL;
    RCUTILS_SET_ERROR_MSG("Failed to allocate memory for thread attributes");
    return NULL;
  }
  return rcl_thread;
}

rcutils_ret_t
rcl_thread_attrs_copy(
  const rcl_thread_attrs_t * src,
  rcl_thread_attrs_t * dst)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(src, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(dst, RCUTILS_RET_INVALID_ARGUMENT);

  size_t size = src->capacity_attributes * sizeof(rcl_thread_attr_t);
  void * new_attributes = src->allocator.reallocate(
    dst->attributes, size, src->allocator.state);
  if (NULL == new_attributes) {
    RCUTILS_SET_ERROR_MSG("Failed to reallocate memory for thread attributes");
    return RCUTILS_RET_BAD_ALLOC;
  }
  dst->attributes = new_attributes;
  for (size_t j = 0; j < src->num_attributes; j++) {
    dst->attributes[j].core_affinity = src->attributes[j].core_affinity;
    dst->attributes[j].scheduling_policy = src->attributes[j].scheduling_policy;
    dst->attributes[j].priority = src->attributes[j].priority;
  }
  dst->num_attributes = src->num_attributes;
  dst->capacity_attributes = src->capacity_attributes;
  dst->allocator = src->allocator;

  return RCUTILS_RET_OK;
}

rcutils_ret_t
rcl_thread_attrs_fini(rcl_thread_attrs_t * rcl_thread)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(rcl_thread, RCUTILS_RET_INVALID_ARGUMENT);
  rcutils_allocator_t * allocator = &rcl_thread->allocator;
  RCUTILS_CHECK_ALLOCATOR(allocator, return RCUTILS_RET_INVALID_ARGUMENT);
  if (NULL != rcl_thread->attributes) {
    allocator->deallocate(rcl_thread->attributes, allocator->state);
    rcl_thread->attributes = NULL;
  }
  rcl_thread->capacity_attributes = INIT_NUM_THREAD_ATTRIBUTE;
  rcl_thread->num_attributes = 0U;
  return RCUTILS_RET_OK;
}

rcutils_ret_t
rcl_get_default_thread_attrs(char ** thread_attr_string, rcutils_allocator_t allocator)
{
  const char * const ROS_THREAD_ATTR_SETTING_ENV_VAR = "ROS_THREAD_ATTR_SETTING";

  RCUTILS_CAN_SET_MSG_AND_RETURN_WITH_ERROR_OF(RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CAN_SET_MSG_AND_RETURN_WITH_ERROR_OF(RCUTILS_RET_ERROR);
  RCUTILS_CHECK_ALLOCATOR(&allocator, return RCUTILS_RET_INVALID_ARGUMENT);

  const char * ros_thread_attr_string = NULL;
  const char * get_env_error_str = NULL;

  RCUTILS_CHECK_ARGUMENT_FOR_NULL(thread_attr_string, RCUTILS_RET_INVALID_ARGUMENT);

  get_env_error_str = rcutils_get_env(ROS_THREAD_ATTR_SETTING_ENV_VAR, &ros_thread_attr_string);
  if (NULL != get_env_error_str) {
    RCUTILS_SET_ERROR_MSG_WITH_FORMAT_STRING(
      "Error getting env var '" RCUTILS_STRINGIFY(ROS_THREAD_ATTR_SETTING_ENV_VAR) "': %s\n",
      get_env_error_str);
    return RCUTILS_RET_ERROR;
  }
  if (ros_thread_attr_string && strcmp(ros_thread_attr_string, "") != 0) {
    *thread_attr_string = rcutils_strdup(ros_thread_attr_string, allocator);
  } else {
    *thread_attr_string = rcutils_strdup("", allocator);
  }
  if (!*thread_attr_string) {
    RCUTILS_SET_ERROR_MSG("failed to set thread_attr_string");
    return RCUTILS_RET_BAD_ALLOC;
  }
  return RCUTILS_RET_OK;
}

rcutils_ret_t
rcl_get_default_thread_attr_file_path(
  char ** thread_attr_file_path,
  rcutils_allocator_t allocator)
{
  const char * const ROS_THREAD_ATTR_FILE_PATH_ENV_VAR = "ROS_THREAD_ATTR_FILE_PATH";
  RCUTILS_CAN_SET_MSG_AND_RETURN_WITH_ERROR_OF(RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CAN_SET_MSG_AND_RETURN_WITH_ERROR_OF(RCUTILS_RET_ERROR);
  RCUTILS_CHECK_ALLOCATOR(&allocator, return RCUTILS_RET_INVALID_ARGUMENT);

  const char * ros_thread_attr_file_path = NULL;
  const char * get_env_error_str = NULL;

  RCUTILS_CHECK_ARGUMENT_FOR_NULL(thread_attr_file_path, RCUTILS_RET_INVALID_ARGUMENT);

  get_env_error_str =
    rcutils_get_env(ROS_THREAD_ATTR_FILE_PATH_ENV_VAR, &ros_thread_attr_file_path);
  if (NULL != get_env_error_str) {
    RCUTILS_SET_ERROR_MSG_WITH_FORMAT_STRING(
      "Error getting env var '" RCUTILS_STRINGIFY(ROS_THREAD_ATTR_FILE_PATH_ENV_VAR) "': %s\n",
      get_env_error_str);
    return RCUTILS_RET_ERROR;
  }
  if (ros_thread_attr_file_path && strcmp(ros_thread_attr_file_path, "") != 0) {
    *thread_attr_file_path = rcutils_strdup(ros_thread_attr_file_path, allocator);
  } else {
    *thread_attr_file_path = rcutils_strdup("", allocator);
  }
  if (!*thread_attr_file_path) {
    RCUTILS_SET_ERROR_MSG("failed to set thread_attr_file_path");
    return RCUTILS_RET_BAD_ALLOC;
  }
  return RCUTILS_RET_OK;
}
