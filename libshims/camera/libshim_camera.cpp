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

#include <dlfcn.h>
#include <stdint.h>
#include <string>

namespace {

void* load_libui_symbol(const char* symbol_name) {
    static void* libui = dlopen("libui.so", RTLD_NOW | RTLD_LOCAL);
    if (libui == nullptr) {
        return nullptr;
    }

    return dlsym(libui, symbol_name);
}

using GraphicBufferSizeConstructor = void (*)(
        void*, uint32_t, uint32_t, int, uint32_t, std::string);
using GraphicBufferDestructor = void (*)(void*);

}  // namespace

/*
 * CameraParameters extensions removed from the platform Camera1 API but still
 * referenced by the Samsung S5K2P2/S5K8B1 camera binaries.
 */
extern "C" const char _ZN7android16CameraParameters13FLASH_MODE_ONEE[] = "one";
extern "C" const char _ZN7android16CameraParameters9ISO_NIGHTE[] = "night";
extern "C" const char _ZN7android16CameraParameters10ISO_SPORTSE[] = "sports";
extern "C" const char _ZN7android16CameraParameters7ISO_6400E[] = "6400";
extern "C" const char _ZN7android16CameraParameters7ISO_3200E[] = "3200";
extern "C" const char _ZN7android16CameraParameters7ISO_1600E[] = "1600";
extern "C" const char _ZN7android16CameraParameters6ISO_80E[] = "80";
extern "C" const char _ZN7android16CameraParameters6ISO_50E[] = "50";
extern "C" const char _ZN7android16CameraParameters27KEY_SUPPORTED_METERING_MODEE[] =
        "metering-values";
extern "C" const char _ZN7android16CameraParameters15METERING_CENTERE[] = "center";
extern "C" const char _ZN7android16CameraParameters15METERING_MATRIXE[] = "matrix";
extern "C" const char _ZN7android16CameraParameters13METERING_SPOTE[] = "spot";
extern "C" const char _ZN7android16CameraParameters12METERING_OFFE[] = "off";
extern "C" const char _ZN7android16CameraParameters25KEY_DYNAMIC_RANGE_CONTROLE[] =
        "dynamic-range-control";
extern "C" const char _ZN7android16CameraParameters22KEY_SUPPORTED_PHASE_AFE[] =
        "phase-af-values";
extern "C" const char _ZN7android16CameraParameters12KEY_PHASE_AFE[] = "phase-af";
extern "C" const char _ZN7android16CameraParameters20KEY_SUPPORTED_RT_HDRE[] =
        "rt-hdr-values";
extern "C" const char _ZN7android16CameraParameters10KEY_RT_HDRE[] = "rt-hdr";

/*
 * Android 5/6 Samsung binaries use the four-argument GraphicBuffer
 * constructor. Android 11 retains the same behavior through a constructor
 * that additionally accepts a requestor name, so forward to it when present.
 */
extern "C" __attribute__((visibility("default"))) void
legacy_graphic_buffer_constructor(void* self, uint32_t width, uint32_t height,
        int format, uint32_t usage)
        __asm__("_ZN7android13GraphicBufferC1Ejjij");

extern "C" void legacy_graphic_buffer_constructor(
        void* self, uint32_t width, uint32_t height, int format, uint32_t usage) {
    const char modern_symbol[] =
            "_ZN7android13GraphicBufferC1EjjijNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE";
    auto constructor = reinterpret_cast<GraphicBufferSizeConstructor>(
            load_libui_symbol(modern_symbol));
    if (constructor == nullptr) {
        return;
    }

    constructor(self, width, height, format, usage, std::string("k3gxx-camera"));
}

extern "C" __attribute__((visibility("default"))) void
legacy_graphic_buffer_base_constructor(void* self, uint32_t width,
        uint32_t height, int format, uint32_t usage)
        __asm__("_ZN7android13GraphicBufferC2Ejjij");

extern "C" void legacy_graphic_buffer_base_constructor(
        void* self, uint32_t width, uint32_t height, int format, uint32_t usage) {
    legacy_graphic_buffer_constructor(self, width, height, format, usage);
}

/*
 * Keep the old complete-object destructor entry point available. The current
 * libui implementation exposes the base-object destructor, which performs the
 * actual handle release for the initialized object.
 */
extern "C" __attribute__((visibility("default"))) void
legacy_graphic_buffer_destructor(void* self)
        __asm__("_ZN7android13GraphicBufferD1Ev");

extern "C" void legacy_graphic_buffer_destructor(void* self) {
    static const char base_destructor[] = "_ZN7android13GraphicBufferD2Ev";
    auto destructor = reinterpret_cast<GraphicBufferDestructor>(
            load_libui_symbol(base_destructor));
    if (destructor == nullptr) {
        return;
    }

    destructor(self);
}

extern "C" __attribute__((visibility("default"))) void
legacy_graphic_buffer_base_destructor(void* self)
        __asm__("_ZN7android13GraphicBufferD2Ev");

extern "C" void legacy_graphic_buffer_base_destructor(void* self) {
    legacy_graphic_buffer_destructor(self);
}
