#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Kill_or_Eat

struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
	const unsigned int MAX_DISTANCE = 60;
	unsigned int agressive_units;
	const int UNITS_DEFICIT = 5;
	bool go_agressive;

  //Represents the map, It paints true if that pos is Waste
  vector<vector<bool> > is_waste;
  //vector<Pos> food;
  
	//Initialize the map values
  void ini_map() {
	is_waste = vector<vector<bool> >(board_rows(), vector<bool>(board_cols(), false));

	for (int i = 0; i < board_rows(); ++i)
	  for (int j = 0; j < board_cols(); ++j)
		if (cell(Pos(i, j)).type == Waste) is_waste[i][j] = true;
  }
  
	//Return true if some unit can move to that position
	bool can_move(const Pos& p) {
		return	pos_ok(p) and
						not is_waste[p.i][p.j] and
						(cell(p).id == -1 or
						 unit(cell(p).id).type != Dead
						);
	}

	bool zombie_in(const Pos& p) {
		return cell(p).id != -1 and unit(cell(p).id).type == Zombie;
	}

	bool is_secure(const Pos& p) {
		return	go_agressive or (not zombie_in(p+Up) and
						not zombie_in(p+Down) and
						not zombie_in(p+Left) and
						not zombie_in(p+Right) and
						not zombie_in(p+DR) and
						not zombie_in(p+RU) and
						not zombie_in(p+UL) and
						not zombie_in(p+LD)
						);
	}

	
	//Moves the unit with id id to a food or a zombie
	Dir dir_to_something(int id) {
		struct opt_dir {
			Pos p;
			Dir dir;
			unsigned int distance;
		};

		queue<opt_dir> Q;
		vector<vector<bool> > visited(board_rows(), vector<bool>(board_cols(), false));
		vector<bool> secure_dir(4, false); //{Up, Down, Left, Right}
		Pos p = unit(id).pos;
		visited[p.i][p.j] = true;
		if (can_move(p+Up) and is_secure(p+Up)) {
			Q.push(opt_dir{p+Up, Up, 1}); 
			visited[(p+Up).i][(p+Up).j] = true;
			secure_dir[0] = true;
			if (cell(p+Up).food or zombie_in(p+Up)) return Up;
		}
		if (can_move(p+Down) and is_secure(p+Down)) {
			Q.push(opt_dir{p+Down, Down, 1});
			secure_dir[1] = true;
			visited[(p+Down).i][(p+Down).j] = true;
			if (cell(p+Down).food or zombie_in(p+Down)) return Down;
		}
		if (can_move(p+Left) and is_secure(p+Left)) {
			Q.push(opt_dir{p+Left, Left, 1});
			secure_dir[2] = true;
			visited[(p+Left).i][(p+Left).j] = true;
			if (cell(p+Left).food or zombie_in(p+Left)) return Left;
		}
		if (can_move(p+Right) and is_secure(p+Right)) {
			Q.push(opt_dir{p+Right, Right, 1});
			visited[(p+Right).i][(p+Right).j] = true;
			secure_dir[3] = true;
			if (cell(p+Right).food or zombie_in(p+Right)) return Right;
		}
		while (not Q.empty()) {
			p = Q.front().p;
			Dir d = Q.front().dir;
			unsigned int distance = Q.front().distance; Q.pop();
			if (distance+1 < MAX_DISTANCE and can_move(p+Up) and not visited[(p+Up).i][(p+Up).j]) {
				if (cell(p+Up).food or zombie_in(p+Up)) return d;
				Q.push(opt_dir{p+Up, d, distance+1});
				visited[(p+Up).i][(p+Up).j] = true;
			}
			if (distance+1 < MAX_DISTANCE and can_move(p+Down) and not visited[(p+Down).i][(p+Down).j]) {
				if (cell(p+Down).food or zombie_in(p+Down)) return d;
				Q.push(opt_dir{p+Down, d, distance+1});
				visited[(p+Down).i][(p+Down).j] = true;
			}
			if (distance+1 < MAX_DISTANCE and can_move(p+Left) and not visited[(p+Left).i][(p+Left).j]) {
				if (cell(p+Left).food or zombie_in(p+Left)) return d;
				Q.push(opt_dir{p+Left, d, distance+1});
				visited[(p+Left).i][(p+Left).j] = true;
			}
			if (distance+1 < MAX_DISTANCE and can_move(p+Right) and not visited[(p+Right).i][(p+Right).j]) {
				if (cell(p+Right).food or zombie_in(p+Right)) return d;
				Q.push(opt_dir{p+Right, d, distance+1});
				visited[(p+Right).i][(p+Right).j] = true;
			}
		}
		cerr << "Do not find something" << endl;
		if (secure_dir[0]) return Up;
		if (secure_dir[1]) return Down;
		if (secure_dir[2]) return Left;
		if (secure_dir[3]) return Right;
		return Left;
	}
	

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
		if (round() == 0) {
			agressive_units = alive_units(me()).size() - UNITS_DEFICIT;
			ini_map();
			go_agressive = true;
		}
		//else if (alive_units(me()).size() < agressive_units) go_agressive = false;
		//else go_agressive = true;

		vector<int> alive = alive_units(me());
		for (int id : alive) {
			Dir d = dir_to_something(id);
			move(id, d);
		}
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
