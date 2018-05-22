-- This table includes the standard library for defining hero
SimpleHero = {}

SimpleHero.target = function(map, pos)

	-- Calculate the order of the individual enemy relative to my hero position
	-- Smaller order enemy should be attack first
	local order = function(my_pos, enemy_pos)
		local h = enemy_pos%3
		local l = (enemy_pos-h)/3
		local m = my_pos%3
		if m == 2 then h = 2-h end
		if m == 1 then h = (1-h)%3 end
		return l+h*3
	end

	-- Find the enemy with the lowest order
	local target = map[1]
	for _,v in ipairs(map) do
		if order(pos, v)<order(pos, target) then target = v end
	end
	return target
end

SimpleHero.baseAttack = function()
	print(query.map())
	if 1==1 then return end
	local target = SimpleHero.target(query.map(1), query.pos())
	Caller.take(1, target, state.dmg)
end

SimpleHero.init = function()
	for k, v in pairs(stat) do
		state[k] = v
	end
	Logger.name(lore.name)
	Logger.hp(state.hp)
end

SimpleHero.turn = function()
--	Logger.focus(111)
	SimpleHero.baseAttack()
end

SimpleHero.take = function(t)
	d = t[1]
	state.hp = state.hp - d
	Logger.take(d)
	Logger.hp(state.hp)
end

SimpleHero.dead = function()
--	return state.hp <= 0
	return true
end