print("Pre build invoked")

mypath = "."

from os import listdir
from os.path import isfile, join
import subprocess
import os
import time

files = [f for f in listdir(mypath) if isfile(join(mypath, f))]

for file in files:
    if ".png" in file:
        print("Processing: " + file)
        filename_no_extension = file[:file.index(".png")]
        cmd = "convert " + file + " rgba:" + filename_no_extension + ".raw"
        os.system(cmd)

assembly_counter = 0

for file in files:
    if ".raw" in file:
        assembly_counter += 1
        filename_no_extension = file[:file.index(".raw")]
        print("Processing: " + file)
        print(filename_no_extension)
        file_handle = open("assembly" + str(assembly_counter), "w")
        assembly = ".data\n.global " + filename_no_extension + \
                   "_start\n" + filename_no_extension + "_start:\n\t.incbin " + "\"" + \
                   file + "\"\n"
        file_handle.write(assembly)
        file_handle.close()
        cmd = "cat assembly" + str(assembly_counter)  + " | psp-as -o " + filename_no_extension + ".o"
        print("cmd is: " + cmd)
        os.system(cmd)
