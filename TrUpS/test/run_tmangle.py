#!usr/bin/python
import os

for sect in xrange(1,13):
	for wh in xrange(-2,3):
		cmd = "cmsRun tmangle.py processor="+str(sect)+" wheel="+str(wh)+" > YB"+str(wh)+"_S"+str(sect)+".dat"
		os.system(cmd)
		cmd = "sed -i -e '1,7d' YB"+str(wh)+"_S"+str(sect)+".dat"
		os.system(cmd) 
