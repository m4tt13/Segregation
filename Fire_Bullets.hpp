struct Fire_Bullets_Info_Structure
{
	__int8 Additional_Bytes_1[28];

	float Spread[2];

	__int8 Additional_Bytes_2[4];

	float Range;
};

__int8 Bullets_Fired;

float Weapon_Recoil[2];

float Weapon_Spread[2];

float Weapon_Range;

void* Original_Fire_Bullets_Caller;

void __thiscall Redirected_Fire_Bullets(void* Player, Fire_Bullets_Info_Structure* Fire_Bullets_Info)
{
	Bullets_Fired = 1;
	
	if (__builtin_return_address(0) == (void*)((unsigned __int32)Client_Module + 1095978))
	{
		Byte_Manager::Set_Bytes(0, Weapon_Recoil, sizeof(Weapon_Recoil), 0);
	}
	else
	{
		Byte_Manager::Copy_Bytes(0, Weapon_Recoil, sizeof(Weapon_Recoil), (float*)((unsigned __int32)Player + 9440));
	}

	Byte_Manager::Copy_Bytes(0, Weapon_Spread, sizeof(Weapon_Spread), Fire_Bullets_Info->Spread);

	Weapon_Range = Fire_Bullets_Info->Range;

	(decltype(&Redirected_Fire_Bullets)(Original_Fire_Bullets_Caller))(Player, Fire_Bullets_Info);
}