void* Original_Packet_Start_Caller_Location;

void __thiscall Redirected_Packet_Start(void* Unknown_Parameter_1, void* Unknown_Parameter_2, __int32 Outgoing_Sequence_Number)
{
	Sequence_Structure* Sequence = &Sequences[Outgoing_Sequence_Number % 90];

	if (Outgoing_Sequence_Number == Sequence->Last_Sequence_Number)
	{
		(decltype(&Redirected_Packet_Start)(Original_Packet_Start_Caller_Location))(Unknown_Parameter_1, Unknown_Parameter_2, Sequence->First_Sequence_Number);
	}
	else
	{
		(decltype(&Redirected_Packet_Start)(Original_Packet_Start_Caller_Location))(Unknown_Parameter_1, Unknown_Parameter_2, Outgoing_Sequence_Number);
	}
}