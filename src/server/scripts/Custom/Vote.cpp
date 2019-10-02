/*
*
* Made by mthsena
*
*

REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES('900000','0','0','0','0','0','25900','0','0','0','Trader - Donor & Voter','- by mthsena -',NULL,'0','80','80','0','35','35','1','1','1.14286','4','3','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','1','1','1','0','0','0','0','0','0','0','0','1','0','0','Donor_Voter_Trader','1');

*/

#include "ScriptPCH.h"

enum Tokens
{
	DONOR_TOKEN = 19322, // Your token ID, Default: Mark of Thrallmar
	VOTER_TOKEN = 38186, // Your token ID, Default: Mark of Honor Hold
};

class Donor_Voter_Trader : public CreatureScript
{
public:
	Donor_Voter_Trader() : CreatureScript("Donor_Voter_Trader") { }

	bool OnGossipHello(Player *player, Creature *creature)
	{
		player->ADD_GOSSIP_ITEM(0, ">> Meus Pontos <<", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(0, "[Pontos V.I.P]", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(0, "[Pontos de Voto]", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(4, "Fechar.", GOSSIP_SENDER_MAIN, 10);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
	{
		QueryResult select = LoginDatabase.PQuery("SELECT dp, vp FROM account WHERE id = '%u'", player->GetSession()->GetAccountId());

		if (!select)
		{
			player->GetSession()->SendAreaTriggerMessage("Internal error!");
			return false;
		}

		Field* fields = select->Fetch();
		uint32 dp = fields[0].GetUInt32();
		uint32 vp = fields[1].GetUInt32();

		player->PlayerTalkClass->ClearMenus();

		if (sender == GOSSIP_SENDER_MAIN)
		{
			switch (uiAction)
			{
			case 1:// Donor Points
				if (dp == 0)
				{
					player->GetSession()->SendAreaTriggerMessage("Voce nao tem Pontos VIP.");
					player->CLOSE_GOSSIP_MENU();
					return false;
				}

				player->ADD_GOSSIP_ITEM_EXTENDED(0, "[1 Pontos VIP] para [1 Token VIP]", GOSSIP_SENDER_MAIN, 4, "Voce tem Certeza?", 0, false);
				player->ADD_GOSSIP_ITEM_EXTENDED(0, "[10 Pontos VIP] para [10 Token VIP]", GOSSIP_SENDER_MAIN, 5, "Voce tem Certeza?", 0, false);
				player->ADD_GOSSIP_ITEM(4, "...Back", GOSSIP_SENDER_MAIN, 11);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				break;

			case 2:// Voter Points
				if (vp == 0)
				{
					player->GetSession()->SendAreaTriggerMessage("Voce nao tem Pontos de Voto.");
					player->CLOSE_GOSSIP_MENU();
					return false;
				}

				player->ADD_GOSSIP_ITEM_EXTENDED(0, "[1 Pontos de Voto] para [1 Vote Token]", GOSSIP_SENDER_MAIN, 6, "Voce tem Certeza?", 0, false);
				player->ADD_GOSSIP_ITEM_EXTENDED(0, "[10 Pontos de Voto] para [10 Vote Token]", GOSSIP_SENDER_MAIN, 7, "Voce tem Certeza?", 0, false);
				player->ADD_GOSSIP_ITEM(4, "...Back", GOSSIP_SENDER_MAIN, 11);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				break;

			case 3:// Show My Points
				player->GetSession()->SendAreaTriggerMessage("Pontos VIP: %u", dp);
				player->GetSession()->SendAreaTriggerMessage("Pontos de Voto: %u", vp);
				player->CLOSE_GOSSIP_MENU();
				break;

			case 4:// [1 Donor Point] For [1 Donor Token]
				if (dp < 1)
				{
					player->GetSession()->SendAreaTriggerMessage("Voce nao tem os itens necessarios.");
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					LoginDatabase.PExecute("UPDATE account SET dp = '%u' -1 WHERE id = '%u'", dp, player->GetSession()->GetAccountId()); // DP Exchange 1
					player->GetSession()->SendAreaTriggerMessage("Sucesso !");
					player->AddItem(DONOR_TOKEN, 1);
					player->SaveToDB();
					player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 5:// [10 Donor Points] For [10 Donor Tokens]
				if (dp < 10)
				{
					player->GetSession()->SendAreaTriggerMessage("Voce nao tem os itens necessarios.");
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					LoginDatabase.PExecute("UPDATE account SET dp = '%u' -10 WHERE id = '%u'", dp, player->GetSession()->GetAccountId()); // DP Exchange 10
					player->GetSession()->SendAreaTriggerMessage("Sucesso !");
					player->AddItem(DONOR_TOKEN, 10);
					player->SaveToDB();
					player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 6:// [1 Voter Point] For [1 Voter Token]
				if (vp < 1)
				{
					player->GetSession()->SendAreaTriggerMessage("Voce nao tem os itens necessarios.");
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					LoginDatabase.PExecute("UPDATE account SET vp = '%u' -1 WHERE id = '%u'", vp, player->GetSession()->GetAccountId()); // VP Exchange 1
					player->GetSession()->SendAreaTriggerMessage("Sucesso !");
					player->AddItem(VOTER_TOKEN, 1);
					player->SaveToDB();
					player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 7:// [10 Voter Points] For [10 Voter Tokens]
				if (vp < 10)
				{
					player->GetSession()->SendAreaTriggerMessage("Voce nao tem os itens necessarios.");
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					LoginDatabase.PExecute("UPDATE account SET vp = '%u' -10 WHERE id = '%u'", vp, player->GetSession()->GetAccountId()); // VP Exchange 10
					player->GetSession()->SendAreaTriggerMessage("Sucesso !");
					player->AddItem(VOTER_TOKEN, 10);
					player->SaveToDB();
					player->CLOSE_GOSSIP_MENU();
				}
				break;

			case 10:// Close Window
				player->CLOSE_GOSSIP_MENU();
				break;

			case 11: // ...Back
				OnGossipHello(player, creature);
				break;
			}
		}

		return true;
	}
};

void AddSC_Donor_Voter_Trader()
{
	new Donor_Voter_Trader();
}