#pragma once
#include <string>
#include <algorithm>
#include <vector>
//INCOMPLETE
class ProgramOptions{
private:
	const std::string EMPTY{""};
	std::vector<std::string> _tokens;
public:
	ProgramOptions(const int argc, char* argv[]){
		_tokens.reserve(argc);
		for(int i = 0; i < argc; ++i){
			_tokens.emplace_back(argv[i]);
		}
	}
	const std::string& getOption(const size_t index) const{
		if(index >= _tokens.size()){
			return EMPTY;
		}
		return _tokens[index];		
	}
	const std::string& getOption(const std::string& option) const{
		auto itr = std::find(_tokens.begin(), _tokens.end(), option);
		if(itr != _tokens.end() && ++itr != _tokens.end()){
			return *itr;
		}		
		return EMPTY;
	}
	std::string toString() const{
		std::string out;
		const std::string newLine{"\n"};
		for(const auto& str : _tokens){
			out += str+newLine;
		}
		return out;
	}
	bool optionExists(const std::string& option) const {
		return std::find(_tokens.begin(), _tokens.end(), option) != _tokens.end();
	}
};