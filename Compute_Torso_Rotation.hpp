void* Original_Compute_Torso_Rotation_Caller;

__int8 Compute_Custom_Torso_Rotation(void* Animation_State, void* Studio_Header)
{
	if (Interface_Bruteforce.Integer == 1)
	{
		if (*(void**)Animation_State == (void*)((unsigned __int32)Client_Module + 6164288))
		{
			void* Entity = *(void**)((unsigned __int32)Animation_State + 248);

			if (Entity != *(void**)((unsigned __int32)Client_Module + 7603940))
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 80)];

				if (Player_Data->Priority != -2)
				{
					using Set_Pose_Parameter_Type = float(__thiscall*)(void* Entity, void* Studio_Header, __int32 Parameter, float Value);

					if (*(float*)((unsigned __int32)Animation_State + 120) == 180)
					{
						Set_Pose_Parameter_Type((unsigned __int32)Client_Module + 1562352)(Entity, Studio_Header, *(__int32*)((unsigned __int32)Animation_State + 60), Player_Data->Switch_X == 0 ? 90 : -90);
					}

					if (Player_Data->Memory_Tolerance == 0)
					{
						*(float*)((unsigned __int32)Animation_State + 36) = *(float*)((unsigned __int32)Animation_State + 116) - Bruteforce_Angles[Player_Data->Shots_Fired];
					}
					else
					{
						*(float*)((unsigned __int32)Animation_State + 36) = *(float*)((unsigned __int32)Animation_State + 116) - Player_Data->Memorized_Y;
					}

					Set_Pose_Parameter_Type((unsigned __int32)Client_Module + 1562352)(Entity, Studio_Header, *(__int32*)((unsigned __int32)Animation_State + 56), __builtin_remainderf(*(float*)((unsigned __int32)Animation_State + 116) - *(float*)((unsigned __int32)Animation_State + 36), 360));

					return 1;
				}
			}
		}
	}
	
	return 0;
}

void __thiscall Redirected_Compute_Torso_Rotation(void* Animation_State, void* Studio_Header)
{
	if (Compute_Custom_Torso_Rotation(Animation_State, Studio_Header) == 0)
	{
		(decltype(&Redirected_Compute_Torso_Rotation)(Original_Compute_Torso_Rotation_Caller))(Animation_State, Studio_Header);
	}
}