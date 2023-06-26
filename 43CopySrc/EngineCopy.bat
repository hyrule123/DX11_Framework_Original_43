:: *.h 파일 복사(라이브러리 참조용)
xcopy /d /s /y /i /r /exclude:exclude_list.txt ".\Project\Engine\*.h" ".\External\Include\Engine\"

:: *.inl 파일 복사(inline 파일)
xcopy /d /s /y /i /r /exclude:exclude_list.txt ".\Project\Engine\SimpleMath.inl" ".\External\Include\Engine\"

:: 참조용 파일 읽기 전용으로 변경
attrib +r ".\External\Include\Engine\*"

:: *.fx 파일 복사(쉐이더 컴파일 코드)
xcopy /d /s /y /i /r  /exclude:exclude_list.txt ".\Project\Engine\*.fx" ".\OutputFile\bin\content\shader\"
attrib +r ".\OutputFile\bin\content\shader\*"

:: bin/content/ 폴더를 bin_d/content/ 폴더로 복사
xcopy /d /s /y /i /r  /exclude:exclude_list.txt ".\OutputFile\bin\content\*" ".\OutputFile\bin_d\content\"

:: 코드 생성 프로그램 복사
xcopy /d /s /y /i /r  ".\OutputFile\bin\CodeGen.exe" ".\OutputFile\bin_d\"
xcopy /d /s /y /i /r  ".\OutputFile\bin\exeptlist.txt" ".\OutputFile\bin_d\"

::폴더 없을 시 폴더 생성
if not exist .\OutputFile\bin\material ( mkdir .\OutputFile\bin\material )
if not exist .\OutputFile\bin_d\material ( mkdir .\OutputFile\bin_d\material )