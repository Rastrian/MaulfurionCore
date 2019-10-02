#include "ScriptPCH.h"

class duell_script : public PlayerScript
{
    public:
        duell_script() : PlayerScript("duell_script") {}

		void OnDuelStart(Player* player1, Player* player2)
		{
				player1->SetHealth(player1->GetMaxHealth());
                player1->SetPower(POWER_MANA, player1->GetMaxPower(POWER_MANA));
                player2->SetHealth(player2->GetMaxHealth());
                player2->SetPower(POWER_MANA, player2->GetMaxPower(POWER_MANA));
                player1->RemoveAllSpellCooldown();
                player2->RemoveAllSpellCooldown();
		}

		void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType /*type*/)
		{
			    winner->SetHealth(winner->GetMaxHealth());
                winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
                loser->SetHealth(loser->GetMaxHealth());
                loser->SetPower(POWER_MANA, loser->GetMaxPower(POWER_MANA));
		}
};

void AddSC_duell_script()
{
    new duell_script;
}