SET @TEXT_ID := 50000;
REPLACE INTO `npc_text` (`ID`, `text0_0`) VALUES
(@TEXT_ID, 'Transmogrification allows you to change how your items look like without changing the stats of the items.\r\nItems used in transmogrification are no longer refundable, tradeable and are bound to you.\r\nUpdating a menu updates the view and prices.\r\n\r\nNot everything can be transmogrified with eachother.\r\nRestrictions include but are not limited to:\r\nOnly armor and weapons can be transmogrified\r\nGuns, bows and crossbows can be transmogrified with eachother\r\nFishing poles can not be transmogrified\r\nYou must be able to equip both items used in the process.\r\n\r\nTransmogrifications stay on your items as long as you own them.\r\nIf you try to put the item in guild bank or mail it to someone else, the transmogrification is stripped.\r\n\r\nYou can also remove transmogrifications for free at the transmogrifier.'),
(@TEXT_ID+1, 'You can save your own transmogrification sets.\r\n\r\nTo save, first you must transmogrify your equipped items.\r\nThen when you go to the set management menu and go to save set menu,\r\nall items you have transmogrified are displayed so you see what you are saving.\r\nIf you think the set is fine, you can click to save the set and name it as you wish.\r\n\r\nTo use a set you can click the saved set in the set management menu and then select use set.\r\nIf the set has a transmogrification for an item that is already transmogrified, the old transmogrification is lost.\r\nNote that same transmogrification restrictions apply when trying to use a set as in normal transmogrification.\r\n\r\nTo delete a set you can go to the set\'s menu and select delete set.');

SET @STRING_ENTRY := 11100;
REPLACE INTO `trinity_string` (`entry`, `content_default`) VALUES
(@STRING_ENTRY+0, 'Item transmogrified'),
(@STRING_ENTRY+1, 'Equipment slot is empty'),
(@STRING_ENTRY+2, 'Invalid source item selected'),
(@STRING_ENTRY+3, 'Source item does not exist'),
(@STRING_ENTRY+4, 'Destination item does not exist'),
(@STRING_ENTRY+5, 'Selected items are invalid'),
(@STRING_ENTRY+6, 'Not enough money'),
(@STRING_ENTRY+7, 'You don\'t have enough tokens'),
(@STRING_ENTRY+8, 'Transmogrifications removed'),
(@STRING_ENTRY+9, 'There are no transmogrifications'),
(@STRING_ENTRY+10, 'Invalid name inserted');


SET
@Entry = 190010,
@Name = "Warpweaver";
DELETE FROM `creature_template` WHERE `entry` = @Entry;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) values
(@Entry,'0','0','0','0','0','19646','0','0','0',@Name,'Transmogrifier',NULL,'0','80','80','2','35','1','1','1.14286','1','0','0','2000','0','1','1','1','0','0','0','0','0','0','0','0','7','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','1','1','1','1','1','0','0','0','0','0','0','0','0','1','0','0','Creature_Transmogrify','0');
