#include "ScriptPCH.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// KILLSTREAK CONFIG ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PvPSystemEnabled = true;
bool OnlyInBattlegrounds = true;
bool LooseTokenOnPvPDeath = true;
int32 AmountOfItemsYouWantTheVictimToLoose = 1;
bool AddTokenOnPvPKill = true;
int32 ItemReward = 44115;
int32 AmountOfRewardsOnKillStreak[9] = { 1, 1, 1, 2, 2, 2, 3, 3, 3 };
int32 HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim = 2;
const int32 KillerStreak1 = 5;
const int32 KillerStreak2 = 10;
const int32 KillerStreak3 = 15;
const int32 KillerStreak4 = 20;
const int32 KillerStreak5 = 25;
const int32 KillerStreak6 = 30;
const int32 KillerStreak7 = 35;
const int32 KillerStreak8 = 40;
const int32 KillerStreak9 = 50;
int32 KillStreaks[9] = { KillerStreak1, KillerStreak2, KillerStreak3, KillerStreak4, KillerStreak5, KillerStreak6, KillerStreak7, KillerStreak8, KillerStreak9 };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SystemInfo
{
	uint32 KillStreak;
	uint32 LastGUIDKill;
	uint8 KillCount;
};

static std::map<uint32, SystemInfo> KillingStreak;

class killstreak_system : public PlayerScript
{
public:
	killstreak_system() : PlayerScript("killstreak_system") { }

	void OnPVPKill(Player* killer, Player* killed)
	{
		if (PvPSystemEnabled == false)
		{
			return;
		}
		else if (PvPSystemEnabled == true)
		{
			uint32 kGUID; 
			uint32 vGUID;
			char msg[500];
			kGUID = killer->GetGUID();
			vGUID = killed->GetGUID();

			if (kGUID == vGUID)
			{
				return;
			}

			if (KillingStreak[kGUID].LastGUIDKill == vGUID)
			{
				KillingStreak[kGUID].KillCount++;
				KillingStreak[vGUID].KillCount = 1;
				killer->AddItem(ItemReward, 1);
				if (LooseTokenOnPvPDeath == true)
				{
					killed->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true, false);
				}
			}
			if (KillingStreak[kGUID].LastGUIDKill != vGUID)
			{
				KillingStreak[kGUID].KillCount = 1;
				KillingStreak[vGUID].KillCount = 1;
			}

			if (KillingStreak[kGUID].KillCount == HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim)
			{
				return;
			}

			if (OnlyInBattlegrounds == true)
			{
				if (!killer->GetMap()->IsBattleground() || killer->GetMapId() == 30)
				{
					return;
				}
			}

			KillingStreak[kGUID].KillStreak++;
			KillingStreak[vGUID].KillStreak = 0;
			KillingStreak[kGUID].LastGUIDKill = vGUID;
			KillingStreak[vGUID].LastGUIDKill = 0;

			if (AddTokenOnPvPKill == true)
			{
				killer->AddItem(29435, 1);
			}

			if (LooseTokenOnPvPDeath == true)
			{
				killed->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true);
			}

			switch(KillingStreak[kGUID].KillStreak)
			{
				case KillerStreak1:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cff4876FFULTRAAAA KIIIIIIIIILLLLL!!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
					killer->ModifyHonorPoints(500);
					killer->CastSpell(killer, 24378, true);
					break;

				case KillerStreak2:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cffDAA520MOOOOONSTERRRR KILLLLLLL!!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[2]);
					killer->ModifyHonorPoints(1000);
					killer->CastSpell(killer, 24378, true);
					break;

				case KillerStreak3:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cffFFFF00HOOOLYYYY SHIIIITTTTT!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[3]);
					killer->ModifyHonorPoints(1500);
					killer->CastSpell(killer, 24378, true);
					break;

				case KillerStreak4:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cff7FFF00KILLING SPREEEEEE!!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[4]);
					killer->ModifyHonorPoints(2000);
					killer->CastSpell(killer, 24378, true);
					break;

				case KillerStreak5:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cffE066FFDOOMINATING!!!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[5]);
					killer->ModifyHonorPoints(2500);
					killer->CastSpell(killer, 24378, true);
					break;

				case KillerStreak6:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cff8B4C39RAAAAAMPAGEEEEEE!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[6]);
					killer->ModifyHonorPoints(3000);
					killer->CastSpell(killer, 24378, true);
					break;

				case KillerStreak7:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cff9400D3UNSTOPPABLEEEEEEEEEE!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[7]);
					killer->ModifyHonorPoints(3500);
					killer->CastSpell(killer, 24378, true);
					break;

				case KillerStreak8:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cffFF0000GOOOOOOOOOOOOOOD LIKEEEEEEEE!!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[8]);
					killer->ModifyHonorPoints(4000);
					killer->CastSpell(killer, 24378, true);
					break;

				case KillerStreak9:
					sprintf(msg, "|cffffffffkiLL Streak [|r|cffFF0000%s|r|cffffffff] Matou o jogador [|r|cffFF0000%s|r|cffffffff] e fez|r |cffFFFF00BEYOOOOND GOOOOOD LIKE!!!!", killer->GetName().c_str(), killed->GetName().c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[9]);
					KillingStreak[kGUID].KillStreak = 0;
					killer->ModifyHonorPoints(5000);
					killer->CastSpell(killer, 24378, true);
					break;
			}
		}
	}
};

void AddSC_killstreak_system()
{
	new killstreak_system;
}