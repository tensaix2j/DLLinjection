// myinject.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <tlhelp32.h>  
#include <iostream.h>
#include <shlwapi.h>  


//We will be writing our own little function called CreateRemoteThreadInject 
BOOL CreateRemoteThreadInject(DWORD PID, const char * dll)  {  
	
	//Declare the handle of the process. 
	HANDLE Process; 

	//Declare the memory we will be allocating 
	LPVOID Memory; 

	//Declare LoadLibrary 
	LPVOID LoadLibrary;  

   //If there's no process ID we return false. 
   if(!PID) { 
		return false; 
   } 
    
  //Open the process with read , write and execute priviledges 
   Process = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_VM_WRITE|PROCESS_VM_OPERATION, FALSE, PID);  
  
   //Get the address of LoadLibraryA 
   LoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");  
  
   // Allocate space in the process for our DLL  
   Memory = (LPVOID)VirtualAllocEx(Process, NULL, strlen(dll)+1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);  
  
   // Write the string name of our DLL in the memory allocated  
   WriteProcessMemory(Process, (LPVOID)Memory, (void *)dll, strlen(dll)+1, NULL);  
  
   // Load our DLL, by forcing the process to call LoadLibrary("mydll.dll");  
   CreateRemoteThread(Process, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibrary, (LPVOID)Memory, NULL, NULL);  
  
   //Let the program regain control of itself 
   CloseHandle(Process); 


  //Lets free the memory we are not using anymore. 
   VirtualFreeEx(Process , (LPVOID)Memory , 0, MEM_RELEASE); 

   return true; 
} 


DWORD GetProcessId(IN PCHAR szExeName) 
{ 
    DWORD dwRet = 0; 
    DWORD dwCount = 0; 

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 

    if (hSnapshot != INVALID_HANDLE_VALUE) 
    { 
        PROCESSENTRY32 pe = {0}; 
        pe.dwSize = sizeof(PROCESSENTRY32); 

        BOOL bRet = Process32First(hSnapshot, &pe); 

        while (bRet) 
        { 
            if (!_stricmp(pe.szExeFile, szExeName)) 
            { 
                dwCount++; 
                dwRet = pe.th32ProcessID; 
            } 
            bRet = Process32Next(hSnapshot, &pe); 
        } 

        if (dwCount > 1) 
            dwRet = 0xFFFFFFFF; 

        CloseHandle(hSnapshot); 
    } 

    return dwRet; 
} 


//----------------------------
int main(int argc, char* argv[])
{
	// Declare our dll variable 
    char dll[MAX_PATH]; 

	if ( argc != 3 ) {
		cout << "Usage :" << argv[0] << " <PROCESS NAME> <DLL FULL PATH>" << endl;
		exit(1);
	}
	
    // Get the full path of our .dll 
	GetFullPathName( argv[2] , MAX_PATH, dll , NULL);  
	
	// Get PID of notepad.exe		
	DWORD ID = GetProcessId(argv[1]); 
    
	if (!CreateRemoteThreadInject(ID, dll)) {
		
        //If CreateRemoteThreadInject Returned true 
        cout << "Injection failed!" << endl ; 
        exit(1); 
         

    } else {
		
        //If CreateRemoteThreadInject Returned true 
        cout << "Injection of" << argv[2] << " into " << argv[1]  << " is successful!" << endl; 
        exit(1); 
    
	} 
    
	return 0;
}
