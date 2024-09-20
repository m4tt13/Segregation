Player_Data_Structure Previous_Recent_Player_Data;

void* Original_Copy_Command_Caller;

void __thiscall Redirected_Copy_Command(void* Unknown_Parameter, Command_Structure* Command)
{
	Command->Extra_Simulations = 0;

	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 7603940);

	if (*(__int8*)((unsigned __int32)Local_Player + 143) == 0)
	{
		using Run_Prediction_Type = void(__cdecl*)();

		Run_Prediction_Type((unsigned __int32)Engine_Module + 736144)();

		auto Angle_Vectors = [](float* Angles, float* Forward, float* Right, float* Up) -> void
		{
			using Angle_Vectors_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

			Angle_Vectors_Type((unsigned __int32)Client_Module + 3892288)(Angles, Forward, Right, Up);
		};

		float Move_Angles[3] =
		{
			Command->Angles[0],

			Command->Angles[1],

			0
		};

		static float Previous_Move_Angle_Y;

		if ((Command->Buttons & 2) == 2)
		{
			Command->Move[0] = 0;

			if (*(__int32*)((unsigned __int32)Local_Player + 596) == -1)
			{
				Command->Buttons &= ~(*(__int8*)((unsigned __int32)Local_Player + 376) & 2);
			}
			else
			{
				Command->Buttons &= ~(*(__int32*)((unsigned __int32)Local_Player + 9936) & 2);
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360);

			Previous_Move_Angle_Y = Move_Angles[1];

			float* Velocity = (float*)((unsigned __int32)Local_Player + 244);

			if (__builtin_fabsf(Difference) < __builtin_atan2f(30, __builtin_hypotf(Velocity[0], Velocity[1])) * 180 / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(Move_Angles[1] - __builtin_atan2f(Velocity[1], Velocity[0]) * 180 / 3.1415927f, 360);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					Command->Move[1] = -10000;
				}
				else
				{
					Command->Move[1] = 10000;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					Command->Move[1] = -10000;
				}
				else
				{
					Command->Move[1] = 10000;
				}
			}
		}
		else
		{
			Previous_Move_Angle_Y = Move_Angles[1];
		}

		float Previous_Move[2];

		Byte_Manager::Copy_Bytes(0, Previous_Move, sizeof(Previous_Move), Command->Move);

		float Desired_Move_Forward[3];

		float Desired_Move_Right[3];

		Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

		Desired_Move_Forward[2] = 0;

		auto Vector_Normalize = [](float* Vector) -> float
		{
			using Vector_Normalize_Type = float(__thiscall*)(float* Vector);

			return Vector_Normalize_Type((unsigned __int32)Client_Module + 3889968)(Vector);
		};

		Vector_Normalize(Desired_Move_Forward);

		Desired_Move_Right[2] = 0;

		Vector_Normalize(Desired_Move_Right);

		float Desired_Move[2] =
		{
			Desired_Move_Forward[0] * Command->Move[0] + Desired_Move_Right[0] * Command->Move[1],

			Desired_Move_Forward[1] * Command->Move[0] + Desired_Move_Right[1] * Command->Move[1]
		};

		auto Correct_Movement = [&]() -> void
		{
			float Move_Forward[3];

			float Move_Right[3];

			Angle_Vectors(Command->Angles, Move_Forward, Move_Right, nullptr);

			Move_Forward[2] = 0;

			Vector_Normalize(Move_Forward);

			Move_Right[2] = 0;

			Vector_Normalize(Move_Right);

			float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

			float X = std::clamp((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider, -16383.999f, 16383.999f);

			Command->Move[0] = X;

			Command->Buttons &= ~1560;

			if (__builtin_truncf(X) != 0)
			{
				Command->Buttons |= 8 * ((X < 0) + 1);
			}

			float Y = std::clamp((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider, -16383.999f, 16383.999f);

			Command->Move[1] = Y;

			if (__builtin_truncf(Y) != 0)
			{
				Command->Buttons |= 512 * ((Y > 0) + 1);
			}
		};

		Correct_Movement();

		Bullets_Fired = 0;

		__int32 Previous_Buttons = Command->Buttons;

		Command->Buttons |= 1;
		
		void* Prediction = (void*)((unsigned __int32)Client_Module + 7317296);

		*(__int8*)((unsigned __int32)Prediction + 8) = 1;

		*(__int8*)((unsigned __int32)Prediction + 9) = 0;

		auto Suppress_Events = [&](__int8 State) -> void
		{
			void* Prediction_System = *(void**)((unsigned __int32)Client_Module + 8159336);

			Traverse_Prediction_Systems_Label:
			{
				if (Prediction_System != nullptr)
				{
					*(__int8*)((unsigned __int32)Prediction_System + 8) = State;

					Prediction_System = *(void**)((unsigned __int32)Prediction_System + 4);

					goto Traverse_Prediction_Systems_Label;
				}
			}
		};

		Suppress_Events(1);

		float Local_Player_Previous_Origin[3];

		float* Local_Player_Origin = (float*)((unsigned __int32)Local_Player + 824);

		if (Interface_Alternative.Integer == 0)
		{
			Byte_Manager::Copy_Bytes(0, Local_Player_Previous_Origin, sizeof(Local_Player_Previous_Origin), Local_Player_Origin);
		}

		Redirected_Run_Command(Prediction, Local_Player, Command, (void*)((unsigned __int32)Client_Module + 7065104));

		Suppress_Events(0);

		*(__int8*)((unsigned __int32)Prediction + 8) = 0;

		Command->Buttons = Previous_Buttons;

		Byte_Manager::Copy_Bytes(0, Command->Move, sizeof(Previous_Move), Previous_Move);

		static __int8 Send_Packet;

		__int32 Choked_Commands_Count = *(__int32*)((unsigned __int32)Engine_Module + 5269640);

		__int8 Predicted_Send_Packet = 0;

		static float Networked_Origin[3];

		if (Interface_Alternative.Integer == 0)
		{
			__int32 Predicted_Choked_Commands_Count = Choked_Commands_Count + 1;

			if (Choked_Commands_Count < Interface_Minimum_Choked_Commands.Integer)
			{
				Send_Packet = 0;

				if (Predicted_Choked_Commands_Count == Interface_Minimum_Choked_Commands.Integer)
				{
					if (Predicted_Choked_Commands_Count < Interface_Maximum_Choked_Commands.Integer)
					{
						goto Predict_Dynamic_Send_Packet_Label;
					}
					else
					{
						Predicted_Send_Packet = 1;
					}
				}
			}
			else
			{
				if (Choked_Commands_Count < Interface_Maximum_Choked_Commands.Integer)
				{
					if (__builtin_powf(Networked_Origin[0] - Local_Player_Previous_Origin[0], 2) + __builtin_powf(Networked_Origin[1] - Local_Player_Previous_Origin[1], 2) + __builtin_powf(Networked_Origin[2] - Local_Player_Previous_Origin[2], 2) <= 4096)
					{
						Send_Packet = 0;

						Predict_Dynamic_Send_Packet_Label:
						{
							if (Predicted_Choked_Commands_Count == Interface_Maximum_Choked_Commands.Integer)
							{
								Predicted_Send_Packet = 1;
							}
							else
							{
								if (__builtin_powf(Networked_Origin[0] - Local_Player_Origin[0], 2) + __builtin_powf(Networked_Origin[1] - Local_Player_Origin[1], 2) + __builtin_powf(Networked_Origin[2] - Local_Player_Origin[2], 2) > 4096)
								{
									Predicted_Send_Packet = 1;
								}
							}
						}

					}
					else
					{
						Send_Packet_Label:
						{
							Byte_Manager::Copy_Bytes(0, Networked_Origin, sizeof(Networked_Origin), Local_Player_Origin);

							Send_Packet = 1;
						}
					}
				}
				else
				{
					goto Send_Packet_Label;
				}
			}
		}
		else
		{
			if (Send_Packet == 2)
			{
				goto Send_Packet_Label;
			}

			if (Choked_Commands_Count < Interface_Minimum_Choked_Commands.Integer)
			{
				Send_Packet = 0;
			}
			else
			{
				if (Choked_Commands_Count < Interface_Maximum_Choked_Commands.Integer)
				{
					if (__builtin_powf(Networked_Origin[0] - Local_Player_Origin[0], 2) + __builtin_powf(Networked_Origin[1] - Local_Player_Origin[1], 2) + __builtin_powf(Networked_Origin[2] - Local_Player_Origin[2], 2) <= 4096)
					{
						Send_Packet = 0;
					}
					else
					{
						goto Send_Packet_Label;
					}
				}
				else
				{
					goto Send_Packet_Label;
				}
			}
		}

		__int32 Entity_Number = 1;

		using Get_Latency_Type = float(__thiscall*)(void* Network_Channel, __int32 Type);

		void* Network_Channel = *(void**)((unsigned __int32)Engine_Module + 5201264);

		float Latency = Get_Latency_Type((unsigned __int32)Engine_Module + 1843744)(Network_Channel, 0);

		using Get_Interpolation_Time_Type = float(__stdcall*)();

		float Interpolation_Time = Get_Interpolation_Time_Type((unsigned __int32)Engine_Module + 797328)();

		float Corrected_Latency = std::clamp(Latency + Interpolation_Time, 0.f, 1.f);

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7049092);

		struct Target_Structure
		{
			__int32 Priority;

			void* Self;

			__int32 Tick_Number;

			__int8 Valid;

			float Distance;
		};

		static std::vector<Target_Structure> Sorted_Target_List;

		Sorted_Target_List.clear();

		Traverse_Entity_List_Label:
		{
			Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

			if (Player_Data->Priority != -1)
			{
				void* Entity = *(void**)((unsigned __int32)Client_Module + 7981300 + ((Entity_Number - 16385) << 4));

				if (Entity != nullptr)
				{
					if (Entity != Local_Player)
					{
						if (*(__int8*)((unsigned __int32)Entity + 143) == 0)
						{
							__int8 Valid_Team = Interface_Team_Check.Integer == 0;
							
							if (Valid_Team == 0)
							{
								Valid_Team = *(__int32*)((unsigned __int32)Entity + 156) != *(__int32*)((unsigned __int32)Local_Player + 156);
							}
							
							if (Valid_Team == 1)
							{
								if (*(__int8*)((unsigned __int32)Entity + 382) == 0)
								{
									__int32 Target_Tick = *(float*)((unsigned __int32)Entity + 104) / Global_Variables->Interval_Per_Tick + 0.5f;

									float* Entity_Origin = (float*)((unsigned __int32)Entity + 824);

									Target_Structure Target =
									{
										Player_Data->Priority == -2 ? 0 : Player_Data->Priority,

										Entity,

										Target_Tick + (__int32)(Interpolation_Time / Global_Variables->Interval_Per_Tick + 0.5f),

										__builtin_fabsf(Corrected_Latency - (__int32)(Global_Variables->Tick_Number + (Interface_Alternative.Integer == 0) + (__int32)(Latency / Global_Variables->Interval_Per_Tick + 0.5f) - Target_Tick) * Global_Variables->Interval_Per_Tick) <= 0.2f,

										__builtin_powf(Local_Player_Origin[0] - Entity_Origin[0], 2) + __builtin_powf(Local_Player_Origin[1] - Entity_Origin[1], 2) + __builtin_powf(Local_Player_Origin[2] - Entity_Origin[2], 2)
									};

									Sorted_Target_List.push_back(Target);
								}
							}
						}
					}
				}
			}

			if (Entity_Number != Global_Variables->Maximum_Clients)
			{
				Entity_Number += 1;

				goto Traverse_Entity_List_Label;
			}
		}

		auto Target_List_Sort_Prepare = [](Target_Structure& X, Target_Structure& Y) -> __int8
		{
			return X.Priority < Y.Priority;
		};

		std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort_Prepare);

		auto Target_List_Sort_Finish = [](Target_Structure& X, Target_Structure& Y) -> __int8
		{
			if (X.Priority > Y.Priority)
			{
				return 1;
			}

			return X.Distance < Y.Distance;
		};

		std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort_Finish);

		__int8 In_Attack = 0;

		if (Command->Select == 0)
		{
			if (__builtin_fabsf(Global_Variables->Current_Time - Shot_Time) > 0.5f)
			{
				if (Shot_Time == 0)
				{
					Passed_Shot_Time_Check_Label:
					{
						if ((Command->Buttons & 2048) == 0)
						{
							__int8 Send_Packet_Sequence = (Send_Packet == 0) + (Predicted_Send_Packet == 1);

							if (Interface_Alternative.Integer != 0)
							{
								Send_Packet_Sequence = 2;
							}

							if (Send_Packet_Sequence == 2)
							{
								if (Bullets_Fired == 1)
								{
									size_t Target_Number = 0;

									using Get_Eye_Position_Type = void(__thiscall*)(void* Entity, float* Eye_Position);

									float Eye_Position[3];

									Get_Eye_Position_Type((unsigned __int32)Client_Module + 1388832)(Local_Player, Eye_Position);

									Recent_Player_Data_Number = 0;

									Traverse_Sorted_Target_List_Label:
									{
										if (Target_Number != Sorted_Target_List.size())
										{
											Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

											if (Target->Valid == 1)
											{
												using Get_Studio_Header_Type = void*(__thiscall*)(void* Entity);

												void* Studio_Header = Get_Studio_Header_Type((unsigned __int32)Client_Module + 763792)(Target->Self);

												void* Hitbox_Set = (void*)((unsigned __int32)*(void**)Studio_Header + *(__int32*)((unsigned __int32)*(void**)Studio_Header + 176) + 12 * *(unsigned __int32*)((unsigned __int32)Target->Self + 5024));

												auto Find_Hitbox_By_Group = [&](__int32 Group) -> void*
												{
													void* Hitbox;

													__int32 Hitbox_Number = 0;

													Traverse_Hitboxes_Label:
													{
														Hitbox = nullptr;

														if (Hitbox_Number != *(__int32*)((unsigned __int32)Hitbox_Set + 4))
														{
															Hitbox = (void*)((unsigned __int32)Hitbox_Set + *(__int32*)((unsigned __int32)Hitbox_Set + 8) + Hitbox_Number * 68);

															if (*(__int32*)((unsigned __int32)Hitbox + 4) != Group)
															{
																Hitbox_Number += 1;

																goto Traverse_Hitboxes_Label;
															}
														}
													}

													return Hitbox;
												};

												void* Hitbox = Find_Hitbox_By_Group(Interface_Aim_Hitgroup.Integer);

												if (Hitbox != nullptr)
												{
													Compute_Custom_Torso_Rotation(*(void**)((unsigned __int32)Target->Self + 12280), Studio_Header);

													using Invalidate_Bone_Cache_Type = void(__thiscall*)(void* Entity);

													Invalidate_Bone_Cache_Type((unsigned __int32)Client_Module + 1549344)(Target->Self);

													using Get_Bone_Cache_Type = void*(__cdecl*)(unsigned __int32 Bone_Cache_Handle);

													void* Bone_Cache = Get_Bone_Cache_Type((unsigned __int32)Client_Module + 1491104)(*(unsigned __int32*)((unsigned __int32)Target->Self + 5792));

													if (Bone_Cache != nullptr)
													{
														*(float*)Bone_Cache = -1;
													}

													using Setup_Bones_Type = __int8(__thiscall*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

													float Bones[128][3][4];

													if (Setup_Bones_Type((unsigned __int32)Client_Module + 1562736)((void*)((unsigned __int32)Target->Self + 4), Bones, 128, 524032, Global_Variables->Current_Time) == 1)
													{
														auto Trace_Ray = [&](float Direction[3]) -> __int8
														{
															struct alignas(16) Ray_Structure
															{
																__int8 Additional_Bytes[65];
															};

															struct Filter_Structure
															{
																void* Table;

																void* Skip;

																__int32 Group;

																void* Handler;
															};

															struct Trace_Structure
															{
																__int8 Additional_Bytes_1[55];

																__int8 Start_Solid;

																__int8 Additional_Bytes_2[12];

																__int32 Group;

																__int8 Additional_Bytes_3[4];

																void* Entity;

																__int8 Additional_Bytes_4[4];
															};

															using Trace_Ray_Type = void(__thiscall*)(void* Engine, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

															using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End);

															Ray_Structure Ray;

															Vector_Normalize(Direction);

															float End[3]
															{
																Eye_Position[0] + Direction[0] * Weapon_Range,

																Eye_Position[1] + Direction[1] * Weapon_Range,

																Eye_Position[2] + Direction[2] * Weapon_Range
															};

															Initialize_Ray_Type((unsigned __int32)Client_Module + 983392)(&Ray, Eye_Position, End);

															Filter_Structure Filter;

															Filter.Table = (void*)((unsigned __int32)Client_Module + 5976040);

															Filter.Skip = Local_Player;

															Filter.Group = 0;

															Filter.Handler = nullptr;

															Trace_Structure Trace;
															
															Trace.Entity = nullptr;

															Trace_Ray_Type((unsigned __int32)Engine_Module + 1654768)((void*)((unsigned __int32)Engine_Module + 4325076), &Ray, 1174421507, &Filter, &Trace);

															if (Trace.Start_Solid == 0)
															{
																using Clip_Trace_To_Players_Type = void(__cdecl*)(float* Start, float* End, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																Clip_Trace_To_Players_Type((unsigned __int32)Client_Module + 2756752)(Eye_Position, End, 1174421507, &Filter, &Trace);
															}

															if (Trace.Entity == Target->Self)
															{
																if (Interface_Aim_Intersection.Integer == 0)
																{
																	return Trace.Group == Interface_Aim_Hitgroup.Integer;
																}

																return 1;
															}

															return 0;
														};

														float* Hitbox_Minimum = (float*)((unsigned __int32)Hitbox + 8);

														float* Hitbox_Maximum = (float*)((unsigned __int32)Hitbox + 20);

														float Hitbox_Center[3]
														{
															(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2,

															(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2,

															(Hitbox_Minimum[2] + Hitbox_Maximum[2]) / 2
														};

														__int32 Bone_Index = *(__int32*)Hitbox;

														float Hitbox_Z_Vertices[8]
														{
															Bones[Bone_Index][2][0] * Hitbox_Minimum[0] + Bones[Bone_Index][2][1] * Hitbox_Minimum[1] + Bones[Bone_Index][2][2] * Hitbox_Minimum[2],

															Bones[Bone_Index][2][0] * Hitbox_Maximum[0] + Bones[Bone_Index][2][1] * Hitbox_Minimum[1] + Bones[Bone_Index][2][2] * Hitbox_Minimum[2],

															Bones[Bone_Index][2][0] * Hitbox_Minimum[0] + Bones[Bone_Index][2][1] * Hitbox_Maximum[1] + Bones[Bone_Index][2][2] * Hitbox_Minimum[2],

															Bones[Bone_Index][2][0] * Hitbox_Minimum[0] + Bones[Bone_Index][2][1] * Hitbox_Minimum[1] + Bones[Bone_Index][2][2] * Hitbox_Maximum[2],

															Bones[Bone_Index][2][0] * Hitbox_Maximum[0] + Bones[Bone_Index][2][1] * Hitbox_Maximum[1] + Bones[Bone_Index][2][2] * Hitbox_Minimum[2],

															Bones[Bone_Index][2][0] * Hitbox_Maximum[0] + Bones[Bone_Index][2][1] * Hitbox_Minimum[1] + Bones[Bone_Index][2][2] * Hitbox_Maximum[2],

															Bones[Bone_Index][2][0] * Hitbox_Minimum[0] + Bones[Bone_Index][2][1] * Hitbox_Maximum[1] + Bones[Bone_Index][2][2] * Hitbox_Maximum[2],

															Bones[Bone_Index][2][0] * Hitbox_Maximum[0] + Bones[Bone_Index][2][1] * Hitbox_Maximum[1] + Bones[Bone_Index][2][2] * Hitbox_Maximum[2]
														};

														float* Hitbox_Z_Extremes[2];

														std::tie(Hitbox_Z_Extremes[0], Hitbox_Z_Extremes[1]) = std::minmax_element(Hitbox_Z_Vertices, &Hitbox_Z_Vertices[sizeof(Hitbox_Z_Vertices) / sizeof(Hitbox_Z_Vertices[0])]);

														float Target_Origin[3] =
														{
															Bones[Bone_Index][0][0] * Hitbox_Center[0] + Bones[Bone_Index][0][1] * Hitbox_Center[1] + Bones[Bone_Index][0][2] * Hitbox_Center[2] + Bones[Bone_Index][0][3],

															Bones[Bone_Index][1][0] * Hitbox_Center[0] + Bones[Bone_Index][1][1] * Hitbox_Center[1] + Bones[Bone_Index][1][2] * Hitbox_Center[2] + Bones[Bone_Index][1][3],

															Hitbox_Z_Extremes[0][0] + (Hitbox_Z_Extremes[1][0] - Hitbox_Z_Extremes[0][0]) * Interface_Aim_Height.Floating_Point + Bones[Bone_Index][2][3]
														};

														float Direction[3] =
														{
															Target_Origin[0] - Eye_Position[0],

															Target_Origin[1] - Eye_Position[1],

															Target_Origin[2] - Eye_Position[2]
														};

														if (Trace_Ray(Direction) == 1)
														{
															Command->Tick_Number = Target->Tick_Number;

															Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180 / 3.1415927f;

															Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f;

															Command->Buttons |= 1;

															if (Interface_Bruteforce.Integer == 1)
															{
																__int32 Target_Number = *(__int32*)((unsigned __int32)Target->Self + 80);

																Player_Data_Structure* Player_Data = &Players_Data[Target_Number];

																if (Player_Data->Priority != -2)
																{
																	Recent_Player_Data_Number = Target_Number;

																	Byte_Manager::Copy_Bytes(0, &Previous_Recent_Player_Data, sizeof(Previous_Recent_Player_Data), Player_Data);

																	if (Player_Data->Memory_Tolerance == 0)
																	{
																		if (Player_Data->Tolerance == 0)
																		{
																			Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % Bruteforce_Angles_Count;

																			if (Player_Data->Shots_Fired == 0)
																			{
																				Player_Data->Switch_X ^= 1;
																			}

																			Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Integer;
																		}
																		else
																		{
																			Player_Data->Tolerance -= 1;
																		}
																	}
																	else
																	{
																		Player_Data->Memory_Tolerance -= 1;
																	}
																}
															}

															goto Found_Target_Label;
														}
													}
												}
											}

											Target_Number += 1;

											goto Traverse_Sorted_Target_List_Label;

											Found_Target_Label:
											{

											}
										}
									}

									if ((Command->Buttons & 1) == 1)
									{
										auto Calculate_Spread = [&](float* Spread) -> void
										{
											auto Console_Variable_Floating_Point = [&](Interface_Structure* Console_Variable) -> float
											{
												if (Console_Variable->Server_Value != nullptr)
												{
													if (Console_Variable->Server_Value[0] != 0)
													{
														return atof(Console_Variable->Server_Value);
													}
												}
												
												return Console_Variable->Floating_Point;
											};
											
											using Random_Seed_Type = void(__cdecl*)(__int32 Seed);

											static void* Standard_Library_Module = GetModuleHandleW(L"vstdlib.dll");

											Random_Seed_Type((unsigned __int32)Standard_Library_Module + 38368)(Command->Random_Seed & 255);

											float Random_X;

											float Random_Y;

											float Random_Z;

											using Random_Type = float(__cdecl*)(float Minimum, float Maximum);
											
											void* Console_Variables = *(void**)((unsigned __int32)Engine_Module + 10627684);

											using Find_Console_Variable_Type = Interface_Structure*(__thiscall**)(void* Console_Variables, char* Name);

											static Interface_Structure* Interface_Shot_Bias_Min = (*Find_Console_Variable_Type(*(unsigned __int32*)Console_Variables + 52))(Console_Variables, (char*)"ai_shot_bias_min");

											static Interface_Structure* Interface_Shot_Bias_Max = (*Find_Console_Variable_Type(*(unsigned __int32*)Console_Variables + 52))(Console_Variables, (char*)"ai_shot_bias_max");

											float Shot_Bias_Min = Console_Variable_Floating_Point(Interface_Shot_Bias_Min);
											
											float Shot_Bias_Max = Console_Variable_Floating_Point(Interface_Shot_Bias_Max);

											float Shot_Bias = (Shot_Bias_Max - Shot_Bias_Min) + Shot_Bias_Min;

											float Flatness = __builtin_fabsf(Shot_Bias) * 0.5f;

											Calculate_Random_Label:
											{
												Random_X = Random_Type((unsigned __int32)Standard_Library_Module + 38208)(-1, 1) * Flatness + Random_Type((unsigned __int32)Standard_Library_Module + 38208)(-1, 1) * (1 - Flatness);

												Random_Y = Random_Type((unsigned __int32)Standard_Library_Module + 38208)(-1, 1) * Flatness + Random_Type((unsigned __int32)Standard_Library_Module + 38208)(-1, 1) * (1 - Flatness);

												if (Shot_Bias < 0)
												{
													if (Random_X < 0)
													{
														Random_X = -1 - Random_X;
													}
													else
													{
														Random_X = 1 - Random_X;
													}

													if (Random_Y < 0)
													{
														Random_Y = -1 - Random_Y;
													}
													else
													{
														Random_Y = 1 - Random_Y;
													}
												}

												Random_Z = Random_X * Random_X + Random_Y * Random_Y;

												if (Random_Z > 1)
												{
													goto Calculate_Random_Label;
												}
											}

											Spread[0] = 1;

											Spread[1] = -Weapon_Spread[0] * Random_X;

											Spread[2] = Weapon_Spread[1] * Random_Y;

											Vector_Normalize(Spread);
										};

										float Forward[3];

										Angle_Vectors(Command->Angles, Forward, nullptr, nullptr);

										Command->Command_Number = -98069271;

										Command->Random_Seed = 33;

										float Spread[3];

										Calculate_Spread(Spread);

										float Square_XZ = 1 - Spread[1] * Spread[1];

										float Rotation[2];

										if (Forward[2] * Forward[2] > Square_XZ)
										{
											Rotation[0] = __builtin_sqrtf(Square_XZ);

											if (Forward[2] < 0)
											{
												Rotation[0] = -Rotation[0];
											}

											Rotation[1] = 0;
										}
										else
										{
											Rotation[0] = Forward[2];

											Rotation[1] = __builtin_sqrtf(Square_XZ - Forward[2] * Forward[2]);
										}

										float Compensated_Pitch_1 = __builtin_atan2f(Rotation[0] * -Spread[0] + Rotation[1] * Spread[2], Rotation[0] * Spread[2] + Rotation[1] * Spread[0]) * 180 / 3.1415927f;
										
										float Compensated_Pitch_2 = -Compensated_Pitch_1 - Weapon_Recoil[0];
										
										if (Compensated_Pitch_2 > 0)
										{
											Command->Angles[0] = Compensated_Pitch_1 - Weapon_Recoil[0];
										
											Command->Angles[1] = __builtin_atan2f(Forward[0] * -Spread[1] + Forward[1] * Rotation[1], Forward[0] * Rotation[1] + Forward[1] * Spread[1]) * 180 / 3.1415927f - Weapon_Recoil[1];
										}
										else
										{
											Command->Angles[0] = 180 + Compensated_Pitch_2;
										
											Command->Angles[1] = 180 + __builtin_atan2f(Forward[0] * -Spread[1] + Forward[1] * Rotation[1], Forward[0] * Rotation[1] + Forward[1] * Spread[1]) * 180 / 3.1415927f - Weapon_Recoil[1];
										}

										In_Attack = 1;

										Send_Packet = (Interface_Alternative.Integer != 0) * 2;

										Shot_Tick = *(__int32*)((unsigned __int32)Local_Player + 10140);

										Shot_Time = Global_Variables->Current_Time;
									}
								}
							}
						}
					}
				}
				else
				{
					Shot_Time = 0;

					if (Recent_Player_Data_Number == 0)
					{
						goto Passed_Shot_Time_Check_Label;
					}

					Byte_Manager::Copy_Bytes(0, &Players_Data[Recent_Player_Data_Number], sizeof(Previous_Recent_Player_Data), &Previous_Recent_Player_Data);

					goto Passed_Shot_Time_Check_Label;
				}
			}
		}

		Command->Buttons &= ~2048;

		if (In_Attack == 0)
		{
			Command->Buttons &= ~1;

			if (Sorted_Target_List.size() != 0)
			{
				Command->Angles[0] = Interface_Angle_X.Floating_Point;

				float* Target_Origin = (float*)((unsigned __int32)Sorted_Target_List.at(0).Self + 824);

				float Direction[2] =
				{
					Target_Origin[0] - Local_Player_Origin[0],

					Target_Origin[1] - Local_Player_Origin[1]
				};

				if (Send_Packet == 0)
				{
					if ((Command->Command_Number % 2) == 0)
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_First_Choked_Angle_Y.Floating_Point;
					}
					else
					{
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_Second_Choked_Angle_Y.Floating_Point;
					}
				}
				else
				{
					Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_Angle_Y.Floating_Point;
				}
			}
		}

		Correct_Movement();

		if (Send_Packet == 0)
		{
			using Send_Datagram_Type = __int32(__thiscall*)(void* Network_Channel, void* Unknown_Parameter);

			__int32 Sequence_Number = *(__int32*)((unsigned __int32)Network_Channel + 8) = Send_Datagram_Type((unsigned __int32)Engine_Module + 1854608)(Network_Channel, nullptr);

			Sequences[Sequence_Number % 90] =
			{
				Sequence_Number,

				Sequence_Number - Choked_Commands_Count - 1
			};
		}
		else
		{
			Command->Extra_Simulations = max(0, Choked_Commands_Count - 14);

			Byte_Manager::Copy_Bytes(0, Update_Animation_Angles, sizeof(Update_Animation_Angles), Command->Angles);
		}

		*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 4275) = Send_Packet;
	}

	(decltype(&Redirected_Copy_Command)(Original_Copy_Command_Caller))(Unknown_Parameter, Command);
}