# killkey
Linux kernel module to emergency kill a high load process

Default killkey is the often unused and not accidentially pressed PAUSE/BREAK-key.

# Installation
```
# make
# insmod killkey.ko
```

# Usage
press PAUSE/BREAK-key to kill a high load process. **WARNING**: Can kill ANY high load process, including Xorg/systemd/... but most likely unresponsive firefox/chrome or your IDE.




### Disclaimer
Using utime directly is not a sophisticated method to quantify process load. Better suggestions are welcome.
