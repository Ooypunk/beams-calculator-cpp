using std::vector;
using std::cout;

class Partitioner {

	private:

		 vector<vector<int>> collection;

	public:

		// A function to add the generated partition to the collection
		void addToCollection(int p[], int n) {
			vector<int> row;
			for (int i = 0; i < n; i++) {
				row.push_back(p[i]);
			}
			this->collection.push_back(row);
		}

		vector<vector<int>> getPartitions(int n) {
			int p[n];
			int k = 0;
			p[k] = n;

			// Loop until all the array elements converted to 1 mean no further partition can be generated.
			while(true) {
				addToCollection(p, k + 1);
				int rem_val = 0;

				// Move the pointer to the index so that p[k] > 1.
				while (k >= 0 && p[k] == 1) {
					rem_val += p[k];
					k--;
				}

				// If k < 0 then the all the element are broken down to 1.
				if (k < 0) {
					break;
					// return;
				}

				// If value greater than 1 is found then decrease it by 1 and increase rem_val to add it to other elements.
				p[k]--;
				rem_val++;

				// Loop until the number of 1's are greater than the value at k index.
				while (rem_val > p[k]) {
					p[k+1] = p[k];
					// Decrease the rem_val value.
					rem_val = rem_val - p[k];
					k++;
				}

				// Assign the remaining value to the index next to k.
				p[k+1] = rem_val;
				k++;
			}

			return this->collection;
		}

};
