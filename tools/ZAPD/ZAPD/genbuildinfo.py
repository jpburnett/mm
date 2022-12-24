#!/usr/bin/python3
import os.path
import argparse
from datetime import datetime
import getpass
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument("--opath", dest="opath", type=str, required=False)
parser.add_argument("--devel", action="store_true")
args = parser.parse_args()

if args.opath:
  ofile = os.path.join(args.opath, "BuildInfo.cpp")
else:
  ofile = "build/ZAPD/BuildInfo.cpp"

with open(ofile, "w+") as buildFile:
    label = subprocess.check_output(["git", "describe", "--always"]).strip().decode("utf-8")
    now = datetime.now()
    if args.devel:
        label += " ~ Development version"
    buildFile.write("extern const char gBuildHash[] = \"" + label + "\";\n")
    #buildFile.write("extern const char gBuildDate[] = \"" + now.strftime("%Y-%m-%d %H:%M:%S") + "\";\n")
