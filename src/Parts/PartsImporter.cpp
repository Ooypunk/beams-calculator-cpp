using std::vector;
using std::exception;

class PartsImporter: public BaseImporter {

	public:

		vector<Part> import() {
			Register& register_obj = Register::getInstance();
			string separator = register_obj.getPartsImportSeparator();
			string filename = register_obj.getPartsFilename();

			std::ifstream input{filename};

			if (!input.is_open()) {
				throw std::invalid_argument("Couldn't read file: " + filename);
			}

			vector<Part> list;

			bool is_first = true;
			for (string line; std::getline(input, line);) {
				// Skip empty line(s)
				if (line.size() == 0) {
					continue;
				}

				std::istringstream ss(std::move(line));
				vector<string> row;

				// std::getline can split on other characters, here we use ','
				for (string value; std::getline(ss, value, separator[0]);) {
					row.push_back(std::move(value));
				}

				if (is_first) {
					this->setHeaderRow(row);
					is_first = false;
					continue;
				}

				Part part;
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
