-- Wrapper for invoke function
Caller = setmetatable({}, {
	__index = function (t, k)
		return function(team, pos, ...)
			invoke(team, pos, k, {...})
		end
	end
})
