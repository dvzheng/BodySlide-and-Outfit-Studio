/*
BodySlide and Outfit Studio
See the included LICENSE file
*/

#pragma once

#include "../TinyXML-2/tinyxml2.h"

#include <wx/dir.h>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace tinyxml2;

class BuildSelection {
	std::unordered_map<std::string, std::string> outputChoice;
	std::vector<std::string> sourceFiles;

public:
	BuildSelection() { }
	BuildSelection(XMLElement* srcElement) {
		LoadBuildSelection(srcElement);
	}

	bool HasOutputPath(const std::string& search);

	std::unordered_map<std::string, std::string> GetOutputChoices();
	std::string GetOutputChoice(const std::string& outputPath);
	void SetOutputChoice(const std::string& outputPath, const std::string& choice);

	int LoadBuildSelection(XMLElement* srcElement);
};


class BuildSelectionFile {
	XMLDocument doc;
	XMLElement* root;
	int error;

public:
	std::string fileName;
	BuildSelectionFile() :error(0), root(nullptr) { }
	BuildSelectionFile(const std::string& srcFileName);
	~BuildSelectionFile() {};

	bool fail() {
		return error != 0;
	}

	int GetError() {
		return error;
	}

	// Clears all data of the file
	void Clear();

	// Creates a new empty document structure
	void New(const std::string& newFileName);

	// Loads the XML document. On a failure, sets the internal error value.
	void Open(const std::string& srcFileName);

	// Changes the internal file name. The XML file isn't saved until the Save() function is used.
	// Note the original file name is not changed. This method allows you to save build selections as a new file without altering the original.
	void Rename(const std::string& newFileName);

	// Writes the XML file using the internal fileName (use Rename() to change the name).
	bool Save();

	// Get the build selection in the file
	void Get(BuildSelection& outBuildSel);

	// Updates or adds a build selection in the XML document
	int Update(BuildSelection& inBuildSel);
};
