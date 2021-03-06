﻿// FilteredDeleter deletes all files in the target folder, which does not exist in the source folder. 
// It only looks at file names and ignores file extension. 

// It solves a niche problem for me, after photographing big events. 
// I shoot JPG+RAW. RAW files are enormously slow to flip through. 
// Thus, when I manually cull the set - throwing out all unusable photos - 
// -I only look at the JPGs. Leaving me with:
//    -a (source) folder of curated (JPG) files (<1000s of files, <10GB)</li>
//    -a (target) folder with *all* (RAW) files (>1000s of files, >50GB)</li>
// This program deletes all the unneeded RAW files.

// TODO: implement the command line interface
#include <algorithm>
#include <filesystem>
#include <cctype>
#include <iterator>
#include <iostream>
#include <string>
#include "ProgramOptions.h"
using namespace std::string_literals;
namespace fs = std::experimental::filesystem;
using PathList = std::vector<fs::path>;

PathList getFileList(const fs::path& dir); //returns a sorted list of file paths
PathList getDifference(const PathList& source, const PathList& target);
bool userConfirm(const std::string& message, const std::string& yes = "y"s);
void deleteFiles(const PathList& toRemove);
template<typename C, typename T = fs::path> 
void printEach(const C& v);

int main(int argc, char* argv[]){
	const ProgramOptions opts(argc, argv);		
	const auto source = fs::path{R"(Y:\Temp\WeddingPhotosChosen)"}; //Q&D: hardcoding
	const auto target = fs::path{R"(Y:\Temp\WeddingPhotosRAW)"}; //TODO: use ProgramOptions, commandline interface
	const PathList sourceFiles = getFileList(source);
	const PathList targetFiles = getFileList(target);
	const PathList toRemove = getDifference(sourceFiles, targetFiles);	
	printEach(toRemove);		
	if(userConfirm("Press Y to delete these files."s)){
		deleteFiles(toRemove);
	}
	userConfirm("Done! Double-check the error output\n\tbefore you press any key to quit."s);
	return 0;
}
PathList getDifference(const PathList& sourceFiles, const PathList& targetFiles){
	//Copies the elements from the sorted range [targets) 
	//which are not found in the sorted range [source), to the output list.
	PathList toRemove;
	std::set_difference(targetFiles.begin(), targetFiles.end(),
		sourceFiles.begin(), sourceFiles.end(),
		std::inserter(toRemove, toRemove.begin()),
		[](const fs::path& source, const fs::path& target){
			return source.stem() < target.stem(); //comparing only filenames
		}
	);
	return toRemove;
}
template<typename C, typename T>
void printEach(const C& v){
	std::copy(std::begin(v), std::end(v), std::ostream_iterator<T>{std::cout, ",\n"});
	std::cout << '\n';
}
PathList getFileList(const fs::path& dir){
	PathList out;
	if(!fs::exists(dir) || !fs::is_directory(dir)){
		return out;
	}
	for(const auto& entry : fs::directory_iterator(dir)){
		if(fs::is_regular_file(entry.status())){
			out.push_back(entry.path());
		}
	}
	std::sort(out.begin(), out.end());
	return out;
}
void deleteFiles(const PathList& toRemove){
	for(const auto& file : toRemove){
		if(!is_regular_file(file)){
			std::cerr << "Warning: skipping non-file: "s << file.filename().string();
			continue;
		}
		if(!fs::remove(file)){
			std::cerr << "Error: unable to delete: "s << file.filename().string();
		}
	}
}
bool userConfirm(const std::string& message, const std::string& yes){
	std::cout << message << "\n";
	std::string response;
	std::getline(std::cin, response);
	std::transform(response.begin(), response.end(), response.begin(),
		[](unsigned char c){ return std::tolower(c, std::locale()); }
	);
	return response == yes;
}
