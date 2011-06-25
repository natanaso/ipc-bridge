classdef ipc_ros < handle
    properties;
        bridge
        name
        mode
        pid
        connected
    end

    methods;
        function obj = ipc_ros(package_, type_, name_, mode_)
            [a, p] = system(sprintf('rospack find %s', package_));
            addpath(strcat(p, '/bin'));

            obj.bridge = str2func(type_);
            try
                msg = obj.bridge('empty');
            catch
                error(sprintf('ipc_ros (%s): failed to construct bridge', type_));
                return;
            end

            obj.name = name_;
            if strcmp('publisher', mode_)
                obj.mode = 'publisher';
            elseif strcmp('subscriber', mode_)
                obj.mode = 'subscriber';
            else
                error('ipc_ros (%s): publisher or subscriber required', obj.name);
                return;
            end

            obj.connected = false;
            obj.connect();
        end

        function connect(obj)
            if ~obj.connected
                obj.pid = obj.bridge('connect', obj.mode, obj.name, obj.name);
            end

            if obj.pid == -1
                error('ipc_ros (%s): failed to connect', obj.name);
            else
                obj.connected = true;
            end
        end

        function disconnect(obj)
            if obj.connected
                obj.bridge('disconnect', obj.pid);
            end
            obj.connected = false;
            obj.pid = [];
        end

        function msg = read(obj, varargin)
            timeout = 10;
            blocking = true;
            if length(varargin) == 1
                timeout = varargin{1};
                blocking = true;
            elseif length(varargin) == 2
                timeout = varargin{1};
                blocking = varargin{2};
            end

            if obj.connected
                msg = obj.bridge('read', obj.pid, timeout);
                if blocking
                    while isempty(msg)
                        msg = obj.bridge('read', obj.pid, timeout);
                    end
                end
            end
        end

        function msg = empty(obj)
            obj.bridge('empty');
        end

        function send(obj, msg)
            if ~strcmp(obj.mode, 'publisher')
                error('ipc_ros (%s): failed to send message - wrong mode', obj.name);
                return;
            elseif ~obj.connected
                error('ipc_ros (%s): failed to send message - not connected', obj.name);
                return;
            end

            obj.bridge('send', obj.pid, msg);
        end
    end
end
