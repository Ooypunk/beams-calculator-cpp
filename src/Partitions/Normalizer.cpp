using std::cout;
using std::vector;

class Normalizer {

	public:

		vector<vector<int>> normalize(vector<vector<int>> partitions, int nr_of_matrs) {
			vector<vector<int>> filtered;

			for (const vector<int> row : partitions) {
				vector<int> new_row;
				for (const int cell : row) {
					new_row.push_back(cell);
				}
				while (new_row.size() < nr_of_matrs) {
					new_row.push_back(0);
				}
				filtered.push_back(new_row);
			}

			return filtered;
		}

};
