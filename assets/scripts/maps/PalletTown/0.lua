if(os.time()-time >= 1) --example: this will execute once per second
then
	local player_pos = world.get_player_pos()
	print(math.floor(player_pos.x/16))
	print(math.floor(player_pos.y/16))
	time = os.time()
end