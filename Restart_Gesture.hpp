void* Original_Restart_Gesture_Caller;

void __thiscall Redirected_Restart_Gesture(void* Unknown_Parameter_1, __int32 Gesture_Slot, void* Unknown_Parameter_2, void* Unknown_Parameter_3)
{
	if (Gesture_Slot != 5)
	{
		(decltype(&Redirected_Restart_Gesture)(Original_Restart_Gesture_Caller))(Unknown_Parameter_1, Gesture_Slot, Unknown_Parameter_2, Unknown_Parameter_3);
	}
}