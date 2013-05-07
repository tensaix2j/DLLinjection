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

Run myinject.exe with the following arguments:

	myinject.exe <Process Name to inject> <DLL path to inject>
	You can get the running process name in your task manager or enter cmd tasklist in the command prompt.

example:

	myinject.exe mirc.exe C:\tensaix2j\mydll.dll



