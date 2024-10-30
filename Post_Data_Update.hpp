void* Original_Post_Data_Update_Caller;

void __thiscall Redirected_Post_Data_Update(void* Entity, void* Unknown_Parameter_1)
{
	float Simulation_Time = *(float*)((unsigned __int32)Entity + 96);
	
	float Previous_Simulation_Time = *(float*)((unsigned __int32)Entity + 100);
	
	if (Simulation_Time != Previous_Simulation_Time)
	{
		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7253660);
		
		Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 72)];
		
		float* Networked_Origin = (float*)((unsigned __int32)Entity + 816);
		
		float* Previous_Origin = (float*)((unsigned __int32)Entity + 624);
		
		Player_Data->Breaks_Lag_Compensation = __builtin_powf(Networked_Origin[0] - Previous_Origin[0], 2) + __builtin_powf(Networked_Origin[1] - Previous_Origin[1], 2) + __builtin_powf(Networked_Origin[2] - Previous_Origin[2], 2) > 4096;
		
		Player_Data->Simulation_Ticks = (Simulation_Time - Previous_Simulation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;
		
		Player_Data->Last_Update_Tick_Number = Global_Variables->Tick_Number;
	}
	
	(decltype(&Redirected_Post_Data_Update)(Original_Post_Data_Update_Caller))(Entity, Unknown_Parameter_1);
}