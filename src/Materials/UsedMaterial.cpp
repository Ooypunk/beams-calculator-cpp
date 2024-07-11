class UsedMaterial {

	private:
		Material material;
		vector<Part> parts;

	public:
		UsedMaterial(Material material) {
			this->material = material;
		}

	/*
	 * General getters
	 */

	Material getMaterial() {
		return this->material;
	}

	vector<Part> getParts() {
		return this->parts;
	}

	/*
	 * Other
	 */

	void addPart(Part part) {
		this->parts.push_back(part);
	}

	bool partFits(Part part) {
		int avail_length = this->getAvailableLength();
		int needed_length = part.getLength();
		return needed_length <= avail_length;
	}

	int getAvailableLength() {
		int used_length = this->getUsedLength();
		int total_length = this->getTotalLength();
		return total_length - used_length;
	}

	int getUsedLength() {
		Register& register_obj = Register::getInstance();
		int saw_thickness = register_obj.getSawWidth();

		int cuts = this->getParts().size() - 1;
		int length = cuts * saw_thickness;
		for (Part part: this->getParts()) {
			length += part.getLength();
		}
		return length;
	}

	int getTotalLength() {
		return this->getMaterial().getLength();
	}

	float getWasteRatio() {
		int total_len = this->getTotalLength();
		int used_len = this->getUsedLength();
		int len_diff = total_len - used_len;
		float waste_pct = ((float) len_diff / (float) total_len) * 100;
		return waste_pct;
	}

	string getMaterialLabel() {
		return this->getMaterial().getLabel();
	}

};
