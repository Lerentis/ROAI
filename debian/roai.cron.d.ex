#
# Regular cron jobs for the roai package
#
0 4	* * *	root	[ -x /usr/bin/roai_maintenance ] && /usr/bin/roai_maintenance
