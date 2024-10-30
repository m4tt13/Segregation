float Update_Animation_Angles[2];

void* Original_Update_Animation_State_Caller;

void __thiscall Redirected_Update_Animation_State(void* Animation_State, float Eye_Yaw, float Eye_Pitch)
{
	if (*(void**)((unsigned __int32)Animation_State + 248) == *(void**)((unsigned __int32)Client_Module + 7827428))
	{
		Eye_Pitch = Update_Animation_Angles[0];

		Eye_Yaw = Update_Animation_Angles[1];
	}

	(decltype(&Redirected_Update_Animation_State)(Original_Update_Animation_State_Caller))(Animation_State, Eye_Yaw, Eye_Pitch);
}