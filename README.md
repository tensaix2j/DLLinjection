

DLL Injection
=============

Sample codes (Refined) to do DLL injection into a running process.
Added function hooking code to overwrite functions in WinSock.dll 
i.e send() ,recv()


How to compile:
---------------
Under MSVC++
Create a simple console based project. Add myinject.cpp, compile myinject.cpp into an executable. 

Create another DLL based project. Add mydll.cpp and hookapi.h. Compile mydll.cpp into a DLL.


How to run:
------------
First run the executable which uses winsock( ws2_32.dll in particular) you want to inject, eg: mirc.exe
You can check the dependency DLL using the depends.exe tool found under MSVC tool.


Run myinject.exe with the following arguments:

	myinject.exe <Process Name to inject> <DLL path to inject>

example:

	myinject.exe mirc.exe C:\tensaix2j\mydll.dll



