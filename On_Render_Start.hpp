void* Original_On_Render_Start_Caller;

void __thiscall Redirected_On_Render_Start(void* Unknown_Parameter)
{
	if (*(void**)((unsigned __int32)__builtin_frame_address(0) + 12) == (void*)604538622)
	{
		(decltype(&Redirected_On_Render_Start)(Original_On_Render_Start_Caller))(Unknown_Parameter);
	}
}