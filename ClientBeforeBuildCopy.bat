::�ַ�� ������ �ִ� ������ ����(���� ����: ������Ʈ ����)
cd..
cd..

::lib ��� ���� ����
xcopy .\Project\StaticLib\math.h .\External\Include\StaticLib\ /d /s /y /i


::dll ��� ������ ����
xcopy .\Project\DynamicLib\math_dll.h .\External\Include\DynamicLib\ /d /s /y /i

::dll ������ ����(debug ���ϰ� _d�� ����.)
xcopy .\External\Library\DynamicLib\*.dll .\OutputFile\bin\ /d /s /y /i
xcopy .\External\Library\DynamicLib\*_d.dll .\OutputFile\bin_d\ /d /s /y /i
