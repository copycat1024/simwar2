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
		fix_height = 4;
		fix_width  = 15;
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
		board.print();
	}

	void HeroView::print(const ClientModel& model, const HeroViewSetup& setup){
		const Hero& hero = model.teams[team][id];
		HeroValue pos = hero.at(setup.pos_key);
		int top  = setup.board.slotTop (team, pos);
		int left = setup.board.slotLeft(team, pos);

		labels.empty();
		bars.empty();

		// hp
		{
			HeroValue hp = hero.at(setup.hp_key);
			max_hp.set(hp);

			ProgressBar bar;

			bar.moveTo(left+1, top+1);
			bar.width = setup.fix_width-2;

			bar.align  = Alignment::Center;
			bar.fcolor = Color::White;
			bar.bcolor = Color::Red;

			bar.max   = max_hp.get();
			bar.value = hp >= 0 ? hp : 0;
			bar.text  = to_string(hp);

			bars.push_back(bar);
		}

		// name
		{
			int hid = hero.at(setup.hid_key);
			string name = model.val_info.at(setup.hid_key).at(hid);

			Label lab;

			lab.moveTo(left, top+2);
			lab.width = setup.fix_width;

			lab.align  = Alignment::Center;
			lab.fcolor = Color::Blue;
			lab.bcolor = setup.board.slot_color;

			lab.text = name;

			labels.push_back(lab);
		}

		// breaker
		{
			Label lab;

			lab.moveTo(left, top+setup.fix_height-1);
			lab.width = setup.fix_width;

			lab.align  = Alignment::Center;
			lab.fcolor = Color::Blue;
			lab.bcolor = setup.board.slot_color;

			lab.text = string(setup.fix_width, '_');

			labels.push_back(lab);
		}

		// setup stray keys
		int i = 0;
		for (auto& key: setup.keys){
			Label lab;

			lab.moveTo(left, top+setup.fix_height+i);
			lab.width = setup.fix_width;

			lab.align  = Alignment::Right;
			lab.fcolor = Color::Blue;
			lab.bcolor = setup.board.slot_color;

			lab.text = string(key);

			labels.push_back(lab);
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
