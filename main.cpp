#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <exception>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <ctime>
#include <nlohmann/json.hpp>
#include "src/Exceptions/GroupNotFound.cpp"
#include "src/Exceptions/NotEnoughMaterial.cpp"
#include "src/Exceptions/PartTooLarge.cpp"
#include "src/Exceptions/HeaderNotFound.cpp"
#include "src/Exceptions/HeaderTooSmall.cpp"
#include "src/Partitions/Partitioner.cpp"
#include "src/Partitions/Limiter.cpp"
#include "src/Partitions/Normalizer.cpp"
#include "src/Partitions/Shuffler.cpp"
#include "src/Partitions/IdExpander.cpp"
#include "src/Register/Register.cpp"
#include "src/Base/BasePart.cpp"
#include "src/Materials/Material.cpp"
#include "src/Parts/Part.cpp"
#include "src/Base/BaseImporter.cpp"
#include "src/Materials/MaterialsImporter.cpp"
#include "src/Materials/UsedMaterial.cpp"
#include "src/Parts/PartsImporter.cpp"
#include "src/Scenarios/Scenario.cpp"
#include "src/Materials/Group.cpp"
#include "src/Materials/GroupedStore.cpp"
#include "src/Calculator/Calculator.cpp"

using namespace std;
using json = nlohmann::json;

int getElapsedSeconds(chrono::time_point<chrono::system_clock> start) {
	const chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
	return chrono::duration_cast<chrono::seconds>(now - start).count();
}

void writeElapsedTime(chrono::time_point<chrono::system_clock> start) {
	cout << "Tijd verlopen: " << to_string(getElapsedSeconds(start)) << "s\n";
}

int main(int argc, char** argv) {

	const chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();

	if (argc < 2) {
		cout << "Error: argument verwacht: pad naar config-bestand (JSON)\n";
		return 1;
	}

	std::ifstream f(argv[1]);
	json config_json = json::parse(f);

	Register& register_obj = Register::getInstance();
	register_obj.loadFromJson(config_json);

	PartsImporter parts_importer;
	MaterialsImporter materials_importer;
	vector<Part> parts_list;
	vector<Material> materials_list;

	try {
		parts_list = parts_importer.import();
	} catch (HeaderNotFound hnf) {
		cout << "Error in parts file: " << ": " << hnf.getMessage() << "\n";
		return 1;
	} catch (HeaderTooSmall hts) {
		cout << "Error in parts file: " << ": " << hts.getMessage() << "\n";
		return 1;
	}

	try {
		materials_list = materials_importer.import();
	} catch (HeaderNotFound hnf) {
		cout << "Error in materials file " << ": " << hnf.getMessage() << "\n";
		return 1;
	} catch (HeaderTooSmall hts) {
		cout << "Error in materials file " << ": " << hts.getMessage() << "\n";
		return 1;
	}

	cout << "Aantal Delen in lijst: " << parts_list.size() << "\n";
	cout << "Aantal Materialen in lijst: " << materials_list.size() << "\n";

	writeElapsedTime(start);

	cout << "\n";
	for (Part part: parts_list) {
		cout << part.getLength() << "\t";
		cout << part.getHeight() << "\t";
		cout << part.getWidth() << "\t";
		cout << part.getNumber() << "\t";
		cout << part.getLabelWithDims() << "\n";
	}
	cout << "\n";

	for (Material material: materials_list) {
		cout << material.getLength() << "\t";
		cout << material.getHeight() << "\t";
		cout << material.getWidth() << "\t";
		cout << material.getNumber() << "\t";
		cout << material.getLabelWithDims() << "\n";
	}
	cout << "\n\n";


	cout << "Init Calculator\n";
	Calculator calculator(parts_list, materials_list);
	cout << "Materialen en delen groeperen\n";
	vector<Group> groups = calculator.calcAndGetGroups();
	cout << "Aantal groepen: " << groups.size() << "\n";
	writeElapsedTime(start);

	// Add partitions list to each
	cout << "Partities toevoegen aan groepen\n";
	calculator.addPartitionsToGroups(groups);
	writeElapsedTime(start);

	// Add indexation list to each
	cout << "Indexaties toevoegen aan groepen\n";
	calculator.addIndexationToGroups(groups);
	writeElapsedTime(start);

	// Fill scenarios with "indexed": for each group, add scenario's for all
	// "indexed" entries, filled with materials and parts (according to
	// their respective "indexed" entry)
	cout << "Voeg scenario's toe aan groepen\n";
	calculator.addScenariosToGroups(groups);
	writeElapsedTime(start);

	cout << "Scenario's vullen met materialen and delen\n";
	cout << "Aantal scenario's: " << to_string(calculator.getNumberOfScenarios()) << "\n";

	calculator.fillScenarios(groups);
	writeElapsedTime(start);

	cout << "Calculate which scenario's have the least waste\n";
	vector<Scenario> scenarios = calculator.getLeastWasteScenarios(groups);

	writeElapsedTime(start);

	cout << "\n\nScenarios:\n";
	int j = 0;
	for (Scenario scenario: scenarios) {
		for (UsedMaterial used_material: scenario.getUsedMaterials()) {
			cout << used_material.getMaterial().getLabelWithDims() << "\n";
			for(Part part: used_material.getParts()) {
				cout << "- " << part.getLabelWithDims() << "\n";
			}
			cout << "\n";
		}
	}
	cout << "\nKlaar\n";

};
