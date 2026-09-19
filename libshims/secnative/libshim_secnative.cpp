/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>

/*
 * libsec-ril was built against the pre-Android 7 atomic C API. The release
 * compare-and-swap operation returns zero on success and one on failure.
 */
extern "C" int android_atomic_release_cas(
        int32_t old_value, int32_t new_value, volatile int32_t* address) {
    return __atomic_compare_exchange_n(address, &old_value, new_value, false,
            __ATOMIC_RELEASE, __ATOMIC_RELAXED) ? 0 : 1;
}
