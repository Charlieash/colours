set APPDATA=%~dp0settings
mkdir %APPDATA%
START /D"%~dp0" codeblocks.exe %*  