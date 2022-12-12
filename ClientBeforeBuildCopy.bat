::솔루션 파일이 있는 곳에서 시작(시작 지점: 프로젝트 폴더)
cd..
cd..

::lib 헤더 파일 복사
xcopy .\Project\StaticLib\math.h .\External\Include\StaticLib\ /d /s /y /i


::dll 헤더 파일을 복사
xcopy .\Project\DynamicLib\math_dll.h .\External\Include\DynamicLib\ /d /s /y /i

::dll 파일을 복사(debug 파일가 _d같 붙음.)
xcopy .\External\Library\DynamicLib\*.dll .\OutputFile\bin\ /d /s /y /i
xcopy .\External\Library\DynamicLib\*_d.dll .\OutputFile\bin_d\ /d /s /y /i
