float Animation_Time;

float Update_Animation_Angles[2];

void* Original_Update_Animation_Caller;

void __thiscall Redirected_Update_Animation(void* Player)
{
	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

	float Previous_Current_Time = Global_Variables->Current_Time;

	Global_Variables->Current_Time = Animation_Time;

	float Previous_Frame_Time = Global_Variables->Frame_Time;

	Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick * (*(void**)((unsigned __int32)__builtin_frame_address(0) + 16) != (void*)604538373);

	*(float*)((unsigned __int32)Player + 96) = Animation_Time - Global_Variables->Frame_Time;

	if (Player == *(void**)607867332)
	{
		Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int32)Player + 4124), sizeof(Update_Animation_Angles), Update_Animation_Angles);
	}

	(decltype(&Redirected_Update_Animation)(Original_Update_Animation_Caller))(Player);

	Global_Variables->Frame_Time = Previous_Frame_Time;

	Global_Variables->Current_Time = Previous_Current_Time;
}