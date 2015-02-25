# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := jni_aes
LOCAL_SRC_FILES := jni_aes.c
#LOCAL_CPP_EXTENSION := cc

#增加log函数对应的log库
#引入函数库方法 : 使用 LOCAL_LDLIBS += -l函数库名, 注意函数库名不带lib前缀 和.so 后缀, 同时可以添加多个库, 使用 -l库1 -l库2 -库3 ;
LOCAL_LDLIBS += -llog 
include $(BUILD_SHARED_LIBRARY)
