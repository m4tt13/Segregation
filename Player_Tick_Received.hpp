__int32 Shot_Tick;

float Shot_Time;

void Redirected_Player_Tick_Received(void* Data, void* Unknown_Parameter, __int32* Output)
{
	__int32 Player_Tick = *(__int32*)((unsigned __int32)Data + 4);

	Shot_Time *= Player_Tick < Shot_Tick;

	*Output = Player_Tick;
}