class Group {

	private:
		int width;
		int height;
		vector<Material> materials;
		vector<Part> parts;
		vector<vector<int>> partitions;
		vector<vector<vector<int>>> indexed;
		vector<Scenario> scenarios;

	public:

		/*
		 * "Getter" functions
		 */

		int getWidth() {
			return this->width;
		}

		int getHeight() {
			return this->height;
		}

		vector<Material> getMaterials() {
			return this->materials;
		}

		vector<Part> getParts() {
			return this->parts;
		}

		vector<vector<int>> getPartitions() {
			return this->partitions;
		}

		vector<vector<vector<int>>> getIndexed() {
			return this->indexed;
		}

		vector<Scenario> getScenarios() {
			return this->scenarios;
		}

		/*
		 * "Setter" functions
		 */

		void setWidth(int width) {
			this->width = width;
		}

		void setHeight(int height) {
			this->height = height;
		}

		void setPartitions(vector<vector<int>> partitions) {
			this->partitions = partitions;
		}

		void setIndexed(vector<vector<vector<int>>> indexed) {
			this->indexed = indexed;
		}

		void setScenarios(vector<Scenario> scenarios) {
			this->scenarios = scenarios;
		}

		/*
		 * "Adder" functions
		 */

		void addMaterial(Material material) {
			this->materials.push_back(material);
		}

		void addPart(Part part) {
			this->parts.push_back(part);
		}

		void addScenario(Scenario scenario) {
			this->scenarios.push_back(scenario);
		}

		/*
		 * "Hasser" functions
		 */

		bool hasParts() {
			return this->parts.size() > 0;
		}

		bool hasMaterials() {
			return this->materials.size() > 0;
		}

		/*
		 * "Counter" functions
		 */

		int getPartsCount() {
			return this->parts.size();
		}

		int getMaterialsCount() {
			return this->materials.size();
		}

		int getScenariosCount() {
			return this->scenarios.size();
		}

		/*
		 * Other functions
		 */

		string getLabel() {
			string label = "Group " + to_string(this->width) + "x" + to_string(this->height);
			return label;
		}

		vector<Scenario> getScenariosWithoutExceptions() {
			vector<Scenario> filtered;
			for (Scenario scenario: this->scenarios) {
				if (!scenario.hasExceptions()) {
					filtered.push_back(scenario);
				}
			}
			return filtered;
		}

};
