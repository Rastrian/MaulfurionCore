local ChatPrefix = "chat"
local WorldChannelName = "Global"
local CooldownTimer = 3

local Class = { 
	[1] = "|cff00ff00|TInterface\\icons\\INV_Sword_27.png:17|t", -- Warrior
	[2] = "|cff00ff00|TInterface\\icons\\INV_Hammer_01.png:17|t", -- Paladin
	[3] = "|cff00ff00|TInterface\\icons\\INV_Weapon_Bow_07.png:17|t", -- Hunter
	[4] = "|cff00ff00|TInterface\\icons\\INV_ThrowingKnife_04.png:17|t", -- Rogue
	[5] = "|cff00ff00|TInterface\\icons\\INV_Staff_30.png:17|t", -- Priest
	[6] = "|cff00ff00|TInterface\\icons\\Spell_Deathknight_ClassIcon.png:17|t", -- DK
	[7] = "|cff00ff00|TInterface\\icons\\inv_jewelry_talisman_04.png:17|t", -- Shaman
	[8] = "|cff00ff00|TInterface\\icons\\INV_Staff_30.png:17|t", -- Mage
	[9] = "|cff00ff00|TInterface\\icons\\INV_Staff_30.png:17|t", -- Warlock
	[11] = "|cff00ff00|TInterface\\icons\\Ability_Druid_Maul.png:17|t", -- Druid
};

local Faction = {
    [0] =  "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Human.png:17|t", -- Ally
    [1] =  "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Orc.png:17|t", -- Horda
};

function ChatSystem(event, plr, cmd)
    local stat = cmd:find(ChatPrefix.." ")
	if (stat == 1) then
        local msg_final = string.gsub(cmd, ChatPrefix.." ", "")
        SendWorldMessage("|cFFCC0066["..WorldChannelName.."] "..Faction[plr:GetTeam()].." "..Class[plr:GetClass()].."|r "..plr:GetName()..": "..msg_final)
        return false
    end
end

RegisterPlayerEvent(42, ChatSystem)
