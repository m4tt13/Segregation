SafetyHookInline Original_Move_Caller{};

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int64)Client_Module + 8690824);

	if (*(void**)((unsigned __int64)Client_Module + 9394464) != nullptr)
	{
		Redirected_Read_Packets(Final);

		Global_Variables->Frame_Time = 0;

		using Render_Start_Type = void(*)();

		Render_Start_Type((unsigned __int64)Client_Module + 2057056)();
	}

	Original_Move_Caller.call<void>(Unknown_Parameter, Final);

	using Update_Animations_Type = void(*)();

	Update_Animations_Type((unsigned __int64)Client_Module + 1682880)();

	Update_Animation_Time = Global_Variables->Current_Time;

	Update_Animation_Type = 1;

	Update_Animations_Type((unsigned __int64)Client_Module + 1682880)();

	Update_Animation_Type = 0;
}