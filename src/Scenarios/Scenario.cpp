using std::exception;

class Scenario {

	private:
		vector<vector<int>> indexed;
		vector<UsedMaterial> used_materials;
		vector<exception> exceptions;
		float waste_ratio = 0;

	public:

		/*
		 * General getters
		 */

		vector<vector<int>> getIndexed() {
			return this->indexed;
		}

		vector<UsedMaterial> getUsedMaterials() {
			return this->used_materials;
		}

		vector<exception> getExceptions() {
			return this->exceptions;
		}

		float getWasteRatio() {
			return this->waste_ratio;
		}

		/*
		 * General setters
		 */

		void setIndexed(vector<vector<int>> indexed) {
			this->indexed = indexed;
		}

		void setUsedMaterials(vector<UsedMaterial> used_materials) {
			this->used_materials = used_materials;
		}

		/*
		 * "Adder" functions
		 */

		void addUsedMaterial(UsedMaterial used_material) {
			this->used_materials.push_back(used_material);
		}

		/*
		 * "Calculation" functions
		 */

		void assertPartsFitInMaterials() {
			for (UsedMaterial used_material: this->used_materials) {
				int used_len = used_material.getUsedLength();
				int total_len = used_material.getTotalLength();
				if (used_len > total_len) {
					string msg = to_string(used_len) + " gevraagd, ";
					msg += to_string(total_len) + " beschikbaar";
					msg += " van materiaal " + used_material.getMaterialLabel();
					NotEnoughMaterial exception(msg);
					this->addException(exception);
				}
			}
		}

		void runCalc() {
			this->assertPartsFitInMaterials();
			if (this->hasExceptions()) {
				return;
			}

			float ratio = 0;
			for (UsedMaterial used_material:this->used_materials) {
				float um_ratio = used_material.getWasteRatio();
				ratio += um_ratio;
			}
			this->waste_ratio = ratio;
		}

		/*
		 * "Exceptions" functions
		 */

		void addException(exception exception) {
			this->exceptions.push_back(exception);
		}

		bool hasExceptions() {
			return this->exceptions.size() > 0;
		}
};
