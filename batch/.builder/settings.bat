@echo off

if not %my_builder_start%==1 goto :EOF

set repo_name=Geometry271
set proj_name=MainApp

set fail=0
set git_fail=0
set build_fail=0
set err_file="error.log"

set email_message=""
set email_sender=
set email_subject=""
set email_list=mail_list.txt
set email_log=""

set bin_list=bin.txt

set mail_addr="lol15.ivanov@mail.ru"
set mail_pass="115lalala"
set mail_serv=smtp.mail.ru
