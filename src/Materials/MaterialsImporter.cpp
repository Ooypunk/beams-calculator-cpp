using std::vector;

class MaterialsImporter: public BaseImporter {

	public:

		vector<Material> import() {
			Register& register_obj = Register::getInstance();
			string separator = register_obj.getMaterialsImportSeparator();
			string filename = register_obj.getMaterialsFilename();

			std::ifstream input{filename};

			if (!input.is_open()) {
				throw std::invalid_argument("Couldn't read file: " + filename);
			}

			vector<Material> list;

			bool is_first = true;
			for (string line; std::getline(input, line);) {
				// Skip empty line(s)
				if (line.size() == 0) {
					continue;
				}

				std::istringstream ss(std::move(line));
				vector<string> row;
				bool is_paste_mode = false;
				string temp_cell;

				// use std::getline to split line on a character (indicated by separator) into parts
				for (string part; std::getline(ss, part, separator[0]);) {
					// Read parts into row; paste them together if surrounded by '"'
					if (is_paste_mode && part.back() == '"') {
						// In paste mode, end char is ", so finish paste mode
						is_paste_mode = false;
						temp_cell += separator[0] + part.substr(0, (part.length() - 1));
						row.push_back(std::move(temp_cell));
					} else if (is_paste_mode) {
						// In paste mode: paste current part on to the last one
						temp_cell += separator[0] + part;
					} else if (part[0] == '"' && part.back() != '"') {
						// Not in paste mode, but first char is ", so start paste mode
						is_paste_mode = true;
						temp_cell = part.substr(1);
					} else if (part[0] == '"' && part.back() == '"') {
						// Not in paste mode, but first and last char are ": don't
						// start paste mode, just clip off the "
						row.push_back(part.substr(1, (part.length() - 2)));
					} else {
						row.push_back(std::move(part));
					}
				}

				if (is_first) {
					this->setHeaderRow(row);
					is_first = false;
					continue;
				}

				Material part;
				part.setLength(this->getLengthFromRow(row));
				part.setWidth(this->getWidthFromRow(row));
				part.setHeight(this->getHeightFromRow(row));
				part.setLabel(this->getLabelFromRow(row));

				int qty = this->getQuantityFromRow(row);
				if (qty == 1) {
					list.push_back(part);
					continue;
				}

				for (int i = 1; i <= qty; i++) {
					part.setNumber(i);
					list.push_back(part);
				}

			}

			return list;
		}

};
