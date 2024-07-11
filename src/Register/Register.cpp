using std::map;
using json = nlohmann::json;

class Register {

	private:
		Register() {}
		json config_json;

	public:

		static Register& getInstance(){
			static Register the_instance;
			return the_instance;
		}

		/*
		 * Config JSON
		 */
		json getConfigJson() {
			return this->config_json;
		}

		void loadFromJson(json config_json) {
			this->config_json = config_json;
		}

		/*
		 * Getters
		 */
		int getSawWidth() {
			return this->config_json["config"]["saw_width"];
		}

		string getMaterialsFilename() {
			return this->config_json["materials"]["path"];
		}

		string getPartsFilename() {
			return this->config_json["parts"]["path"];
		}

		string getMaterialsImportSeparator() {
			// @todo Als ["materials"]["import"]["separator"] bestaat, dan die teruggeven
			return this->config_json["config"]["import"]["separator"];
		}

		string getPartsImportSeparator() {
			// @todo Als ["parts"]["import"]["separator"] bestaat, dan die teruggeven
			return this->config_json["config"]["import"]["separator"];
		}

};
