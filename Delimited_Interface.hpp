struct Interface_Structure
{
	__int8 Additional_Bytes_1[20];
	
	__int32 Flags;
	
	__int8 Additional_Bytes_2[12];

	char* String;

	__int8 Additional_Bytes_3[4];

	float Floating_Point;

	__int32 Integer;

	__int8 Additional_Bytes_4[16];

	void* Handler;
	
	char* Server_Value;
};

void Force_Console_Variable_Value(Interface_Structure* Console_Variable)
{
	Console_Variable = (Interface_Structure*)((unsigned __int32)Console_Variable - 24);

	using Set_Console_Variable_Value_Type = void(__thiscall**)(Interface_Structure* Console_Variable, __int32 Value);

	(*Set_Console_Variable_Value_Type(*(unsigned __int32*)Console_Variable + 48))(Console_Variable, 1);
}