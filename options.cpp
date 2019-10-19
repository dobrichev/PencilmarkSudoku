#define _CRT_SECURE_NO_DEPRECATE

#include <time.h>
#include "options.h"

options opt = options();

options::options() {
	verbose = false;

	//SET PREFERENCES
	//opt->noPOSIX(); //do not check for POSIX style character options
	//anyopt.setVerbose(); // print warnings about unknown options
	//anyopt.autoUsagePrint(true); // print usage for bad options

	//SET THE USAGE/HELP and THE OPTION STRINGS/CHARACTERS
	anyopt.addUsage("");
	anyopt.addUsage("Usage:");
	anyopt.addUsage("" );
	anyopt.addUsage(" -h  --help          Print this help");
	anyopt.setCommandFlag("help", 'h');
	anyopt.addUsage(" -v  --version       Print version");
	anyopt.setCommandFlag("version", 'v');
	anyopt.addUsage(" --verbose           Add plenty of info during execution");
	anyopt.setFlag("verbose");

	anyopt.addUsage(" --solve             Solve puzzles");
	anyopt.setCommandFlag("solve");
	anyopt.addUsage("   --vanilla             Input is vanilla 81-char puzzles (default is 729-char pencilmarks)");
	anyopt.setCommandFlag("vanilla");
	anyopt.addUsage("   --minimals            Check puzzles for minimality");
	anyopt.setFlag("minimals");
	anyopt.addUsage("   --count               Print solution count and reduced pencilmarks");
	anyopt.setFlag("count");
	anyopt.addUsage("     --maxsolutioncount <n>  Solves up to <n>-th solution (INT_MAX)");
	anyopt.setOption("maxsolutioncount");

	anyopt.addUsage(" --backdoor          Print backdoors size & exemplar");
	anyopt.setCommandFlag("backdoor");
	anyopt.addUsage("   --vanilla             Input is vanilla 81-char puzzles (default is 729-char pencilmarks)");
	//anyopt.setCommandFlag("vanilla");

	anyopt.addUsage(" --solrowminlex      Transform valid puzzles to their solution lexicographically minimal row morph");
	anyopt.setCommandFlag("solrowminlex");
	anyopt.addUsage("   --vanilla             Input is vanilla 81-char puzzles (default is 729-char pencilmarks)");
	//anyopt.setCommandFlag("vanilla");

	anyopt.addUsage(" --minimizerandom    Remove all redundant constraints from valid puzzles randomly");
	anyopt.setCommandFlag("minimizerandom");
	anyopt.addUsage("   --vanilla             Input is vanilla 81-char puzzles (default is 729-char pencilmarks)");
	//anyopt.setCommandFlag("vanilla");
	anyopt.addUsage("   --buffersize <n>      Breadth search <n> subgrids are passed to next stage (default 0=disable)");
	anyopt.setOption("buffersize");
	anyopt.addUsage("   --numresults <n>      Stop after <n> puzzles are generated (10)");
	anyopt.setOption("numresults");
	anyopt.addUsage("   --minsize <n>         Ignore puzzles smaller than <n> restrictions (0)");
	anyopt.setOption("minsize");
	anyopt.addUsage("   --maxsize <n>         Ignore puzzles larger than <n> restrictions (729)");
	anyopt.setOption("maxsize");
	anyopt.addUsage("     --maxattempts <n>     Max attempts per input (INT_MAX) for buffersize=0");
	anyopt.setOption("maxattempts");
	anyopt.addUsage("     --maxretries <n>      Max subsequent unsuccessful attempts per input (INT_MAX) for buffersize=0");
	anyopt.setOption("maxretries");

	anyopt.addUsage(" --maximizerandom    Add then remove all redundant constraints from valid puzzles randomly");
	anyopt.setCommandFlag("maximizerandom");
	anyopt.addUsage("   --addclues <n>        Add randomly <n> redundant clues to original (9)");
	anyopt.setOption("addclues");
	anyopt.addUsage("   --addattempts <n>     Repeat adding redundant clues <n> times (600)");
	anyopt.setOption("addattempts");
	anyopt.addUsage("   --minimprovement <n>  Ignore generated puzzles of size < original + <n> (1)");
	anyopt.setOption("minimprovement");
	anyopt.addUsage("   --maxattempts <n>     Max reduce attempts per add attempt (INT_MAX)");
	//anyopt.setOption("maxattempts");
	anyopt.addUsage("   --maxretries <n>      Max reduce subsequent unsuccessful attempts per add attempt (INT_MAX)");
	//anyopt.setOption("maxretries");
	anyopt.addUsage("   --numresults <n>      Stop after <n> puzzles are generated per add attempt (10)");
	//anyopt.setOption("numresults");

	anyopt.addUsage(" --addredundantclues Add redundant constraints to valid puzzles in all possible ways");
	anyopt.setCommandFlag("addredundantclues");
	anyopt.addUsage("   --addclues <n>        Add <n> redundant clues to the original (1)");
	//anyopt.setOption("addclues");

	anyopt.addUsage(" --size              Output column with number of constraints (givens)");
	anyopt.setCommandFlag("size");

	anyopt.addUsage("");

	//by default all  options  will be checked on the command line and from option/resource file
	//anyopt.setFlag("help", 'h');   //a flag (takes no argument), supporting long and short form 
	//anyopt.setOption("size", 's'); //an option (takes an argument), supporting long and short form
	//anyopt.setOption("name");      //an option (takes an argument), supporting only long form
	//anyopt.setFlag('c');           //a flag (takes no argument), supporting only short form

	//for options that will be checked only on the command and line not in option/resource file
	//anyopt.setCommandFlag("zip" , 'z'); //a flag (takes no argument), supporting long and short form

	//for options that will be checked only from the option/resource file
	//anyopt.setFileOption("title");      //an option (takes an argument), supporting only long form
	verbose = false;
	time(&startTime);
}

