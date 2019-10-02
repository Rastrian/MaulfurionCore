#include "ScriptPCH.h"
 
class Tools_NPC : public CreatureScript
{
public:
        Tools_NPC() : CreatureScript("Tools_NPC") { }
 
        bool OnGossipHello(Player *player, Creature *creature)
        {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Restaurar HP & Mana", GOSSIP_SENDER_MAIN, 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Resetar Instances", GOSSIP_SENDER_MAIN, 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Resetar Cooldowns", GOSSIP_SENDER_MAIN, 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Resetar Combat", GOSSIP_SENDER_MAIN, 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Remover Sickness", GOSSIP_SENDER_MAIN, 5);
                // player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Reparar Items", GOSSIP_SENDER_MAIN, 6);
				// player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Mais...", GOSSIP_SENDER_MAIN, 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Sair", GOSSIP_SENDER_MAIN, 8);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
        }
        bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
        {
                player->PlayerTalkClass->ClearMenus();
                switch(action)
                {
                case 1: // Restore HP and MP
                        if(player->IsInCombat())
                        {
                                creature->TextEmote("Você está em combate!", player, false);
                                player->CLOSE_GOSSIP_MENU();
                                return false;
                        }
                        else if(player->getPowerType() == POWER_MANA)
                                player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
 
                        player->SetHealth(player->GetMaxHealth());
                        player->CLOSE_GOSSIP_MENU();
                        break;
                case 2: // Reset Instances
                        for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
                        {
                                Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
                                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
                                {
                                        player->UnbindInstance(itr, Difficulty(i));
                                }
                        }
                        player->CLOSE_GOSSIP_MENU();
                        break;
                case 3: // Reset Cooldowns
                        if(player->IsInCombat())
                        {
                                creature->TextEmote("Você está em combate!", player, false);
                                player->CLOSE_GOSSIP_MENU();
                                return false;
                        }
 
                        player->RemoveAllSpellCooldown();
                        player->CLOSE_GOSSIP_MENU();
                        break;
                case 4: // Reset Combat
                        player->CombatStop();
                        player->CLOSE_GOSSIP_MENU();
                        break;
                case 5: // Remove Sickness
                        if(player->HasAura(15007))
                                player->RemoveAura(15007);
 
                        player->CLOSE_GOSSIP_MENU();
                        break;
                case 6: // Repair Items
                        //player->DurabilityRepairAll(false, 0, false);
                        //player->CLOSE_GOSSIP_MENU();
                        break;
                case 7: // Others
                        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Resetar Talentos", GOSSIP_SENDER_MAIN, 71);
                        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Resetar Spells", GOSSIP_SENDER_MAIN, 72);
                        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "...Voltar", GOSSIP_SENDER_MAIN, 73);
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                        break;
                case 8:
                        player->CLOSE_GOSSIP_MENU();
                        break;
                //case 72: // Reset Spells
                //        player->resetSpells();
                //        player->CLOSE_GOSSIP_MENU();
                //        break;
                case 73: // ...Back
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Restorar HP & Mana", GOSSIP_SENDER_MAIN, 1);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Resetar Instances", GOSSIP_SENDER_MAIN, 2);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Resetar Cooldowns", GOSSIP_SENDER_MAIN, 3);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Resetar Combat", GOSSIP_SENDER_MAIN, 4);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Remover Sickness", GOSSIP_SENDER_MAIN, 5);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-> Reparar Items", GOSSIP_SENDER_MAIN, 6);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "->  Mais...", GOSSIP_SENDER_MAIN, 7);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Sair", GOSSIP_SENDER_MAIN, 8);
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                        break;
                }
                return true;
  
      }
};
 
void AddSc_Utilitario()
{
        new Tools_NPC();
}