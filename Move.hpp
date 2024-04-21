void* Original_Move_Caller;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

	auto Update_Animations = [&](__int8 Type)
	{
		Global_Variables->Frame_Time = 0;

		using Render_Start_Type = void(__cdecl*)();

		Render_Start_Type(604538272)();

		Update_Animation_Time = Global_Variables->Current_Time;

		Update_Animation_Type = Type;

		using Update_Animations_Type = void(__cdecl*)();

		Update_Animations_Type(604212176)();

		Update_Animation_Type = 0;
	};

	if (*(void**)607867332 != nullptr)
	{
		Redirected_Read_Packets(Final);

		Update_Animations(1);
	}

	(decltype(&Redirected_Move)(Original_Move_Caller))(Unknown_Parameter, Final);

	Update_Animations(2);
}