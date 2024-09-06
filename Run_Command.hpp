void* Original_Run_Command_Caller;

void __thiscall Redirected_Run_Command(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	float View_Angles[3];

	using Get_View_Angles_Type = void(__thiscall*)(void* Engine, float* View_Angles);

	Get_View_Angles_Type((unsigned __int32)Engine_Module + 614944)((void*)((unsigned __int32)Engine_Module + 4056616), View_Angles);

	(decltype(&Redirected_Run_Command)(Original_Run_Command_Caller))(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);

	using Set_View_Angles_Type = void(__thiscall*)(void* Engine, float* View_Angles);

	Set_View_Angles_Type((unsigned __int32)Engine_Module + 617104)((void*)((unsigned __int32)Engine_Module + 4056616), View_Angles);
}