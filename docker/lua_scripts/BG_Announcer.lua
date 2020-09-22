-------------------------------------------------------
-- Created By Rastrian.dev                           //
-- https://rastrian.dev                              //
-- Name: Eluna Script BG End Announcer               //
-- Content: Top Kill, Top Heal and Top Damage scores //
-------------------------------------------------------

local FactionIcon = {
    [1] =  "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Human.png:17|t", -- Ally
    [0] =  "|TInterface\\icons\\Inv_Misc_Tournaments_banner_Orc.png:17|t", -- Horda
};

local Faction = {
    [1] =  "|cff00ccffAliança", -- Ally
    [0] =  "|cffff6060Horda", -- Horda
};

function getBattleID(bgId, getWinnerTeam)
    local BattleID_final = 0;
    local BattleID = CharDBQuery("SELECT id FROM `pvpstats_battlegrounds` WHERE `type` = '"..bgId.."' AND `winner_faction` = '"..getWinnerTeam.."' ORDER BY `date` DESC LIMIT 1;")
    if (BattleID) then
        BattleID_final = BattleID:GetUInt32(0)
    return BattleID_final
    end
end

function getPlayer_Top_Damage(BattleID)
    local player_top_damage_final = "";
    local player_top_damage = CharDBQuery("SELECT `name` FROM characters WHERE guid = (SELECT `character_guid` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_damage_done` DESC LIMIT 1);")
    if (player_top_damage) then
        player_top_damage_final = player_top_damage:GetString(0)
    return player_top_damage_final
    end
end 

function getPlayer_Top_Damage_Value(BattleID)
    local player_top_Damage_Value_final = 0;
    local player_top_Damage_Value = CharDBQuery("SELECT `score_damage_done` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_damage_done` DESC LIMIT 1")
    if (player_top_Damage_Value) then
        player_top_Damage_Value_final = player_top_Damage_Value:GetUInt32(0)
    return player_top_Damage_Value_final
    end
end 

function getPlayer_Top_Heal(BattleID)
    local player_top_Heal_final = "";
    local player_top_Heal = CharDBQuery("SELECT `name` FROM characters WHERE guid = (SELECT `character_guid` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_healing_done` DESC LIMIT 1);")
    if (player_top_Heal) then
--        print(player_top_Heal)
        player_top_Heal_final = player_top_Heal:GetString(0)
    return player_top_Heal_final
    end
end 

function getPlayer_Top_Heal_Value(BattleID)
    local player_top_Heal_Value_final = 0;
    local player_top_Heal_Value = CharDBQuery("SELECT `score_healing_done` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_healing_done` DESC LIMIT 1")
    if (player_top_Heal_Value) then
        player_top_Heal_Value_final = player_top_Heal_Value:GetUInt32(0)
--        print(player_top_Heal_Value)
    return player_top_Heal_Value_final
    end
end 

function getPlayer_Top_Kills(BattleID)
    local player_top_Kills_final = "";
    local player_top_Kills = CharDBQuery("SELECT `name` FROM characters WHERE guid = (SELECT `character_guid` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_honorable_kills` DESC LIMIT 1);")
    if (player_top_Kills) then
        player_top_Kills_final = player_top_Kills:GetString(0)
    return player_top_Kills_final
    end
end 

function getPlayer_Top_Kills_Value(BattleID)
    local player_top_Kills_Value_final = 0;
    local player_top_Kills_Value = CharDBQuery("SELECT `score_honorable_kills` FROM `pvpstats_players` WHERE `battleground_id` = '"..BattleID.."' ORDER BY `score_honorable_kills` DESC LIMIT 1")
    if (player_top_Kills_Value) then
        player_top_Kills_Value_final = player_top_Kills_Value:GetUInt32(0)
    return player_top_Kills_Value_final
    end
end 

function AnnBGEnd(bgId, bgName, teamName, getWinnerTeam, BattleID, instanceId)
    local player_top_kills = ""
    local amount_top_kills = 0
    local player_top_heal = ""
    local amount_top_heal = 0
    local player_top_damage = ""
    local amount_top_damage = 0    

    if BattleID == nil then
        getBattleID(bgId, getWinnerTeam)
    end

    player_top_kills = getPlayer_Top_Kills(BattleID)
    amount_top_kills = getPlayer_Top_Kills_Value(BattleID)
    
    player_top_damage = getPlayer_Top_Damage(BattleID)
    amount_top_damage = getPlayer_Top_Damage_Value(BattleID)
    
    player_top_heal = getPlayer_Top_Heal(BattleID)
    amount_top_heal = getPlayer_Top_Heal_Value(BattleID)
    
--    print(player_top_kills)
--    print(amount_top_kills)
--    print(player_top_damage)
--    print(amount_top_damage)
--    print(player_top_heal)
--    print(amount_top_heal)

    print("|cffC67171[BG] |cffFF4500"..FactionIcon[1].." "..bgName.." "..FactionIcon[0].." - Time Vencedor: "..teamName..". |cffff0000TOP Kill: "..player_top_kills.." ("..amount_top_kills.." kills).|r TOP Damage: "..player_top_damage.." ("..amount_top_damage.."). |cff00FF7FTOP Heal: "..player_top_heal.." ("..amount_top_heal..").")

    for k,player in pairs(GetPlayersInWorld()) do
        player:SendBroadcastMessage("|cffC67171[BG] |cffFF4500"..FactionIcon[1].." "..bgName.." "..FactionIcon[0].." - Time Vencedor: "..teamName..". |cffff0000TOP Kill: "..player_top_kills.." ("..amount_top_kills.." kills).|r TOP Damage: "..player_top_damage.." ("..amount_top_damage.."). |cff00FF7FTOP Heal: "..player_top_heal.." ("..amount_top_heal..").")
    end
end

function OnBGEnd(event, bg, bgId, instanceId)
    local bgName = bg:GetName()
    local getWinnerTeam = bg:GetWinner()
    local teamName = Faction[getWinnerTeam]
    local BattleID = 0
    local BattleID_result = CharDBQuery("SELECT id FROM `pvpstats_battlegrounds` WHERE `type` = '"..bgId.."' AND `winner_faction` = '"..getWinnerTeam.."' ORDER BY `date` DESC LIMIT 1;")
    if (BattleID_result) then
        BattleID = BattleID_result:GetUInt32(0)

--    print("["..bgId.."] "..bgName.." Win: "..teamName)

    if (BattleID) then
        CreateLuaEvent(AnnBGEnd(bgId, bgName, teamName, getWinnerTeam, BattleID, instanceId), 10000, 3)
    end
    end
end

RegisterBGEvent(4, OnBGEnd)

-------------------------------------------------------
-- Created By Rastrian.dev                           //
-- https://rastrian.dev                              //
-- Name: Eluna Script BG End Announcer               //
-- Content: Top Kill, Top Heal and Top Damage scores //
-------------------------------------------------------