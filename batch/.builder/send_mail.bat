@echo off

if not %my_builder_start%==1 goto :EOF

if %fail%==0 goto :zero_fail 

blat -body " " -tf %email_list% -server %mail_serv% -f %mail_addr% -subject "Building %proj_name%. %email_subject%." -atf %err_file%>%email_log%

goto :EOF

:zero_fail
pause
blat -body " " -tf %email_list% -server %mail_serv% -f %mail_addr% -subject "Building %proj_name%. %email_subject%.">%email_log%
