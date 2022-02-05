#1. Date command with different formats
# date -d "2003-11-12 07:10:25"
#2. what is the difference between / and /root
# '/' is the root of the entire system. All directories stem from it. '/root' is the root user's home directory
#3. show current processes working  ps command
#   PID TTY          TIME CMD
# 11523 pts/4    00:00:00 bash
# 11524 pts/4    00:00:00 bash
# 13959 pts/4    00:00:00 ps
#4. show a tree of the processes working in your system pstree command
# systemd─┬─acpid
#         ├─2*[agetty]
#         ├─amazon-ssm-agen─┬─ssm-agent-worke───6*[{ssm-agent-worke}]
#         │                 └─7*[{amazon-ssm-agen}]
#         ├─anacron───run-parts─┬─awk
#         │                     └─yum-cron
#         ├─atd
#         ├─auditd───{auditd}
#         ├─chronyd
#         ├─containerd───8*[{containerd}]
#         ├─crond
#         ├─dbus-daemon
#         ├─2*[dhclient]
#         ├─dockerd───6*[{dockerd}]
#         ├─gssproxy───5*[{gssproxy}]
#         ├─lsmd
#         ├─lvmetad
#         ├─master─┬─pickup
#         │        └─qmgr
#         ├─rngd
#         ├─rpcbind
#         ├─rsyslogd───2*[{rsyslogd}]
#         ├─sshd─┬─sshd───sshd───bash───node─┬─node─┬─node───6*[{node}]
#         │      │                           │      └─10*[{node}]
#         │      │                           ├─tmux
#         │      │                           └─11*[{node}]
#         │      └─sshd───sshd───bash───node───10*[{node}]
#         ├─systemd-journal
#         ├─systemd-logind
#         ├─systemd-udevd
#         └─tmux─┬─bash───bash───shell───shell
#               └─bash───bash───pstree
#5. exit command
# exit



#show the current user name and user-id
whoami
#print on the screen "Current listing under / "
echo 'Current listing under /'
#list all directories under /ls /
ls /
#print on the screen "Current listing under the user home"
echo 'Current listing under the user home'
#list directories and files under your user home directory
ls /usr
#save the listing under your user home directory into a file named "User_home_files"
touch User_home_files
ls /usr >> User_home_files
#sort and print the content of the "User_home_files"
sort User_home_files
#list all currently running processes
p
#save all currently running processes under a file named "User_processes"
touch User_processes
ps >> User_processes
#Change the permission on "User_processes" file to be read-only for user, groups and other.
chmod 444 User_processes