dofile("api/hero/std.lua")

lore = {
	name = "Eklit",
}

stat = {
	hp = 100,
	ad = 10,
}

hook.init = SimpleHero.init
hook.turn = SimpleHero.turn
hook.take = SimpleHero.take
hook.dead = SimpleHero.dead
