using std::vector;

class BaseImporter {
	
	protected:
		vector<string> header_row;

		void setHeaderRow(vector<string> header_row, std::map<std::string, std::string> mapping) {
			if (header_row.size() <= 1) {
				throw HeaderTooSmall("0 of 1 cellen in header, er gaat iets mis: check het scheidingskarakter");
			}

			vector<string> trimmed;
			for(string cell: header_row) {
				if (cell.front() == '"' && cell.back() == '"') {
					cell.erase(0, 1);
					cell.erase((cell.size() - 1), 1);
				}
				trimmed.push_back(cell);
			}

			vector<string> translated;
			for(string cell: trimmed) {
				string mapped = this->getMappedHeaderCell(cell, mapping);
				translated.push_back(mapped);
			}

			this->header_row = translated;
		}

		string getMappedHeaderCell(string cell, std::map<std::string, std::string> mapping) {
			std::map< std::string, std::string >::iterator MyIterMap; 
			MyIterMap = mapping.begin(); 

			while(MyIterMap != mapping.end() ) {
				std::string key = (*MyIterMap).first; 

				if (mapping[key] == cell) {
					return key;
				}
				MyIterMap++;
			}

			return "not found";
		}

		int getLengthFromRow(vector<string> row) {
			int idx = this->getIdxFromHeader("length");
			if (idx == -1) {
				throw HeaderNotFound("Field 'length' not found in header");
			}
			int cell_val = -1;
			try {
				string cell_str = row.at(idx);
				cell_val = stoi(cell_str);
			} catch (std::invalid_argument iae) {
				std::cerr << "getLengthFromRow(): invalid argument found for length in column " << idx << "\n";
				return cell_val;
			}
			return cell_val;
		}

		int getWidthFromRow(vector<string> row) {
			int idx = this->getIdxFromHeader("width");
			if (idx == -1) {
				throw HeaderNotFound("Field 'width' not found in header");
			}
			int cell_val = -1;
			try {
				string cell_str = row.at(idx);
				cell_val = stoi(cell_str);
			} catch (std::invalid_argument iae) {
				std::cerr << "getWidthFromRow(): invalid argument found for width in column " << idx << "\n";
				return cell_val;
			}
			return cell_val;
		}

		int getHeightFromRow(vector<string> row) {
			int idx = this->getIdxFromHeader("height");
			if (idx == -1) {
				throw HeaderNotFound("Field 'height' not found in header");
			}
			int cell_val = -1;
			try {
				string cell_str = row.at(idx);
				cell_val = stoi(cell_str);
			} catch (std::invalid_argument iae) {
				std::cerr << "getHeightFromRow(): invalid argument found for height in column " << idx << "\n";
				return cell_val;
			}
			return cell_val;
		}

		string getLabelFromRow(vector<string> row) {
			int idx = this->getIdxFromHeader("label");
			if (idx == -1) {
				throw HeaderNotFound("Field 'label' not found in header");
			}
			return row.at(idx);
		}

		int getQuantityFromRow(vector<string> row) {
			int idx1 = this->getIdxFromHeader("qty");
			int idx2 = this->getIdxFromHeader("quantity");
			int cell_val = -1;
			if (idx1 >= 0) {
				try {
					cell_val = stoi(row.at(idx1));
				} catch (std::invalid_argument iae) {
					std::cerr << "getQuantityFromRow()\1: invalid argument found for qty or quantity in column " << idx1 << "\n";
					return cell_val;
				}
				return cell_val;
			}
			if (idx2 >= 0) {
				try {
					string cell_str = row.at(idx2);
					cell_val = stoi(cell_str);
				} catch (std::invalid_argument iae) {
					std::cerr << "getQuantityFromRow()\2: invalid argument found for qty or quantity in column " << idx2 << "\n";
					return cell_val;
				}
				return cell_val;
			}
			return 1;
		}

		int getIdxFromHeader(string search) {
			int idx = 0;
			for(string cell: this->header_row) {
				transform(cell.begin(), cell.end(), cell.begin(), ::tolower);
				transform(search.begin(), search.end(), search.begin(), ::tolower);
				if (cell == search) {
					return idx;
				}
				idx++;
			}
			return -1;
		}

};
