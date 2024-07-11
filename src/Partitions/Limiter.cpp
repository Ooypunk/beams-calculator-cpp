using std::cout;
using std::vector;

class Limiter {

	public:

		vector<vector<int>> limit(vector<vector<int>> partitions, int nr_of_matrs) {
			vector<vector<int>> filtered;

			for (const vector<int> row : partitions) {
				if (row.size() <= nr_of_matrs) {
					filtered.push_back(row);
				}
			}

			return filtered;
		}

};
