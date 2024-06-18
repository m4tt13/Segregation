#include <Windows.h>

#include <TlHelp32.h>

#include <cstdio>

#define Bits_32

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

void* Engine_Module;

void* Client_Module;

#include "Delimited_Interface.hpp"

#include "Extended_Interface.hpp"

#include <unordered_map>

#include "Post_Network_Data_Received.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Processor.hpp"

#include "Player_Tick_Received.hpp"

#include "Write_Events.hpp"

#include "On_Render_Start.hpp"

#include "Interpolate.hpp"

#include "Update_Animation.hpp"

#include "Update_Animation_State.hpp"

#include "Compute_Torso_Rotation.hpp"

#include "Restart_Gesture.hpp"

#include "Run_Simulation.hpp"

#include "Setup_Move.hpp"

#include <algorithm>

#include "Finish_Move.hpp"

#include "Fire_Bullets.hpp"

#include "Read_Packets.hpp"

#include "Move.hpp"

#include "Send_Move.hpp"

#include "Packet_Start.hpp"

#include <vector>

#include "Run_Command.hpp"

#include "Copy_Command.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

__int32 __stdcall DllMain(HMODULE This_Module, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
		{
			if (GetModuleHandleW(L"hl2.exe") == nullptr)
			{
				void* Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

				PROCESSENTRY32W Snapshot_Entry;

				Snapshot_Entry.dwSize = sizeof(Snapshot_Entry);

				Traverse_Snapshot_Label:
				{
					if (Process32NextW(Snapshot, &Snapshot_Entry) == 0)
					{
						return 1;
					}

					if (wcscmp(Snapshot_Entry.szExeFile, L"hl2.exe") != 0)
					{
						goto Traverse_Snapshot_Label;
					}
				}

				void* Process = OpenProcess(PROCESS_ALL_ACCESS, 0, Snapshot_Entry.th32ProcessID);

				void* Remote_Path = VirtualAllocEx(Process, nullptr, 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

				wchar_t Local_Path[MAX_PATH];

				GetModuleFileNameW(This_Module, Local_Path, sizeof(Local_Path));

				WriteProcessMemory(Process, Remote_Path, Local_Path, sizeof(Local_Path), nullptr);

				WaitForSingleObject(CreateRemoteThread(Process, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, Remote_Path, 0, nullptr), INFINITE);

				VirtualFreeEx(Process, Remote_Path, 0, MEM_RELEASE);
			}
			else
			{
				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)LoadLibraryW(L"vaudio_speex.dll") + 9776), 1, 195);

				AllocConsole();

				SetConsoleTitleW(L"Segregation");

				_wfreopen(L"CONOUT$", L"w", stdout);

				SetConsoleOutputCP(65001);

				HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

				CONSOLE_FONT_INFOEX Console_Font_Information;

				Console_Font_Information.cbSize = sizeof(CONSOLE_FONT_INFOEX);

				Console_Font_Information.nFont = 0;

				Console_Font_Information.dwFontSize.X = 0;

				Console_Font_Information.dwFontSize.Y = 12;

				Console_Font_Information.FontFamily = FF_DONTCARE;

				Console_Font_Information.FontWeight = FW_NORMAL;

				wcscpy(Console_Font_Information.FaceName, L"Terminal");

				SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

				CONSOLE_CURSOR_INFO Console_Cursor_Information;

				Console_Cursor_Information.bVisible = 0;

				Console_Cursor_Information.dwSize = sizeof(Console_Cursor_Information);

				SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);

				SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

				CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

				GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

				COORD Top_Left =
				{
					0,

					0
				};

				DWORD Characters_Written_Count;

				FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written_Count);

				Engine_Module = GetModuleHandleW(L"engine.dll");

				Client_Module = GetModuleHandleW(L"client.dll");

				_putws(L"[ + ] Delimit Interface");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 626853), 26, 144);

					void* Console_Variables = *(void**)((unsigned __int32)Engine_Module + 10623468);

					using Find_Console_Variable_Type = Interface_Structure*(__thiscall**)(void* Console_Variables, char* Name);

					Interface_Structure* Interface_Allow_Cheats = (*Find_Console_Variable_Type(*(unsigned __int32*)Console_Variables + 52))(Console_Variables, (char*)"sv_cheats");
					
					Interface_Allow_Cheats->Flags &= ~8192;

					Interface_Allow_Cheats->Handler = (void*)Force_Console_Variable_Value;

					Force_Console_Variable_Value((Interface_Structure*)((unsigned __int32)Interface_Allow_Cheats + 24));

					Interface_Structure* Interface_Allow_Lua = (*Find_Console_Variable_Type(*(unsigned __int32*)Console_Variables + 52))(Console_Variables, (char*)"sv_allowcslua");

					Interface_Allow_Lua->Flags &= ~8192;

					Interface_Allow_Lua->Handler = (void*)Force_Console_Variable_Value;

					Force_Console_Variable_Value((Interface_Structure*)((unsigned __int32)Interface_Allow_Lua + 24));
				}

				_putws(L"[ + ] Extend Interface");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Engine_Module + 2477497), 2, 144);

					Implement_Extended_Interface();
				}

				_putws(L"[ + ] Events");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1615966), 1, 0);

					Redirection_Manager::Redirect_Function(Original_Post_Network_Data_Received_Caller, 0, (void*)((unsigned __int32)Client_Module + 2579600), 1, (void*)Redirected_Post_Network_Data_Received);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Engine_Module + 728702), 1, 235);

					void* Event_Listener = (void*)malloc(sizeof(void*));

					void* Event_Listener_Table = malloc(sizeof(void*) * 2);

					*(void**)((unsigned __int32)Event_Listener_Table + 4) = (void*)Event_Processor;

					*(void**)Event_Listener = Event_Listener_Table;

					using Add_Listener_Type = __int8(__thiscall*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

					Add_Listener_Type((unsigned __int32)Engine_Module + 1665200)((void*)((unsigned __int32)Engine_Module + 4321104), Event_Listener, (char*)"player_hurt", nullptr);

					Add_Listener_Type((unsigned __int32)Engine_Module + 1665200)((void*)((unsigned __int32)Engine_Module + 4321104), Event_Listener, (char*)"entity_killed", nullptr);

					*(void**)((unsigned __int32)Client_Module + 7600488) = (void*)Redirected_Player_Tick_Received;

					Redirection_Manager::Redirect_Function(Original_Write_Events_Caller, 0, (void*)((unsigned __int32)Engine_Module + 1671904), 1, (void*)Redirected_Write_Events);

					Redirection_Manager::Redirect_Function(Original_On_Render_Start_Caller, 0, (void*)((unsigned __int32)Client_Module + 2783696), 1, (void*)Redirected_On_Render_Start);
				}

				_putws(L"[ + ] Interpolation");
				{
					Redirection_Manager::Redirect_Function(Original_Interpolate_Caller, 0, (void*)((unsigned __int32)Client_Module + 1541936), 1, (void*)Redirected_Interpolate);
				}

				_putws(L"[ + ] Animations");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 3158245), 6, 144);

					Redirection_Manager::Redirect_Function(Original_Update_Animation_Caller, 1, (void*)((unsigned __int32)Client_Module + 598224), 1, (void*)Redirected_Update_Animation);
					
					Redirection_Manager::Redirect_Function(Original_Update_Animation_State_Caller, 0, (void*)((unsigned __int32)Client_Module + 3158064), 1, (void*)Redirected_Update_Animation_State);

					Redirection_Manager::Redirect_Function(Original_Compute_Torso_Rotation_Caller, 0, (void*)((unsigned __int32)Client_Module + 3216976), 1, (void*)Redirected_Compute_Torso_Rotation);

					unsigned __int8 Maintain_Sequence_Transitions_Bytes[3] = { 194, 16, 0 };

					Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Client_Module + 1543312), sizeof(Maintain_Sequence_Transitions_Bytes), Maintain_Sequence_Transitions_Bytes);

					Redirection_Manager::Redirect_Function(Original_Restart_Gesture_Caller, 2, (void*)((unsigned __int32)Client_Module + 3225632), 1, (void*)Redirected_Restart_Gesture);
				}

				_putws(L"[ + ] Prediction");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 2577719), 9, 144);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 2584428), 1, 235);

					Redirection_Manager::Redirect_Function(Original_Run_Simulation_Caller, 0, (void*)((unsigned __int32)Client_Module + 2582288), 1, (void*)Redirected_Run_Simulation);

					Redirection_Manager::Redirect_Function(Original_Setup_Move_Caller, 2, (void*)((unsigned __int32)Client_Module + 2583648), 1, (void*)Redirected_Setup_Move);

					Redirection_Manager::Redirect_Function(Original_Finish_Move_Caller, 0, (void*)((unsigned __int32)Client_Module + 2578128), 1, (void*)Redirected_Finish_Move);

					Redirection_Manager::Redirect_Function(Original_Fire_Bullets_Caller, 0, (void*)((unsigned __int32)Client_Module + 594128), 1, (void*)Redirected_Fire_Bullets);
				}

				_putws(L"[ + ] Network");
				{
					Redirection_Manager::Redirect_Function(Original_Read_Packets_Caller, 4, (void*)((unsigned __int32)Engine_Module + 715488), 1, (void*)Redirected_Read_Packets);

					Redirection_Manager::Redirect_Function(Original_Move_Caller, 2, (void*)((unsigned __int32)Engine_Module + 714112), 1, (void*)Redirected_Move);

					unsigned __int8 Send_Move_Bytes[5] = { 233, 160, 0, 0, 0 };

					Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Engine_Module + 714460), sizeof(Send_Move_Bytes), Send_Move_Bytes);

					Redirection_Manager::Redirect_Function(Original_Send_Move_Caller, 0, (void*)((unsigned __int32)Engine_Module + 2511392), 1, (void*)Redirected_Send_Move);

					Redirection_Manager::Redirect_Function(Original_Packet_Start_Caller, 0, (void*)((unsigned __int32)Engine_Module + 1985600), 1, (void*)Redirected_Packet_Start);
				}

				_putws(L"[ + ] Input");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 2355285), 3, 144);

					Redirection_Manager::Redirect_Function(Original_Copy_Command_Caller, 0, (void*)((unsigned __int32)Client_Module + 2203456), 1, (void*)Redirected_Copy_Command);
				}

				_putws(L"[ + ] View Effects");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1404398), 55, 144);

					Redirection_Manager::Redirect_Function(Original_Run_Command_Caller, 0, (void*)((unsigned __int32)Client_Module + 2581360), 1, (void*)Redirected_Run_Command);
				}

				_putws(L"[ + ] Crosshair");
				{
					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 2287248), (void*)Redirected_Draw_Crosshair);
				}

				_putws(L"[ + ] Materials");
				{
					Redirection_Manager::Redirect_Function(Original_Precache_Caller, 5, (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 240320), 1, (void*)Redirected_Precache);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 2890427), 1, 235);

					unsigned __int8 Skybox_Bytes[5] = { 144, 49, 192, 235, 117 };

					Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Client_Module + 2882713), sizeof(Skybox_Bytes), Skybox_Bytes);
				}
			}
		}
	}

	return 1;
}