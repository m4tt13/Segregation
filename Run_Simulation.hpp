struct Command_Structure
{
	__int32 Command_Number;

	__int32 Tick_Number;

	float Angles[3];

	float Move[2];

	__int32 Extra_Simulations;

	__int32 Buttons;

	__int8 Additional_Bytes_1[1];

	__int32 Select;

	__int8 Additional_Bytes_2[4];

	__int32 Random_Seed;
	
	__int8 Additional_Bytes_3[24];
	
	__int8 Typing;
	
	__int8 Additional_Bytes_4[247];
};

SafetyHookInline Original_Run_Simulation_Caller{};

void Redirected_Run_Simulation(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, Command_Structure* Command, void* Unknown_Parameter_4)
{
	static __int32 Extra_Simulations_Left;

	if (Extra_Simulations_Left == 0)
	{
		Extra_Simulations_Left = Command->Extra_Simulations;
		
		Original_Run_Simulation_Caller.call<void>(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Command, Unknown_Parameter_4);
	}
	else
	{
		Extra_Simulations_Left -= 1;
	}
}