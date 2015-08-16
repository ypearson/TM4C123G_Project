# history across invocations
set history save on
set history filename ~/.gdb_history
shell sleep 1
target extended-remote :3333
load
monitor reset init
shell sleep 1
monitor reset init
b main
c
refresh

