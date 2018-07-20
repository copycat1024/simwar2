#include <iostream>
#include <string>

#include "client_view.h"
#include "driver.h"
#include "server/entity.h"

using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::to_string;
using namespace simwar::driver;

namespace simwar {

	HeroViewSetup::HeroViewSetup(){
		// board attributes
		fix_height  = 4;
		fix_width   = 15;
		board_color = Color::Black;
		slot_color  = Color::White;
		river_color = Color::White;

		// hero attributes
		active_color = Color::Green;
		damage_color = Color::Red;
		team1_color  = Color::Red;
		team2_color  = Color::Blue;
		dead_color   = Color::White;

		// detail attributes
		value_width  = 6;
		detail_color = Color::Black;
	}

	void HeroViewSetup::print(const ClientModel& model){
		pos_key = model.key_info.at("pos");
		hp_key  = model.key_info.at("hp");
		hid_key = model.key_info.at("hid");

		// count stray keys
		for (auto p: model.key_info){
			keys.insert(p.first);
		}
		keys.erase("hp");
		keys.erase("hid");

		board.moveTo(3,3);
		board.slot_height = keys.size() + fix_height;
		board.slot_width  = fix_width;

		board.back_color  = board_color;
		board.slot_color  = slot_color;
		board.river_color = river_color;

		board.print();
	}

	void HeroView::print(const ClientModel& model, const HeroViewSetup& setup){
		const Hero& hero = model.teams[team][id];
		HeroValue pos = hero.at(setup.pos_key);
		int top  = setup.board.slotTop (team, pos);
		int left = setup.board.slotLeft(team, pos);

		bool active = (model.active_team == team) && (model.active_id == id);
		int dmg_taken = 0;
		for (const auto& d: model.alter_data){
			if (d.team == team && d.id == id && d.key == setup.hp_key) dmg_taken += d.val;
		}

		int team_color = team == 0 ? setup.team1_color : setup.team2_color;
		if (active) team_color = setup.active_color;
		if (hero.at(setup.hp_key)<=0) team_color = setup.dead_color;

		labels.clear();
		bars.clear();

		// status
		if (active){
			Label lab;
			lab.moveTo(left, top);
			lab.width = setup.fix_width;
			lab.align  = Alignment::Center;
			lab.fcolor = setup.active_color;
			lab.bcolor = setup.board.slot_color;
			lab.text = string(6-setup.fix_width%2, '-');
			labels.push_back(lab);
		} else if (dmg_taken < 0){
			Label lab;
			lab.moveTo(left, top);
			lab.width = setup.fix_width;
			lab.align  = Alignment::Center;
			lab.fcolor = setup.damage_color;
			lab.bcolor = setup.board.slot_color;
			lab.text = to_string(-dmg_taken);
			labels.push_back(lab);
		}

		{	// hp
			HeroValue hp = hero.at(setup.hp_key);
			max_hp.set(hp);

			ProgressBar bar;
			bar.moveTo(left+1, top+1);
			bar.width = setup.fix_width-2;
			bar.align  = Alignment::Center;
			bar.fcolor = setup.dead_color;
			bar.bcolor = team_color;
			bar.max   = max_hp.get();
			bar.value = hp > 0 ? hp : 0;
			bar.text  = to_string(hp);
			bars.push_back(bar);
		}

		{	// name
			int hid = hero.at(setup.hid_key);
			string name = model.val_info.at(setup.hid_key).at(hid);
			Label lab;
			lab.moveTo(left, top+2);
			lab.width = setup.fix_width;
			lab.align  = Alignment::Center;
			lab.fcolor = team_color;
			lab.bcolor = setup.board.slot_color;
			lab.text = name;
			labels.push_back(lab);
		}

		{	// breaker
			Label lab;
			lab.moveTo(left, top+setup.fix_height-1);
			lab.width = setup.fix_width;
			lab.align  = Alignment::Center;
			lab.fcolor = setup.detail_color;
			lab.bcolor = setup.board.slot_color;
			lab.text = string(setup.fix_width, '_');
			labels.push_back(lab);
		}

		// setup details
		int i = 0;
		for (auto& key: setup.keys){
			HeroValue val = hero.at(model.key_info.at(key));
			int delta = setup.fix_width-setup.value_width-1;

			{	// key
				Label lab;
				lab.moveTo(left, top+setup.fix_height+i);
				lab.width  = delta;
				lab.align  = Alignment::Left;
				lab.fcolor = setup.detail_color;
				lab.bcolor = setup.board.slot_color;
				lab.text   = key;
				labels.push_back(lab);
			}

			{	// colon
				Label lab;
				lab.moveTo(left+delta, top+setup.fix_height+i);
				lab.width  = 1;
				lab.align  = Alignment::Left;
				lab.fcolor = setup.detail_color;
				lab.bcolor = setup.board.slot_color;
				lab.text   = ":";
				labels.push_back(lab);
			}

			{	// value
				Label lab;
				lab.moveTo(left+delta+1, top+setup.fix_height+i);
				lab.width = setup.value_width;
				lab.align  = Alignment::Right;
				lab.fcolor = setup.detail_color;
				lab.bcolor = setup.board.slot_color;
				lab.text = to_string(val);
				labels.push_back(lab);
			}

			i++;
		}

		// print all
		for (auto& lab: labels){
			lab.print();
		}
		for (auto& bar: bars){
			bar.print();
		}
	}

	ClientView::ClientView(){
		int i;
		for (i=0; i<10; i++){
			hero_views[i].id   = i%5;
			hero_views[i].team = i/5;			
		}
	}

	void ClientView::print(const ClientModel& model){
		clrscr();

		setup.print(model);

		for (auto& hv: hero_views){
			hv.print(model, setup);
		}

		gotoxy(1,1);
		cout << flush;
		waitkey();
	}

	void OneSetValue::set(HeroValue val){
		if (!_set) _val = val;
		_set = true;
	}

	HeroValue OneSetValue::get(){
		return _val;
	}

}
