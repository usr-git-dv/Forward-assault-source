LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libdobby
LOCAL_SRC_FILES := core/cheat/hooks/dobby/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_EXPORT_C_INCLUDES := core/cheat/hooks/dobby/

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Infinity

LOCAL_SRC_FILES := main.cpp \
	core/cheat/hooks/hooks.cpp \
	core/cheat/inits/inits.cpp \
	core/memory/memory.cpp \
    core/searcher/searcher.cpp \
	core/visuals/esp/esp.cpp \
	core/visuals/menu/menu.cpp \
	core/visuals/widgets/custom_widgets.cpp \
	$(wildcard $(LOCAL_PATH)/ImGui/*.cpp) \
	$(wildcard $(LOCAL_PATH)/ImGui/backends/*.cpp)

LOCAL_CFLAGS := -O2 -ffast-math -ffunction-sections -fdata-sections
LOCAL_CFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
LOCAL_CPPFLAGS := -std=c++23 -O2
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3
LOCAL_STATIC_LIBRARIES := libdobby

include $(BUILD_SHARED_LIBRARY)