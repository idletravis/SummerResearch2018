import sys
import os


def locateDir():
    """locateDir finds the directory path of CRA-Python within the directory it was downloaded to"""
    #  vv   locates all file paths that include the CRA-Python directory and outputs to a file to read from later
    os.system("find $HOME | grep SummerResearch2018/CRA-Python > deleteThis.txt")
    dirPath = " "
    try:
        file = open("deleteThis.txt", "r+", 1)  # attempts to read from the output of the directory search
        dirPath = file.readline(256)
        file.close()
        os.remove("./deleteThis.txt")
    # except(FileNotFoundError, FileExistsError, ReferenceError):
    #    print("Unable to open deleteThis.txt")
    finally:
        return dirPath[:dirPath.__len__()-1]  # get rid of newline character returned by readline


def askFile(path):
    """asks the user for a relative filepath to an object file within the CRA-Python directory to be disassembled"""
    print("Enter the relative filepath for the object file (.obj, .o) to be disassembled. ",
          "(Must be within the CRA-Python directory or any subdirectories) \n", path, "")
    path += input()
    return path


def objDumpCommand(path):
    """prepares the Linux objdump command based on that object file, then returns the command as a string"""
    outfile = path[:path.find(".")] + "-dsmbl.txt"
    print("Output of disassembly written to file within the parent directory of selected file. Output file name: ",
          outfile)
    command = "objdump -d -M intel " + path + ">" + outfile
    return command


def findLEA(path):
    """findLEA searches the disassembled file for LEA instructions and outputs each line they're found in to a new file ending in -LEA.txt. This function is
     intended to show the memory locations of buffers to potentially overflow"""
    print("To search for LEA instructions, input a relative filepath for a -dsmbl.txt: \n", path)
    path += input()
    # this is the filepath of the LEA file to be created (will be written over if it already exists
    # if it exists,that would mean the -dsmbl file was given as input in last execution
    leaFP = path[:path.find("-dsmbl")] + "-LEA.txt"
    with open(path, 'r', 1) as dsmblFile:  # opens file in the mode that overwrites the file in read/write format
        with open(leaFP, 'w+', 1) as leaFile:
            for line in dsmblFile:  # for each line read from the leaFile
                instruction = line[line.find("lea"):]
                if line.find("lea") != -1 and line.find("leave") == -1:
                    leaFile.write("Found LEA instruction:   " + instruction + "\n")  # write formatted output to leaFile
    print("The LEA instructions found in " + path + " have been written to:    " + leaFP)


os.system(""+objDumpCommand(askFile(locateDir())))
findLEA(locateDir())

# python $HOME/Desktop/ROPgadget-master/ROPgadget.py --binary $HOME/Desktop/ROPgadget-master
# /test-suite-binaries/elf-Linux-x86 >> $HOME/Desktop/ROPgadget-master/elf-Linux-x86-Output.txt
# ^^ this is command to build the chain for me, with filePath being the designated file to use as the binary
# automated chain generation is random and not targeted at all.
# refer to http://shell-storm.org/blog/Return-Oriented-Programming-and-ROPgadget-tool/ for an example
# still need to write my own outline for how I want the program to run and then link the ROP chain "manually"
# first try manually to do /bin/sh exploit then attempt automation of finding and linking ROP chain
# need to confirm whether push operations to store target memory addresses is necessary for linking
