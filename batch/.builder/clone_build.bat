@echo off

if not %my_builder_start%==1 goto :EOF

git clone https://github.com/CepGamer/%repo_name%.git>nul 2>%err_file%
if errorlevel 1 goto :fail_git

MSBuild.exe %repo_name%/%proj_name%.sln>%err_file%
if not %ERRORLEVEL%==0  goto :fail_build

set email_message="Build successfull"
goto :EOF

:fail_git
set git_fail=1
set fail=1
goto :EOF

:fail_build
set build_fail=1
set fail=1
goto :EOF
