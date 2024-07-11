using std::string;
using std::to_string;

class BasePart {

	private:
		int length;
		int width;
		int height;
		string label;
		int number = 0;

	public:

		/*
		 * General getters
		 */

		int getLength() {
			return this->length;
		}

		int getWidth() {
			return this->width;
		}

		int getHeight() {
			return this->height;
		}

		string getLabel() {
			return this->label;
		}

		int getNumber() {
			return this->number;
		}

		/*
		 * General setters
		 */

		void setLength(int length) {
			this->length = length;
		}

		void setWidth(int width) {
			this->width = width;
		}

		void setHeight(int height) {
			this->height = height;
		}

		void setLabel(string label) {
			if (label.front() == '"' && label.back() == '"') {
				label.erase(0, 1);
				label.erase((label.size() - 1), 1);
			}
			this->label = label;
		}

		void setNumber(int number) {
			this->number = number;
		}

		/*
		 * Other
		 */

		string getLabelWithDims() {
			string label = this->label;
			if (this->number > 0) {
				label += " " + to_string(this->number);
			}
			label += " [";
			label += to_string(this->length) + "x";
			label += to_string(this->width) + "x";
			label += to_string(this->height);
			label += "]";
			return label;
		}

};
