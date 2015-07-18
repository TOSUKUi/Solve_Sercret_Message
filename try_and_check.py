#!/usr/bin/env python

import sys
import commands


port = commands.getoutput("nmap ")
args = sys.argv

print args[2]
