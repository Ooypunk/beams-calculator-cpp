using std::cout;
using std::vector;

class IdExpander {

	public:

		vector<vector<vector<int>>> expand(vector<vector<int>> partitions) {
			vector<vector<vector<int>>> expanded_all;
			int count = 0;

			for (vector<int> row : partitions) {
				vector<vector<int>> expanded_row = this->expandRow(row);
				expanded_all.push_back(expanded_row);

				if (count % 1000 == 0) {
					cout << "." << std::flush;
					usleep(70000);
				}
				count++;
			}
			cout << count << "\n";

			return expanded_all;
		}

	private:

		vector<vector<int>> expandRow(const vector<int> row) {
			vector<vector<int>> new_row;

			int count = 1;
			for (int cell_val : row) {
				vector<int> new_cell;
				for (int i = 0; i < cell_val; i++) {
					new_cell.push_back(count++);
				}
				new_row.push_back(new_cell);
			}

			return new_row;
		}

};
