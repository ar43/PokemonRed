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
			pkm.set_player_dir(1)
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
		pkm.set_script(3)
	end
end
