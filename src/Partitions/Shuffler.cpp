using std::cout;
using std::vector;

class Shuffler {

	public:

		vector<vector<int>> shuffle(vector<vector<int>> partitions) {
			vector<vector<int>> shuffled_all;

			for (const vector<int> row : partitions) {
				for (const vector<int> shuffled_row : this->shuffleRow(row)) {
					shuffled_all.push_back(shuffled_row);
				}
			}

			return shuffled_all;
		}

	private:

		vector<vector<int>> shuffleRow(const vector<int> row) {
			vector<vector<int>> rows;

			vector<int> temp_row = row;
			rows.push_back(temp_row);

			for (int i = 0; i < (row.size() - 1); i++) {
				// Get first value, set it as last
				int temp_val = temp_row.front();
				temp_row.push_back(temp_val);
				temp_row.erase(temp_row.begin());

				// Add newly edited row to output vector
				rows.push_back(temp_row);
			}

			return rows;
		}

};
