--[[if(os.time()-time >= 1) --example: this will execute once per second
then
	local player_pos = world.get_player_pos()
	print(math.floor(player_pos.x/16))
	print(math.floor(player_pos.y/16))
	time = os.time()
end--]]
if(delay > 0) then
	delay = delay - 1
elseif(pkm.get_script() == 0) then
	if(pkm.check_event("EVENT_FOLLOWED_OAK_INTO_LAB")== false) then
		local player_pos = pkm.get_player_pos()
		if(player_pos.y/16 == 1) then
			print("triggered")
			pkm.text_auto_scroll(true)
			pkm.set_object_dir(0,1)
			pkm.display_text("OakAppearsText",false)
			delay = 10;
			pkm.set_script(1)
		end
	end
elseif(pkm.get_script() == 1) then
	pkm.set_emote(0,0)
	pkm.set_script(2)
elseif(pkm.get_script() == 2) then
	if(pkm.get_emote_time(0) == 0) then
		pkm.close_text()
		pkm.set_freeze(0,true)
		pkm.set_script(3)
		delay = 15;
	end
elseif(pkm.get_script() == 3) then
	if(pkm.get_emote_time(0) == 0) then
		pkm.set_active("HS_PALLET_TOWN_OAK",true)
		pkm.set_event("EVENT_OAK_APPEARED_IN_PALLET",true)
		pkm.set_object_dir(1,0)
		pkm.set_freeze(1,true)
		pkm.set_script(4)
	end
elseif(pkm.get_script() == 4) then
	local player_pos = pkm.get_player_pos()
	if(player_pos.x / 16 == 10) then
		player_on_left = true
		pkm.add_movement(1,0,1)
		pkm.add_movement(1,3,1)
		pkm.add_movement(1,0,1)
		pkm.add_movement(1,3,1)
		pkm.add_movement(1,0,1)
	else 
		player_on_left = false
		pkm.add_movement(1,3,1)
		pkm.add_movement(1,0,1)
		pkm.add_movement(1,3,1)
		pkm.add_movement(1,0,1)
		pkm.add_movement(1,3,1)
		pkm.add_movement(1,0,1)
	end
	pkm.set_script(5)
elseif(pkm.get_script() == 5) then
	if(pkm.is_mq_empty(1) == true) then
		pkm.text_auto_scroll(false)
		pkm.display_text("OakWalksUpText",true)
		pkm.set_script(6)
	end
elseif(pkm.get_script() == 6) then
	if(pkm.get_keycatchers() == 0 and pkm.is_mq_empty(0)) then
		if(player_on_left == false) then
			pkm.add_movement(1,2,1)
			pkm.set_script(7)
		else
			pkm.speedup(1,true)
			pkm.set_object_dir(1,0)
				
			pkm.add_movement(1,1,5)
			pkm.add_movement(1,2,1)
			pkm.add_movement(1,1,5)
			pkm.add_movement(1,3,3)
			pkm.add_movement(1,0,1)
			pkm.add_movement(0,1,6)
			pkm.add_movement(0,2,1)
			pkm.add_movement(0,1,5)
			pkm.add_movement(0,3,3)
			pkm.add_movement(0,0,1)
			pkm.set_script(8)
		end
	end
elseif(pkm.get_script() == 7) then
	if(pkm.is_mq_empty(1) == true) then
		pkm.add_movement(0,2,1)
		pkm.set_script(6)
		player_on_left = true
	end
elseif(pkm.get_script() == 8) then
	if(pkm.is_mq_empty(1) == true) then
		pkm.set_active("HS_PALLET_TOWN_OAK",false)
		pkm.set_script(9)
	end
end

