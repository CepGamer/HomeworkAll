@echo off

echo "Inside rm_tmp.bat"

if "%builder_start%"=="" goto :EOF

if exist %err_file% del %err_file%
if exist %repo_name%\%err_file% del %repo_name%\%err_file%
if exist %email_log% del %email_log%
