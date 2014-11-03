@echo off

echo "Inside check.bat"

if not %my_builder_start%==1 goto :EOF

for /F "tokens=*" %%f in (%config_folder%\%bin_list%) do (
	if not exist "%build_folder%\%%f" (
		set file_missed="%%f"
		goto :fail
	)
)

set email_subject="Successfull result"
goto :EOF

:fail
set fail=1
set build_fail=1
set email_subject="Build failed"
