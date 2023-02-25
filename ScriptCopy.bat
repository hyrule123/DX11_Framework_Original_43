xcopy /d /i /s /y  /exclude:exclude_list.txt ".\Project\Script\*.h" ".\External\Include\Script"

:: Engine 내부의 파일들을 읽기 전용으로 변경
attrib +r ".\External\Include\Engine\*"