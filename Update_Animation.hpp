float Update_Animation_Time;

__int8 Update_Animation_Type;

void* Original_Update_Animation_Caller;

void __thiscall Redirected_Update_Animation(void* Player)
{
	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7253660);

	float Previous_Current_Time = Global_Variables->Current_Time;

	Global_Variables->Current_Time = Update_Animation_Time;

	float Previous_Frame_Time = Global_Variables->Frame_Time;

	Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick * Update_Animation_Type;

	*(float*)((unsigned __int32)Player + 96) = Update_Animation_Time - Global_Variables->Frame_Time;

	(decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller))(Player);

	Global_Variables->Frame_Time = Previous_Frame_Time;

	Global_Variables->Current_Time = Previous_Current_Time;
}