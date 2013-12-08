@echo off

set my_builder_start=1
chcp 1252
set config_folder=.builder
set msbuildpath="C:\Program Files (x86)\MSBuild\12.0\Bin"

set PATH=%PATH%;%msbuildpath%;C:\Users\Сергей\Downloads\blat311\full

call %config_folder%\settings.bat
call %config_folder%\cleaner.bat
call %config_folder%\clone_build.bat

call %config_folder%\fail.bat

call %config_folder%\send_mail.bat
call %config_folder%\rm_tmp.bat
