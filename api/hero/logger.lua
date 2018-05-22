-- Wrapper for log function
Logger = setmetatable({}, {
	__index = function (t, k)
		local fn = function(...)
			local ret = k.."("
			for key,val in pairs({...}) do
				if key > 1 then ret = ret.."," end
				if type(val) == "string" then
					ret = ret.."'"..tostring(val).."'"
				else
					ret = ret..tostring(val)
				end
			end
			ret = ret..")"
			log(ret)
		end
		rawset(t, k, fn)
		return fn
	end
})
