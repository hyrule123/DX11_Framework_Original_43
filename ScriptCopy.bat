xcopy /d /i /s /y /r  /exclude:exclude_list.txt ".\Project\Script\*.h" ".\External\Include\Script\"
attrib +r ".\External\Include\Script\*"

xcopy /d /s /y /i /r  /exclude:exclude_list.txt ".\OutputFile\bin\CodeGen.exe" ".\OutputFile\bin_d\"
xcopy /d /s /y /i /r  /exclude:exclude_list.txt ".\OutputFile\bin\exeptlist.txt" ".\OutputFile\bin_d\"