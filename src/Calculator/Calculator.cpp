using std::cout;

class Calculator {

	private:
		vector<Part> parts_list;
		vector<Material> materials_list;
		GroupedStore grouped_store;
		vector<Group> groups;
		int scenarios_count;

	public:

		Calculator(vector<Part> parts_list, vector<Material> materials_list) {
			this->parts_list = parts_list;
			this->materials_list = materials_list;
		}

		vector<Group> calcAndGetGroups() {
			// Get materials store, grouped on width and height
			this->grouped_store.loadMaterialsList(this->materials_list);

			try {
				// Add parts to their corresponding group (match on width and height)
				this->grouped_store.loadPartsListIntoGroups(this->parts_list);
			} catch (GroupNotFound gnf) {
				cout << gnf.getMessage() << "\n";
			}

			// Now get these groups (materials/parts combinations)
			return this->grouped_store.getGroupsWithParts();
		}

		void addPartitionsToGroups(vector<Group> &groups) {
			for(Group &group: groups) {
				int nr_of_parts = group.getPartsCount();
				int nr_of_matrs = group.getMaterialsCount();

				Partitioner partitioner;
				Limiter limiter;
				Normalizer normalizer;
				Shuffler shuffler;

				vector<vector<int>> partitions = partitioner.getPartitions(nr_of_parts);
				vector<vector<int>> limited_partitions = limiter.limit(partitions, nr_of_matrs);
				vector<vector<int>> normalized_partitions = normalizer.normalize(limited_partitions, nr_of_matrs);
				vector<vector<int>> shuffled_partitions = shuffler.shuffle(normalized_partitions);

				group.setPartitions(shuffled_partitions);
			}
		}

		void addIndexationToGroups(vector<Group> &groups) {
			for(Group &group: groups) {
				IdExpander expander;
				vector<vector<int>> partitions = group.getPartitions();
				vector<vector<vector<int>>> expanded_partitions = expander.expand(partitions);
				group.setIndexed(expanded_partitions);
			}
		}

		void addScenariosToGroups(vector<Group> &groups) {
			this->scenarios_count = 0;
			for(Group &group: groups) {
				for(vector<vector<int>> index_arr: group.getIndexed()) {
					Scenario scenario;
					scenario.setIndexed(index_arr);
					group.addScenario(scenario);

					if (this->scenarios_count % 1000 == 0) {
						cout << "." << std::flush;
						usleep(80000);
					}
					this->scenarios_count++;
				}
			}
			cout << this->scenarios_count << "\n" << std::flush;
			usleep(70000);
		}


		int getNumberOfScenarios() {
			return this->scenarios_count;
		}

		void fillScenarios(vector<Group> &groups) {
			// Fill scenarios with "indexed": for each group, add scenario's for all
			// "indexed" entries, filled with materials and parts (according to
			// their respective "indexed" entry)
			this->fillScenariosInGroups(groups);

			// Calculate waste ratios
			this->calcScenariosInGroups(groups);
		}

		vector<Scenario> getLeastWasteScenarios(vector<Group> groups) {
			vector<Scenario> scenarios;
			for(Group group: groups) {
				vector<Scenario> filtered_scenarios = group.getScenariosWithoutExceptions();

				sort(filtered_scenarios.begin(), filtered_scenarios.end(), this->sortLeastWaste);

				scenarios.push_back(filtered_scenarios.front());
			}
			return scenarios;
		}

	private:

		static bool sortLeastWaste(Scenario scenario1, Scenario scenario2) {
			return scenario1.getWasteRatio() < scenario2.getWasteRatio();
		}

		/**
		 * Fill all scenarios in given groups: fill them with Materials and
		 * Parts
		 * @param vector<Group> &groups
		 * @return void
		 */
		void fillScenariosInGroups(vector<Group> &groups) {
			int count = 0;
			for(Group &group: groups) {
				vector<Material> materials = group.getMaterials();
				vector<Part> parts = group.getParts();
				vector<Scenario> scenarios = group.getScenarios();

				for(Scenario &scenario: scenarios) {
					vector<vector<int>> index_vcr = scenario.getIndexed();
					int mat_idx = 0;
					int part_idx;

					for (vector<int> idx_row: index_vcr) {
						if (idx_row.size() == 0) {
							continue;
						}

						Material material = materials.at(mat_idx);
						UsedMaterial used_material(material);

						for (int cell : idx_row) {
							part_idx = (cell - 1);
							Part part = parts.at(part_idx);
							used_material.addPart(part);
						}

						scenario.addUsedMaterial(used_material);
						mat_idx++;

						if (count % 1000 == 0) {
							cout << "." << std::flush;
							usleep(500000);
						}
						count++;
					}
				}
				group.setScenarios(scenarios);
			}
			cout << count << "\n";
		}

		void calcScenariosInGroups(vector<Group> &groups) {
			for(Group &group: groups) {
			   vector<Scenario> scenarios = group.getScenarios();
			   for(Scenario &scenario: scenarios) {
				   scenario.runCalc();
			   }
			   group.setScenarios(scenarios);
			}
		}

};
