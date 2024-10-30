void* Original_Move_Caller;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7253660);

	if (*(void**)((unsigned __int32)Client_Module + 7827428) != nullptr)
	{
		Redirected_Read_Packets(Final);

		Global_Variables->Frame_Time = 0;

		using Render_Start_Type = void(__cdecl*)();

		Render_Start_Type((unsigned __int32)Client_Module + 1973072)();
	}

	(decltype(&Redirected_Move)(Original_Move_Caller))(Unknown_Parameter, Final);

	using Update_Animations_Type = void(__cdecl*)();

	Update_Animations_Type((unsigned __int32)Client_Module + 1653168)();

	Update_Animation_Time = Global_Variables->Current_Time;

	Update_Animation_Type = 1;

	Update_Animations_Type((unsigned __int32)Client_Module + 1653168)();

	Update_Animation_Type = 0;
}