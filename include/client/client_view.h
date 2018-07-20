#ifndef SW_CLIENT_VIEW_H
#define SW_CLIENT_VIEW_H

#include <vector>
#include <array>
#include <string>
#include <set>

#include "label.h"
#include "progress_bar.h"
#include "board.h"
#include "client_model.h"

namespace simwar {

	class OneSetValue {
		public:
			void set(HeroValue);
			HeroValue get();
		private:
			bool _set = false;
			HeroValue _val;
	};

	struct HeroViewSetup {
		HeroViewSetup();
		void print(const ClientModel&);

		Board board;
		HeroKey pos_key, hp_key, hid_key;
		std::set<std::string> keys;

		// board attributes
		int fix_height, fix_width;
		int board_color, slot_color, river_color;

		// hero attributes
		int active_color, damage_color;
		int team1_color, team2_color, dead_color;

		// detail attributes
		int value_width;
		int detail_color;
	};

	struct HeroView {
		void print(const ClientModel&, const HeroViewSetup&);

		int team, id;
		OneSetValue	max_hp;
		std::vector<Label>       labels;
		std::vector<ProgressBar> bars;
	};

	struct ClientView {
		ClientView();
		void print(const ClientModel&);

		std::array<HeroView, 10> hero_views;
		HeroViewSetup setup;
	};

};

#endif
