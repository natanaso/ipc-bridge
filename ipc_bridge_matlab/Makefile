MEX = mex
IPC_BRIDGE_CPATH = ../ipc_bridge/include
IPC_LD_LIBRARY_PATH = /opt/ipc/lib

MEX_FILES := $(patsubst src/%.cc,%,$(wildcard src/*.cc))

all: prep $(MEX_FILES)

%: src/%.cc
	$(MEX) -I./include -I$(IPC_BRIDGE_CPATH) -lstdc++ -L$(IPC_LD_LIBRARY_PATH) -lipc $^ -output bin/$@

prep:
	bash -c "mkdir -p bin"

clean:
	rm bin/*.mex*
