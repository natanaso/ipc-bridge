PKG_CXXFLAGS += $(foreach path, $(shell rospack cflags-only-I ipc_roslib), -I$(path))
