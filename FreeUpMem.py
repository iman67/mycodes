#!/usr/bin/python
import time
import os
os.system("sudo sysctl -w vm.drop_caches=3")
time.sleep(10)
os.system("sudo sync && echo 3 | sudo tee /proc/sys/vm/drop_caches")

