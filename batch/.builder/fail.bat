@echo off

if not %my_builder_start%==1 goto :EOF
if %git_fail%==1 goto :fail_git
if %build_fail%==1 goto :fail_build
echo No fail
goto :EOF

:fail_git
set email_message="Git failed, error log is in attachment."
goto :EOF

:fail_build
set email_message="Build failed, error log is in attachment."
goto :EOF
