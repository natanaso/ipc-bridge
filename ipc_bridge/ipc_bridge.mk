IPC_LFLAGS = -L/opt/ipc/lib
IPC_BRIDGE_CXXFLAGS := $(foreach path, $(shell rospack cflags-only-I ipc_bridge), -I$(path))

xdr: generate_msgs

generate_msgs:
	bash -c "`rospack find ipc_bridge`/generate_msgs.sh ."
