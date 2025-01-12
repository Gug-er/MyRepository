echo off
rem this file is part of installer for Notepad++
rem Copyright (C)2006 Don HO <don.h@free.fr>
rem 
rem This program is free software; you can redistribute it and/or
rem modify it under the terms of the GNU General Public License
rem as published by the Free Software Foundation; either
rem version 2 of the License, or (at your option) any later version.
rem 
rem This program is distributed in the hope that it will be useful,
rem but WITHOUT ANY WARRANTY; without even the implied warranty of
rem MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
rem GNU General Public License for more details.
rem 
rem You should have received a copy of the GNU General Public License
rem along with this program; if not, write to the Free Software
rem Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

echo on

del /F /Q .\build\*.*

rem Notepad++ minimalist package
del /F /S /Q .\zipped.package.release\minimalist\*.*
copy /Y ..\bin\license.txt .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\readme.txt .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\change.log .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\src\config.model.xml .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\src\langs.model.xml .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\src\stylers.model.xml .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\src\contextMenu.xml .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\src\shortcuts.xml .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\doLocalConf.xml .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\"notepad++.exe" .\minimalist\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\SciLexer.dll .\minimalist\
If ErrorLevel 1 PAUSE


rem Notepad++ Unicode package
del /F /S /Q .\zipped.package.release\unicode\*.*
copy /Y ..\bin\license.txt .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\readme.txt .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\change.log .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\src\config.model.xml .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\src\langs.model.xml .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\src\stylers.model.xml .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\src\contextMenu.xml .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\src\shortcuts.xml .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
xcopy /Y /S ..\bin\user.manual .\zipped.package.release\unicode\user.manual
If ErrorLevel 1 PAUSE
copy /Y ..\bin\doLocalConf.xml .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\"notepad++.exe" .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\SciLexer.dll .\zipped.package.release\unicode\
If ErrorLevel 1 PAUSE
copy /Y "..\bin\plugins\*.*" .\zipped.package.release\unicode\plugins\
If ErrorLevel 1 PAUSE
xcopy /Y /E /S "..\bin\plugins\doc" .\zipped.package.release\unicode\plugins\doc
If ErrorLevel 1 PAUSE
copy /Y "..\bin\plugins\Config\tidy\*.*" .\zipped.package.release\unicode\plugins\Config\tidy\
If ErrorLevel 1 PAUSE
copy /Y "..\bin\updater\gpup.exe" .\zipped.package.release\unicode\updater\
If ErrorLevel 1 PAUSE

copy /Y ".\nativeLang\*.xml" .\zipped.package.release\unicode\localization\
If ErrorLevel 1 PAUSE
copy /Y ".\APIs\*.xml" .\zipped.package.release\unicode\plugins\APIs\
If ErrorLevel 1 PAUSE
copy /Y ".\themes\*.xml" .\zipped.package.release\unicode\themes\
If ErrorLevel 1 PAUSE

rem Notepad++ ANSI package
del /F /S /Q .\zipped.package.release\ansi\npp.pdb
del /F /S /Q .\zipped.package.release\ansi\config.xml
del /F /S /Q .\zipped.package.release\ansi\langs.xml
del /F /S /Q .\zipped.package.release\ansi\stylers.xml
del /F /S /Q .\zipped.package.release\ansi\session.xml
copy /Y ..\bin\SciLexer.dll .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\license.txt .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\readme.txt .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
xcopy /Y /S ..\bin\user.manual .\zipped.package.release\ansi\user.manual
If ErrorLevel 1 PAUSE
copy /Y ..\bin\change.log .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y ..\src\config.model.xml .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y ..\src\langs.model.xml .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y ..\src\stylers.model.xml .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y ..\src\contextMenu.xml .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y ..\src\shortcuts.xml .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y ..\bin\doLocalConf.xml .\zipped.package.release\ansi\
If ErrorLevel 1 PAUSE
copy /Y "..\bin\plugins\Config\tidy\*.*" .\zipped.package.release\ansi\plugins\Config\tidy\
If ErrorLevel 1 PAUSE
copy /Y ".\APIs\*.xml" .\zipped.package.release\ansi\plugins\APIs\
If ErrorLevel 1 PAUSE
copy /Y ".\themes\*.xml" .\zipped.package.release\ansi\themes\
If ErrorLevel 1 PAUSE


"C:\Program Files\7-Zip\7z.exe" a -r .\build\npp.bin.minimalist.7z .\minimalist\*
If ErrorLevel 1 PAUSE
"C:\Program Files\7-Zip\7z.exe" a -tzip -r .\build\npp.bin.zip .\zipped.package.release\*
If ErrorLevel 1 PAUSE
"C:\Program Files\7-Zip\7z.exe" a -r .\build\npp.bin.7z .\zipped.package.release\*
If ErrorLevel 1 PAUSE
"C:\Program Files (x86)\NSIS\makensis.exe" nppSetup.nsi


@echo off

setlocal enableDelayedExpansion 

cd .\build\

for %%a in (npp.*.Installer.exe) do (
  rem echo a = %%a
  set nppInstallerVar=%%a
  set zipvar=!nppInstallerVar:Installer.exe=bin.zip!
  set 7zvar=!nppInstallerVar:Installer.exe=bin.7z!
  set 7zvarMin=!nppInstallerVar:Installer.exe=bin.minimalist.7z!
  rem set md5var=!nppInstallerVar:Installer.exe=release.md5!
)
ren npp.bin.zip !zipvar!
ren npp.bin.7z !7zvar!
ren npp.bin.minimalist.7z !7zvarMin!
rem ..\externalTools\md5.exe -o!md5var! !nppInstallerVar! !zipvar! !7zvar!

cd ..

endlocal