extern const char *versionString;

bool options::read(int argc, char* argv[]) {
	//PROCESS THE COMMAND LINE AND RESOURCE FILE */
	//read options from a  option/resource file with ':' separated opttions or flags, one per line
	//anyopt.processFile( "/home/user/.options" );  
	//go through the command line and get the options/
	anyopt.processCommandArgs(argc, argv);

	if((!anyopt.hasOptions()) || anyopt.getFlag("help")) { //print usage if no options
		anyopt.printUsage();
		return true;
	}
	verbose = anyopt.getFlag("verbose");
	if(anyopt.getFlag("version")) { //print version and exit
		cout << endl << versionString << endl;
		return true;
	}
	return false;
}

void options::printUsage() {
	anyopt.printUsage();
}

const char* options::getValue(const char* key) {
	return anyopt.getValue(key);
}

int options::getIntValue(const char* key, const int defaultValue) {
	const char* textVal = anyopt.getValue(key);
	if(textVal) return atoi(textVal);
	return defaultValue;
}

bool options::getFlag(const char* key) {
	return anyopt.getFlag(key);
}

const char* options::getStartTime() const {
	return ctime(&startTime);
}

int options::execCommand() {
	if(anyopt.getFlag("solve")) {
		cmdSolve cmd;
		return cmd.exec();
	}
	if(anyopt.getFlag("backdoor")) {
		cmdBackdoor cmd;
		return cmd.exec();
	}
	if(anyopt.getFlag("solrowminlex")) {
		return transform::cmdSolRowMinLex();
	}
	if(anyopt.getFlag("minimizerandom")) {
		return transform::cmdMinimizeRandom();
	}
	if(anyopt.getFlag("maximizerandom")) {
		return transform::cmdMaximizeRandom();
	}
	if(anyopt.getFlag("addredundantclues")) {
		return transform::cmdAddRedundant();
	}
	if(anyopt.getFlag("size")) {
		return transform::cmdSize();
	}
	cout << "Error: No command specified." << endl;
	return -1;
}

