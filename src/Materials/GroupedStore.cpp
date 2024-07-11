class GroupedStore {

	private:
		vector<Group> groups;

	public:

		void loadMaterialsList(vector<Material> materials_list) {
			this->groups.clear();

			for (Material material : materials_list) {
				int width = material.getWidth();
				int height = material.getHeight();
				if (!this->groupIsset(width, height)) {
					this->addGroup(width, height);
				}
				this->addMaterial(material);
			}
		}

		void loadPartsListIntoGroups(vector<Part> parts_list) {
			for (Part part : parts_list) {
				int width = part.getWidth();
				int height = part.getHeight();

				if (!this->groupIsset(width, height)) {
					string msg = "No Group found for Part " + part.getLabelWithDims();
					throw GroupNotFound(msg);
				}
				this->addPart(part);
			}
		}

		vector<Group> getGroupsWithParts() {
			vector<Group> groups;
			for (Group group: this->groups) {
				if (group.hasParts()) {
					groups.push_back(group);
				}
			}
			return groups;
		}

		vector<Group> getGroups() {
			return this->groups;
		}

	private:

		bool groupIsset(int width, int height) {
			for (Group group: this->groups) {
				if (group.getWidth() == width && group.getHeight() == height) {
					return true;
				}
			}
			for (Group group: this->groups) {
				if (group.getWidth() == height && group.getHeight() == width) {
					return true;
				}
			}
			return false;
		}

		void addGroup(int width, int height) {
			Group group;
			group.setWidth(width);
			group.setHeight(height);
			this->groups.push_back(group);
		}

		void addMaterial(Material material) {
			int width = material.getWidth();
			int height = material.getHeight();
			for (Group &group: this->groups) {
				if (group.getWidth() == width && group.getHeight() == height) {
					group.addMaterial(material);
					return;
				}
			}
			for (Group &group: this->groups) {
				if (group.getWidth() == height && group.getHeight() == width) {
					group.addMaterial(material);
					return;
				}
			}
		}

		void addPart(Part part) {
			int width = part.getWidth();
			int height = part.getHeight();
			for (Group &group: this->groups) {
				if (group.getWidth() == width && group.getHeight() == height) {
					group.addPart(part);
					return;
				}
			}
			for (Group &group: this->groups) {
				if (group.getWidth() == height && group.getHeight() == width) {
					group.addPart(part);
					return;
				}
			}
		}

};
