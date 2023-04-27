#!/bin/bash
# daemon.sh

monitor_processes() {
    # Start pspy64 in the background, capturing output to a log file
    nohup /usr/local/bin/pspy64 > /var/log/pspy.log 2>&1 &
}


# Check if the monitoring process is already running
if ! pgrep -f "pspy64" > /dev/null; then
  # Start the monitoring process in the background
    monitor_processes &
fi
