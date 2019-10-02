/*

- Made by mthsena -

*/
#include "ScriptPCH.h"

class Anti_Farming : public PlayerScript
{
public: Anti_Farming() : PlayerScript("Anti_Farming") {}

		void OnPVPKill(Player * killer, Player * killed)
		{
			if (killer->GetGUID() == killed->GetGUID())
			{
				return;
			}

			if (killer->GetSession()->GetRemoteAddress() == killed->GetSession()->GetRemoteAddress())
			{
				std::string str = "";
				SessionMap ss = sWorld->GetAllSessions();
				for (SessionMap::const_iterator itr = ss.begin(); itr != ss.end(); ++itr)
					if (itr->second->GetSecurity() > 0)
						str = "|cFFFFFF00[Anti-Farming]|cFF00FFFF[|cFF60FF00" + std::string(killer->GetName()) + "|cFF00FFFF] E um possivel farmer de KILL !";
				WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
				data << str;
				sWorld->SendGlobalGMMessage(&data);
			}
		}
};

void AddSC_Anti_Farming()
{
	new Anti_Farming;
}