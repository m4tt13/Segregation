void* Original_On_Render_Start_Caller;

void __thiscall Redirected_On_Render_Start(void* Unknown_Parameter)
{
	if (*(void**)((unsigned __int32)__builtin_frame_address(0) + 48) == (void*)((unsigned __int32)Client_Module + 1884337))
	{
		(decltype(&Redirected_On_Render_Start)(Original_On_Render_Start_Caller))(Unknown_Parameter);
	}
}