SafetyHookInline Original_On_Render_Start_Caller{};

void On_Render_Start(void* Unknown_Parameter, void* Frame_Address)
{
	if (*(void**)((unsigned __int64)Frame_Address + 152) == (void*)((unsigned __int64)Client_Module + 2049454))
	{
		Original_On_Render_Start_Caller.call<void>(Unknown_Parameter);
	}
}

__attribute__((naked)) void Redirected_On_Render_Start()
{
	asm("leaq -8(%rsp), %rdx");
	asm("jmp %P0" : : "i"(On_Render_Start));
}