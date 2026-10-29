# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: unreg.exe

# Update the object file if necessary

unreg.obj: unreg.c
    $(cc) $(cdebug) $(cflags) $(cvars) unreg.c

# Update the executable file if necessary.

unreg.exe: unreg.obj
    $(link) $(linkdebug) $(guiflags) -out:unreg.exe unreg.obj $(guilibs) advapi32.lib
