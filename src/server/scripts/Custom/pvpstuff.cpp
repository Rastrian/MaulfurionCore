/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Edited: Synth
 - Complete: 100%
 - ScriptName: 'npc_changer' 
 - Comment: Tested.
 - Updated: 9/17/13.
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

enum  defines
{
 faction_token = 29434, // Faction Change Token
 race_token = 29434, // Race Change Token
 customize_token = 29434,  // Customize Change Token
 rename_token = 29434, // Rename Change Token
};

class npc_changer : public CreatureScript
{
	public:
		npc_changer() : CreatureScript("npc_changer"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			
			
			pPlayer->ADD_GOSSIP_ITEM(4, "Quero mudar a minha raça.", GOSSIP_SENDER_MAIN, 0);
		    pPlayer->ADD_GOSSIP_ITEM(4, "Quero mudar a minha facção.", GOSSIP_SENDER_MAIN, 1);
            pPlayer->ADD_GOSSIP_ITEM(4, "Quero personalizar o meu personagem.", GOSSIP_SENDER_MAIN, 2);
             pPlayer->ADD_GOSSIP_ITEM(4, "Quero mudar o meu nome.", GOSSIP_SENDER_MAIN, 3);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;

			switch(uiAction)
			{
				case 0:
					if(Player->HasItemCount(race_token, 200))
					{
						Player->DestroyItemCount(race_token, 200, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
						Player->GetSession()->SendNotification("Você necessita de relogar para mudar a sua raça!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("Você necessita de 200 Badge of Justice para mudar de raça!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case 1:
					if(Player->HasItemCount(faction_token, 200))
					{
						Player->DestroyItemCount(faction_token, 200, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						Player->GetSession()->SendNotification("Você necessita de relogar para mudar a sua facção!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
					Player->GetSession()->SendNotification("Você necessita de 200 Badge of Justice para mudar de facção!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
                               case 2:
                                        if(Player->HasItemCount(customize_token, 200))
                                        {
                                                Player->DestroyItemCount(customize_token, 200, true, false);
                                                Player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                                                Player->GetSession()->SendNotification("Você necessita de relogar para se personalizar!");
                                                Player->PlayerTalkClass->SendCloseGossip();
 
                                        }
 
                                        else
                                        {
                                                Player->GetSession()->SendNotification("Você necessita de 200 Badge of Justice para se personalizar!");
                                                Player->PlayerTalkClass->SendCloseGossip();
                                        }
                                        break;                         
                                case 3:
                                        if(Player->HasItemCount(rename_token, 200))
                                        {
                                                Player->DestroyItemCount(rename_token, 200, true, false);
                                                Player->SetAtLoginFlag(AT_LOGIN_RENAME);
                                                Player->GetSession()->SendNotification("Você necessita de relogar para mudar o seu nome!");
												Player->PlayerTalkClass->SendCloseGossip();
 
                                        }
 
                                        else
                                        {
                                                Player->GetSession()->SendNotification("Você necessita de 200 Badge of Justice para mudar de nome!");
                                                Player->PlayerTalkClass->SendCloseGossip();
                                        }
                                        break;
			}
			return true;
		}

};

void AddSC_npc_changer()
{
	new npc_changer();
}