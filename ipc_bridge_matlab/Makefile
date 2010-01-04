MEX = /Applications/MATLAB_R2009b.app/bin/mex
IPC_BRIDGE_CPATH = ../ipc_bridge/include
IPC_LD_LIBRARY_PATH = /opt/ipc/lib

MEX_FILES := $(patsubst src/%.cc,%,$(wildcard src/*.cc))

all: $(MEX_FILES)

%: src/%.cc
	$(MEX) -I./include -I$(IPC_BRIDGE_CPATH) -lstdc++ -L$(IPC_LD_LIBRARY_PATH) -lipc $^ -output bin/$@

clean:
	rm bin/*.mex*
