#include <iostream>
#include <string>
#include <set>
#include "logger.h"

using std::endl;
using std::string;
using std::make_pair;
using std::set;

namespace simwar {

	LuaLogger::LuaLogger(SwLogStream& stream, Director& dir): _stream(stream), _dir(dir){
	}

	void LuaLogger::alter(int team, int hero, HeroKey key, HeroValue val){
		_stream << "  alter(";
		_stream << team << ",";
		_stream << hero << ",";
		_stream << key  << ",";
		_stream << val  << ")";
		_stream << endl;
	}

	void LuaLogger::set(int team, int hero, HeroKey key, HeroValue val){
		_val.insert(make_pair(key, val));
		_stream << "  set(";
		_stream << team << ",";
		_stream << hero << ",";
		_stream << key  << ",";
		_stream << val  << ")";
		_stream << endl;
	}

	void LuaLogger::turn(int team, int hero){
		_stream << "  turn(";
		_stream << team << ",";
		_stream << hero << ")";
		_stream << endl;
	}

	void LuaLogger::start(const char * func){
		_stream << "function " << func << "()" << endl;
	}

	void LuaLogger::end(){
		_stream << "end" << endl << endl;
	}

	void LuaLogger::init(const Battle& bat){
		start("init");

		int i,j;
		for (i=0; i<2; i++){
			for (j=0; j<5; j++){
				const auto& hero = bat.team[i].heroes[j];
				for (auto pair: hero){
					set(i, j, pair.first, pair.second);
				}
			}
		}

		end();
	}

	void LuaLogger::info(){
		std::set<HeroKey> _key;
		const auto& key_i = _dir.key_info;
		const auto& val_i = _dir.val_info;

		start("info");

		for (auto p: _val){
			auto k = p.first;
			auto v = p.second;

			_key.insert(k);
			if (val_i.find(k) != val_i.end()){
				const auto& val_ii = val_i.at(k);
				if (val_ii.find(v) != val_ii.end()){
					_val_info(k, v, val_ii.at(v));
				}
			}
		}

		for (auto k: _key){
			if (key_i.find(k) != key_i.end()){
				_key_info(k, key_i.at(k));
			}
		}

		end();
	}

	void LuaLogger::_key_info(HeroKey key, std::string info){
		_stream << "  key_info(";
		_stream << key << ",";
		_stream << "'" << info << "')";
		_stream << endl;
	}

	void LuaLogger::_val_info(HeroKey key, HeroValue val, std::string info){
		_stream << "  val_info(";
		_stream << key << ",";
		_stream << val << ",";
		_stream << "'" << info << "')";
		_stream << endl;
	}

}
