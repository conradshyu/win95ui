# Programming the Windows 95 User Interface

This repository contains the companion-disc source code and supporting files for
Nancy Winnick Cluts's *Programming the Windows 95 User Interface* (1995). The
examples demonstrate the Win32 controls and shell interfaces available during
the Windows 95 era. They are historical teaching samples, not a modern,
cross-platform application or a single buildable product.

## Repository contents

- `CHAPTER NN\` contains the examples, project files, resources, sample data,
  and (for some examples) prebuilt programs for that chapter.
- `code\` contains copies of the `readme.txt` files for a subset of the
  examples; the corresponding source projects are in the chapter directories.
- `readme.txt` is the original companion-disc installation and troubleshooting
  guide. `setup.exe`, `setup.ini`, and `setup.txt` are files for the original
  installer; the setup configuration names `C:\Cluts` as its install
  directory.
- `LICENSE` is included at the repository root. Consult it and the copyright
  and attribution notices retained in the sample files when using or
  redistributing this material.

The archive has chapter directories for 01–07, 09, and 11–14; chapters 08 and
10 are not present in this copy.

## Chapter guide

| Directory | Examples and topics |
| --- | --- |
| `CHAPTER 01` | Status bars and toolbars. Includes Win32 samples `status` and `toolbar`, plus MFC counterparts `MFCSTATUS` and `mfctool`. |
| `CHAPTER 02` | Common controls: animation, progress indicators, sliders/trackbars, and up-down (spin) controls. Includes Win32 and MFC examples such as `animat`, `progress`, `slider`, `updown`, `mfcanim`, `mfcprog`, `mfcspin`, and `mfctrack`. |
| `CHAPTER 03` | List-view and tree-view controls, with Win32 (`listview`, `treeview`) and MFC (`mfclist`, `mfctree`) samples. |
| `CHAPTER 04` | Property sheets and wizard-style multi-page dialogs (`props`, `wizard`). |
| `CHAPTER 05` | A rich-edit control example (`riched`), with sample text files. |
| `CHAPTER 06` | Common dialogs (`cmndlg32`), including file open/save, font and color selection, find/replace, printing, and dialog hooks/templates. |
| `CHAPTER 07` | A Chicago/Windows 95-style sample application for browsing and editing sample listings (`chicoapp`, `mfcexp`), bringing together controls such as toolbars, status bars, list/tree views, dialogs, and property sheets. |
| `CHAPTER 09` | An MFC sample for creating and resolving shell shortcuts (`shortcut`). |
| `CHAPTER 11` | Examples of Windows shell library functions (`shellfun`). |
| `CHAPTER 12` | An MFC file-viewer shell extension (`mfcview`), with a separate unregister utility under `mfcview\unreg`. |
| `CHAPTER 13` | Shell extensions: context menus (`ctxtmenu`), property pages (`propext`), and the combined `shellext` sample, which also demonstrates icon-handler and copy-hook extensions. Each extension project has an `unreg` utility. |
| `CHAPTER 14` | Shell namespace enumeration and display. `enumdesk` uses `IShellFolder` with tree/list views; `mfcenum` is the MFC counterpart. |

Most chapter directories contain standalone projects rather than one shared
solution. Project files include legacy `.MAK`/`.VCP` files along with source
(`.c`, `.cpp`, `.h`), resources (`.rc`, `.rc2`, bitmaps, icons, and related
files), sample data, and some prebuilt `.exe`/`.dll` binaries.

## Building and running

These are 32-bit Windows samples written for the Windows 95-era Win32 SDK and
Visual C++/MFC toolchain. The original companion-disc notes specify the Win32
SDK as a build requirement; the shell-extension sample specifically documents
Visual C++ 2.x. A compatible period toolchain may be needed because these
projects predate current Visual Studio project formats and Windows SDKs.

To build an individual project, open its project file in a compatible Visual
C++ environment, or use the project's `.MAK` file with NMAKE from that
project's directory. The bundled MFC project notes give commands in this form:

```bat
nmake /f PROJECT.MAK CFG="Win32 Debug"
nmake /f PROJECT.MAK CFG="Win32 Release"
```

Replace `PROJECT.MAK` with the makefile name in the sample directory. Not every
sample has an MFC readme or both configurations, so check that project's files
and local notes first. There is no repository-wide build script.

The included executables and DLLs are historical builds and may not run on
current Windows versions. Prefer inspecting or rebuilding the source in a
compatible, isolated environment. In particular, Chapters 12–13 include shell
extensions and unregister utilities that interact with Windows shell
registration. Follow the sample-specific instructions and unregister an
extension when finished; the original notes warn that unregistering removes
registry entries but does not delete the extension DLL.

## Original companion-disc notes

The root `readme.txt` records these known issues:

- Some MFC samples may fail in `Win32 Release` with undeclared
  `TCM_GETBKCOLOR`/`TCM_SETBKCOLOR` identifiers or a precompiled-header error.
  The documented workaround is to select `Win32 Debug` and rebuild.
- `.REG` files do not support line continuations. Long lines split across
  printed pages in the book must remain single lines in the actual file.
- Windows 95 may use the first registered file viewer for a file type rather
  than the most recently registered one. Unregister existing viewers before
  registering a different one.
- The unregister utilities for the Chapter 12 viewer and Chapter 13 extensions
  remove registry entries but leave their DLLs on disk; those files must be
  removed separately if no longer needed.

See each sample's `readme.txt` for project-specific details. The original
companion-disc documentation credits Nancy Winnick Cluts and retains the
copyright notices present in individual examples.
