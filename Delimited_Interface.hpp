struct Interface_Structure
{
	__int8 Additional_Bytes_1[40];
	
	__int32 Flags;
	
	__int8 Additional_Bytes_2[28];

	char* String;

	__int8 Additional_Bytes_3[64];
	
	__int32 Get_Integer()
	{
		using Get_Console_Variable_Integer_Type = __int32(**)(Interface_Structure* Console_Variable);
		
		return (*Get_Console_Variable_Integer_Type(*(unsigned __int64*)this + 104))(this);
	}
	
	float Get_Floating_Point()
	{
		using Get_Console_Variable_Floating_Point_Type = float(**)(Interface_Structure* Console_Variable);
		
		return (*Get_Console_Variable_Floating_Point_Type(*(unsigned __int64*)this + 96))(this);
	}
};

void Force_Console_Variable_Value(Interface_Structure* Console_Variable)
{
	Console_Variable = (Interface_Structure*)((unsigned __int64)Console_Variable - 48);

	using Set_Console_Variable_Integer_Type = void(**)(Interface_Structure* Console_Variable, __int32 Value);

	(*Set_Console_Variable_Integer_Type(*(unsigned __int64*)Console_Variable + 128))(Console_Variable, 1);
}