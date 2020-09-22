local NPC_ID = 999992

local arena = {
        [5] = {"|TInterface\\icons\\achievement_featsofstrength_gladiator_07:40|t Top 10 Arena 1v1"},
        [2]     = {"|TInterface\\icons\\achievement_featsofstrength_gladiator_06:40|t Top 10 Arena 2v2"},
        [3] = {"|TInterface\\icons\\achievement_featsofstrength_gladiator_05:40|t Top 10 Arena 3v3"},
};


function seleciona(event, plr, unit)
        for k, v in pairs(arena) do
                plr:GossipMenuAddItem(0, v[1], 0, k)
        end
        plr:GossipSendMenu(1, unit)
end

function clica(event, plr, unit, arg2, intid)
    if (intid > 0) then
        local resultado = CharDBQuery("SELECT name,rating FROM arena_team WHERE type='"..intid.."' ORDER BY rating DESC LIMIT 10")
        if resultado == nil then
        plr:SendBroadcastMessage("|rSem nenhum time cadastrado.")
        plr:GossipComplete()
        end
        local counter = 1
        repeat
        time = resultado:GetString(0);
        pontos = resultado:GetUInt32(1);
        plr:SendBroadcastMessage("["..counter.."] |cFF33CCFFTime:|r ".. time .." |cFF33CCFFRating:|r " .. pontos .. " pontos de arena.")
        counter = counter + 1
        until not resultado:NextRow()
        plr:GossipComplete()
    end
end
RegisterCreatureGossipEvent(NPC_ID, 1, seleciona)
RegisterCreatureGossipEvent(NPC_ID, 2, clica)
