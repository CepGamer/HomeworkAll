@echo off

if not %my_builder_start%==1 goto :EOF
if exist %repo_name% RD /S /Q %repo_name%
