__int32 Recent_Player_Data_Number;

void __stdcall Event_Processor(void* Event)
{
	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 7596836);

	if (Local_Player != nullptr)
	{
		using Get_Name_Type = char*(__thiscall*)(void* Event);

		char* Name = Get_Name_Type((unsigned __int32)Engine_Module + 1666864)(Event);

		using Get_Integer_Type = __int32(__thiscall*)(void* Event, char* Key, void* Unknown_Parameter);

		__int32 Victim_Number;

		__int32 Killer_Number;

		if (Name[0] == 'p')
		{
			using Identifier_To_Number_Type = __int32(__thiscall*)(void* Engine, __int32 Identifier);
			
			Victim_Number = Identifier_To_Number_Type((unsigned __int32)Engine_Module + 613520)((void*)((unsigned __int32)Engine_Module + 4052520), Get_Integer_Type((unsigned __int32)Engine_Module + 1666848)(Event, (char*)"userid", nullptr));

			Killer_Number = Identifier_To_Number_Type((unsigned __int32)Engine_Module + 613520)((void*)((unsigned __int32)Engine_Module + 4052520), Get_Integer_Type((unsigned __int32)Engine_Module + 1666848)(Event, (char*)"attacker", nullptr));
		}
		else
		{
			Victim_Number = Get_Integer_Type((unsigned __int32)Engine_Module + 1666848)(Event, (char*)"entindex_killed", nullptr);

			Killer_Number = Get_Integer_Type((unsigned __int32)Engine_Module + 1666848)(Event, (char*)"entindex_attacker", nullptr);
		}

		if (Victim_Number != Killer_Number)
		{
			if (Killer_Number != 0)
			{
				__int32 Local_Player_Number = *(__int32*)((unsigned __int32)Local_Player + 80);

				if (Victim_Number == Local_Player_Number)
				{
					if (Name[0] == 'e')
					{
						Player_Data_Structure* Player_Data = &Players_Data[Killer_Number];

						Player_Data->Memory_Tolerance = 0;

						if (Interface_Commentator.Integer == 1)
						{
							PlaySoundW((wchar_t*)Sounds_Laugh, nullptr, SND_ASYNC | SND_MEMORY);
						}
					}
				}
				else
				{
					if (Killer_Number == Local_Player_Number)
					{
						if (Victim_Number == Recent_Player_Data_Number)
						{
							Player_Data_Structure* Player_Data = &Players_Data[Victim_Number];

							if (Name[0] == 'p')
							{
								if (Player_Data->Memory_Tolerance == 0)
								{
									if (Player_Data->Tolerance == Interface_Bruteforce_Tolerance.Integer)
									{
										if (Player_Data->Shots_Fired == 0)
										{
											Player_Data->Switch_X ^= 1;
										}

										Player_Data->Shots_Fired = ((Player_Data->Shots_Fired - 1) % Bruteforce_Angles_Count + Bruteforce_Angles_Count) % Bruteforce_Angles_Count;
									}
									else
									{
										Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Integer;
									}
								}
							}
							else
							{
								if (Interface_Bruteforce_Memory_Tolerance.Integer != 0)
								{
									if (Player_Data->Memory_Tolerance == 0)
									{
										Player_Data->Tolerance = 0;

										Player_Data->Memorized_Y = Bruteforce_Angles[Player_Data->Shots_Fired];
									}

									Player_Data->Memory_Tolerance = Interface_Bruteforce_Memory_Tolerance.Integer;
								}
							}
						}

						if (Name[0] == 'e')
						{
							if (Interface_Commentator.Integer == 1)
							{
								PlaySoundW((wchar_t*)Sounds_Exclamation, nullptr, SND_ASYNC | SND_MEMORY);
							}
						}
					}
				}
			}
		}
	}
}