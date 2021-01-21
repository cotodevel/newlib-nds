setx DEFAULT_GCC_PATH /c/toolchain_generic/6.2_2016q4/
setx DEFAULT_GCC_PATH_WIN c:/toolchain_generic/6.2_2016q4/

setx TGDS_ENV windows

SET var=%cd%

mkdir c:\toolchain_generic\6.2_2016q4

xcopy /Y /i /s %var%\..\shared\6.2_2016q4 c:\toolchain_generic\6.2_2016q4

setup-x86_64.exe

