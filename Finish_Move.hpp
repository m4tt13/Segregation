SafetyHookInline Original_Finish_Move_Caller{};

void Redirected_Finish_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Move_Data)
{
	float X = *(float*)((unsigned __int64)Move_Data + 76);

	if (X > 180)
	{
		X -= 360;
	}

	*(float*)((unsigned __int64)Move_Data + 76) = std::clamp(X, -90.f, 90.f);

	Original_Finish_Move_Caller.call<void>(Unknown_Parameter_1, Player, Unknown_Parameter_2, Move_Data);

	*(__int32*)((unsigned __int64)Player + 496) |= 4096;
}