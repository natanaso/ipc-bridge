.PHONY= all prep clean
.DEFAULT_GOAL=all

all: prep xdr mex ros

include $(shell rospack find ipc_bridge)/ipc_bridge.mk
include $(shell rospack find ipc_bridge_matlab)/ipc_bridge_matlab.mk
include $(shell rospack find ipc_bridge_ros)/ipc_bridge_ros.mk

prep:
	bash -c "mkdir -p bin"

clean:
	rm -fr bin include/ipc_bridge
