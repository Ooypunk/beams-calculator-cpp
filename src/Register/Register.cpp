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
			try {
				return this->config_json.at("materials").at("import").at("separator");
			} catch (const json::out_of_range& materials_separator_not_found) {
				// Separator mapping not found in "materials", try in "config"
				try {
					return this->config_json.at("config").at("import").at("separator");
				} catch (const json::out_of_range& config_separator_not_found) {
					// Separator mapping not found in "config" either: return default
				}
			}
			return ";";
		}

		string getPartsImportSeparator() {
			try {
				return this->config_json.at("parts").at("import").at("separator");
			} catch (const json::out_of_range& parts_separator_not_found) {
				// Separator mapping not found in "parts", try in "config"
				try {
					return this->config_json.at("config").at("import").at("separator");
				} catch (const json::out_of_range& config_separator_not_found) {
					// Separator mapping not found in "config" either: return default
				}
			}
			return ";";
		}

		std::map<std::string, std::string> getPartsImportMapping() {
			std::map<std::string, std::string> mapping;
			mapping["length"] = this->getPartsImportMappingLength();
			mapping["width"] = this->getPartsImportMappingWidth();
			mapping["height"] = this->getPartsImportMappingHeight();
			mapping["label"] = this->getPartsImportMappingLabel();
			mapping["quantity"] = this->getPartsImportMappingQuantity();
			return mapping;
		}

		string getPartsImportMappingLength() {
			try {
				return this->config_json.at("parts").at("import").at("mapping").at("length");
			} catch (const json::out_of_range& parts_length_not_found) {
				// Length mapping not found in "parts", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("length");
				} catch (const json::out_of_range& config_length_not_found) {
					// Length mapping not found in "config" either: return default
				}
			}
			return "length";
		}

		string getPartsImportMappingWidth() {
			try {
				return this->config_json.at("parts").at("import").at("mapping").at("width");
			} catch (const json::out_of_range& parts_width_not_found) {
				// Width mapping not found in "parts", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("width");
				} catch (const json::out_of_range& config_width_not_found) {
					// Width mapping not found in "config" either: return default
				}
			}
			return "width";
		}

		string getPartsImportMappingHeight() {
			try {
				return this->config_json.at("parts").at("import").at("mapping").at("height");
			} catch (const json::out_of_range& parts_height_not_found) {
				// Height mapping not found in "parts", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("height");
				} catch (const json::out_of_range& config_height_not_found) {
					// Height mapping not found in "config" either: return default
				}
			}
			return "height";
		}

		string getPartsImportMappingLabel() {
			try {
				return this->config_json.at("parts").at("import").at("mapping").at("label");
			} catch (const json::out_of_range& parts_label_not_found) {
				// Label mapping not found in "parts", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("label");
				} catch (const json::out_of_range& config_label_not_found) {
					// Label mapping not found in "config" either: return default
				}
			}
			return "label";
		}

		string getPartsImportMappingQuantity() {
			try {
				return this->config_json.at("parts").at("import").at("mapping").at("quantity");
			} catch (const json::out_of_range& parts_quantity_not_found) {
				// Quantity mapping not found in "parts", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("quantity");
				} catch (const json::out_of_range& config_quantity_not_found) {
					// Quantity mapping not found in "config" either: return default
				}
			}
			return "quantity";
		}

		std::map<std::string, std::string> getMaterialsImportMapping() {
			std::map<std::string, std::string> mapping;
			mapping["length"] = this->getMaterialsImportMappingLength();
			mapping["width"] = this->getMaterialsImportMappingWidth();
			mapping["height"] = this->getMaterialsImportMappingHeight();
			mapping["label"] = this->getMaterialsImportMappingLabel();
			mapping["quantity"] = this->getMaterialsImportMappingQuantity();
			return mapping;
		}

		string getMaterialsImportMappingLength() {
			try {
				return this->config_json.at("materials").at("import").at("mapping").at("length");
			} catch (const json::out_of_range& materials_length_not_found) {
				// Length mapping not found in "materials", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("length");
				} catch (const json::out_of_range& config_length_not_found) {
					// Length mapping not found in "config" either: return default
				}
			}
			return "length";
		}

		string getMaterialsImportMappingWidth() {
			try {
				return this->config_json.at("materials").at("import").at("mapping").at("width");
			} catch (const json::out_of_range& materials_width_not_found) {
				// Width mapping not found in "materials", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("width");
				} catch (const json::out_of_range& config_width_not_found) {
					// Width mapping not found in "config" either: return default
				}
			}
			return "width";
		}

		string getMaterialsImportMappingHeight() {
			try {
				return this->config_json.at("materials").at("import").at("mapping").at("height");
			} catch (const json::out_of_range& materials_height_not_found) {
				// Height mapping not found in "materials", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("height");
				} catch (const json::out_of_range& config_height_not_found) {
					// Height mapping not found in "config" either: return default
				}
			}
			return "height";
		}

		string getMaterialsImportMappingLabel() {
			try {
				return this->config_json.at("materials").at("import").at("mapping").at("label");
			} catch (const json::out_of_range& materials_label_not_found) {
				// Label mapping not found in "materials", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("label");
				} catch (const json::out_of_range& config_label_not_found) {
					// Label mapping not found in "config" either: return default
				}
			}
			return "label";
		}

		string getMaterialsImportMappingQuantity() {
			try {
				return this->config_json.at("materials").at("import").at("mapping").at("quantity");
			} catch (const json::out_of_range& materials_quantity_not_found) {
				// Quantity mapping not found in "materials", try in "config"
				try {
					return this->config_json.at("config").at("import").at("mapping").at("quantity");
				} catch (const json::out_of_range& config_quantity_not_found) {
					// Quantity mapping not found in "config" either: return default
				}
			}
			return "quantity";
		}

};
