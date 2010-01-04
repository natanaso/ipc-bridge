function ret = msg_test(name)
fcn = eval(sprintf('@%s', name));

disp('testing empty message generation');
empty = fcn('empty');
disp('testing publisher connect');
pid = fcn('connect', 'publisher', 'p', 'msg');
if pid < 0
  disp(sprintf('%s: failed to connect publisher', name));
  ret = false
  return;
end
disp('testing subscriber connect');
sid = fcn('connect', 'subscriber', 's', 'msg');
if sid < 0
  disp(sprintf('%s: failed to connect subscriber', name));
  ret = false;
  return
end
disp('testing send');
if fcn('send', pid, empty) ~= 0
  disp(sprintf('%s: failed to send', name));
  ret = false;
  return
end
pause(0.1)
disp('testing read');
ret = fcn('read', sid, 100);
if ~isempty(comp_struct(ret{1}, empty))
  disp(sprintf('%s: read did not get expected message', ...
               name));
  ret = false;
  return
end
disp('testing subscriber disconnect');
if fcn('disconnect', sid) ~= 0
  disp(sprintf('%s: failed to disconnect subscriber', name));
  ret = false;
  return
end
disp('testing publisher disconnect');
if fcn('disconnect', pid) ~= 0
  disp(sprintf('%s: failed to disconnect publisher', name));
  ret = false;
  return
end
disp('testing memory dealloc');
clear fcn;
disp(sprintf('%s: test passed', name));

ret = true;
