/*
	UACODD: Run any program in UAC (say clear is that S**T screen asking a password) mode.
	Copyright 2018-???? LWYS.
	
	THIS IS A NO LICENSE FREE SOFTWARE (NOT FREEWARE).
	If you force me to select a license for this, I say use WTFPL. http://www.wtfpl.net/about/ Here you are.
	NO WARRANTY: WARRANTY OF CODES THAT WROTE BY ANYONE ELSE THAN "LWYS" IS REVERSED ON THEIR OWN. (comfirmed: 95% of code is not
				 wrote by me)
				 I DO NOT SERVE THE GRAMMER PROBLEM IN MY CHINGLISH. DON'T MIND IF YOU MISTAKES ME.
	WARNING: This program is not very protected. If say rules, Firstly™ don't sold, Secondly™ don't release the Program as
			 freeware, Thridly™ ask me for use. If you do not agree, then I will catch you.
	
	Usage: uacodd [program executeable file] [program arugments]
	You shouldn't run this without arugments (kidding)
*/

#include<Windows.h>
#include<string>

// use printf for usage? if false i suggest you use the -mwindows option on the compiler.
BOOL printfInstead = true;

// credits:
// https://blog.csdn.net/gaoxin1076/article/details/7562466
// https://download.csdn.net/download/moonshine99/7533603
// https://blog.csdn.net/immcss/article/details/5304972
// edited.

// Test is UAC enabled or not.
BOOL isUACOpen(){
	// made no problem.
	BOOL is;
	
	// ready reg stuff
	HKEY hKEY = NULL;
	DWORD dwType = REG_DWORD;
	DWORD dwEnableLUA = 0;
	DWORD dwConsentPromptBehaviorAdmin = 0;
	DWORD dwPromptOnSecureDesktop = 0;
	DWORD dwSize = sizeof(DWORD);
	
	// useless(?) status indiactor
	LONG status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE//Microsoft//Windows//CurrentVersion//Policies//System//", 0, KEY_READ, &hKEY);
	LONG status2;
	LONG status3;
	
	// SUCCess? (bad pun)
	if (ERROR_SUCCESS == status)
	{
		
		// if yes then query values.
		status = RegQueryValueEx(hKEY, "EnableLUA", NULL, &dwType, (BYTE*)&dwEnableLUA, &dwSize);
		status2 = RegQueryValueEx(hKEY, "ConsentPromptBehaviorAdmin", NULL, &dwType, (BYTE*)&dwConsentPromptBehaviorAdmin, &dwSize);
		status3 = RegQueryValueEx(hKEY, "PromptOnSecureDesktop", NULL, &dwType, (BYTE*)&dwPromptOnSecureDesktop, &dwSize);
		
		// also success?
		if (ERROR_SUCCESS == status&&ERROR_SUCCESS == status2&&ERROR_SUCCESS == status3)
		{
			// then say true or false.
			is = (dwEnableLUA == 1|| 1 >= dwConsentPromptBehaviorAdmin || 1 >= dwPromptOnSecureDesktop) ? TRUE : FALSE;
		}
		
		// close the useless(again) hive key
		RegCloseKey(hKEY);
	}
	
	// the elder BOOL names "is"(bad name) scrolls. (bad joke)
	return is;
}

// credits:
// https://blog.csdn.net/u013147600/article/details/41681011
// or some other that boost my thinking:
// https://blog.csdn.net/allh45601/article/details/21005155
// https://jpassing.com/2007/12/08/launch-elevated-processes-from-the-command-line/
// https://bbs.csdn.net/topics/391853758
// https://bbs.csdn.net/topics/390684999
// https://bbs.csdn.net/topics/370124427
// etc.
// edited.

// gimmie UAC
void GainAdminPrivileges(LPCSTR strApp,LPCSTR strCmd){
	// create shell execution info first
    SHELLEXECUTEINFO nfo;
	// fill it
    ZeroMemory(&nfo, sizeof(nfo));
	
	// set some unreadable thing
    nfo.lpFile = strApp;
    nfo.cbSize = sizeof(nfo);
    nfo.lpVerb = "runas";
    nfo.fMask = NULL;
    nfo.nShow = SW_SHOWDEFAULT;
    nfo.lpParameters = strCmd;  
	
	// run it
    ShellExecuteEx(&nfo);  
}

// the entrypoint
int main(int argc,LPCSTR* argv){
	// bad if
	if(argc>=2){
		// run uac giver
		GainAdminPrivileges(argv[1],argv[2]);
	}else{	
		if (printfInstead){
			// use printf
			printf(
			"Usage: uacodd [program executeable file] [program arugments]\nYou shouldn't run this without arugments (kidding)\nby LWYS."
			);
		}else{
			// use msgboxes
			MessageBoxA(
				NULL,
				"Usage: uacodd [program executeable file] [program arugments]\nYou shouldn't run this without arugments (kidding)\nby LWYS.",
				"uacodd",
				MB_OK
			);
		}
	}
	
	// yeah doog away
	ExitProcess(0);
	// useless
	return 0;
}