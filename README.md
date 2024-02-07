# Project-0B-S24-matvii0392
In this lab, we continued refreshing the knowledge of programming in C. We continued learning about Linux utilities' implementation.
We also continued learning about system calls and their usage.
This project is Part B of Project 0.
The tool tucp is used to copy files or a group of files.
Tool tucp creates an exact image (copy) of a file found on a disk.
The tucp command requires at least two filenames in its arguments.

1) In case tucp command contains two “file names”, then it copies the contents of the 1st file to the 2nd file.
2) In case 2nd file doesn’t exist, then it first creates a file with the specified name and the content of the first file is copied to it. 
HOWEVER if the second file already exists, then it is simply overwritten without any warning.
3) If the tucp command has one or more arguments specifying source file names and following those arguments, an argument specifying a directory name, then the command copies each source file to the destination directory with the same source file name.
The destination file is created if did not exist, or it is overwritten if it already existed.

For example:
```
tucp Sourcefile Destinationfile

tucp Sourcefile Directory

tucp Sourcefile-1 Sourcefile-2 Sourcefile-3 Sourcefile-n Directory
```