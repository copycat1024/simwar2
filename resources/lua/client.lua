echo('test')
_ENV = setmetatable(_ENV, {
	__index = function (t, k)
		echo(k)
		_ENV[k] = function(...)
		end
		return _ENV[k]
	end
})
