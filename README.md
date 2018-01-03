# FilteredDeleter
TLDR: deletes all files in the target folder which does not exist in the source folder, looking only at filenames.

This is a small app to solve a niche problem after photographing big events. For important events (say weddings) I shoot JPG+RAW. RAW files are enormous and enormously slow to flip through. So when I load everything onto a drive and do my first manual culling of the set – throwing out all unusable photos – I only look at the JPGs, leaving me with:
 - a (source) folder of curated (JPG) files (<500 of files, <8GB)
 - a (target) folder with *all* (RAW) files (>1000 of files, >50GB)

This program figures out what JPG-images I kept and makes sure I only keep the matching RAWs – saving me from storing tens of gigabytes of garbage in my archives.

It's the type of problem I'd normally use Python / bash / Perl for, but I wanted to see if could build it reasonably quickly with C++ using STL + the new filesystem library.

I cheated slightly and hard-coded the folders. I began implementing a command line interface but decided that’s really more work than I need to put into it right now. So ~80 lines of code and ~60 minutes, all told, including some cursory testing to verify I wouldn’t nuke my archive. I’m sure the Python version would be much shorter, but I doubt I’d be any faster writing it (and I’d be even slower reading it!).

//Ulf Benjaminsson, 2018
