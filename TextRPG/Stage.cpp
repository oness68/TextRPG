#include <iostream>
#include <map>
#include <string>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace Stage {

	class Stage {
	public:
		std::string description;
		std::map<int, std::string> options;
		std::map<int, std::string> outcomes;

		Stage()
			: description(""),
			options(),
			outcomes() {}

		Stage(const std::string& desc,
			const std::map<int, std::string>& opts,
			const std::map<int, std::string>& outs)
			: description(desc), options(opts), outcomes(outs) {}


		static Stage parseStage(const json& stageJson) {
			std::map<int, std::string> options;
			std::map<int, std::string> outcomes;

			// JSON 데이터에서 options와 outcomes 파싱
			for (auto& [key, value] : stageJson["options"].items())
			{
				options[std::stoi(key)] = value;
			}
			for (auto& [key, value] : stageJson["outcomes"].items())
			{
				outcomes[std::stoi(key)] = value;
			}

			return Stage(stageJson["description"], options, outcomes);
		}

		static std::map<std::string, Stage> loadStages(const std::string& filename)
		{
			std::ifstream file(filename);
			json jsonData;
			file >> jsonData;

			std::map<std::string, Stage> stages;

			for (auto& [stageName, stageJson] : jsonData["stages"].items())
			{
				stages[stageName] = parseStage(stageJson);
			}

			return stages;
		}

	};

}