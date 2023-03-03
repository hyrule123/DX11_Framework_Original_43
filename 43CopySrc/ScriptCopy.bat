xcopy /d /i /s /y /r  /exclude:exclude_list.txt ".\Project\Script\*.h" ".\External\Include\Script\"
attrib +r ".\External\Include\Script\*"