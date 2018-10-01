#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>

using namespace std;

string locateDir() //locates the CRA-Program directory and returns it for use in the other methods
{
    string dirPath(256, '\0');
    system("sudo find $HOME | grep SummerResearch2018/CRA-Program > deleteThis.txt"); //locates all filepaths that include the CRA-Program directory and outputs to a file to read from later
    fstream f("deleteThis.txt", ios::in | ios::app); //file stream to read from deleteThis.txt
    if(f.is_open()) //this if statement confirms that the file is created, reads the filepath of the CRA-Program directory, then deletes the file used to read from
    {
        getline(f, dirPath); //the first line of the grep command is the filepath for the CRA-Program directory - all other results can be ignored
        string deleteFile(dirPath); deleteFile.append("/deleteThis.txt"); //full path of deleteThis.txt to allow for call to remove()
        remove(deleteFile.c_str()); //requires a const_ char*, which is returned by c_str()
    }
    f.close();
    return dirPath;
}

string askFile(string path) //asks for a relative filepath to an object file to be disassembled
{
    cout << "Enter the relative filepath for the object file (.obj, .o) to be disassembled. (Must be within the CRA-Program directory or any subdirectories)\n" << path << std::flush;
    char fp[40]; cin.getline(fp, 40, '\n'); path.append(fp); //takes in the rest of the filepath to the object file from the user
    return path; //gives filepath
}

string objDumpCommand(string fp) //outputs disassembly to a file in the parent directory and returns the objdump command
{
    string outfile(fp); outfile.replace(outfile.find(".", outfile.length()-6), outfile.length() ,"-dsmbl.txt"); //appends -dsmbl.txt to the name of the file given
    string command = "objdump -d -M intel "; command.append(fp); command.append(" > "); command.append(outfile); //creates the objdump command string to be passed to system() and output to file
    cout << "Attempting to output disassembly to output file within the parent directory of selected file. Output file name: " << outfile << endl; //giving user acknowledgement of input
    return command;
}

void findLEA(string path) //asks for a file to be read and outputs memory addresses of LEA commands to terminal
{
    cout << "To search for LEA instructions, input a filepath for the -dsmbl.txt file previously created, starting from the CRA-Program directory:\n" << path << std::flush;
    char fp[44]; cin.getline(fp, 44, '\n'); path.append(fp);
    fstream f(path, ios::in | ios::app);
    string instr(64, ' ');
    int ind;
    string leaFile(path, 0, path.length()-4); leaFile.append("-LEA.txt"); //stores name of output file to store all LEA instruction output in a file to reference in other functions
    fstream store(leaFile, ios::out | ios::trunc); //if file already exists, the contents need to be overwritten, hence ios::trunc as the mode for output
    store.is_open() ? cout << leaFile << " has been created and opened." << endl : cout << leaFile << " has failed to be created and opened." << endl;
    string line; //temporary string to store each line to be written to file
    while(!f.eof())
    {
        getline(f, instr);
        ind = instr.find("lea",0,3);
        if(ind != (signed)string::npos) //not sure why warning for signed comparison is necessary here but not next line vvvvvv (already converted to unsigned when assigned to int?)
            if(instr.find("leave",0,5) == string::npos)
            {
                cout << "Found LEA instruction:     " << instr << endl;
                line.assign("Found LEA instruction:    "); line.append(instr); //reset line and allow for appending the current instruction
                store << line.c_str() << endl; // formatted output to fstream store, which writes to $filename-LEA.txt
            }
    }
    flush(cout);
    store.close();
    f.close();
}

int main()
{
    //system() requires a const_ char*, which is returned by c_str() - objDumpCommand() returns the prepared objdump linux command
    system(objDumpCommand(askFile(locateDir())).c_str()); //locateDir() is called first and outputs to askFile(), then askFile accepts user input and outputs to objDumpCommand
    findLEA(locateDir()); //not working
    //cout << "Press 'R' to rerun the program." << endl;
    //char input; cin.get(input); if(input == 'r'){ flush(cout); main();} //intended to rerun the program from the start using recursion. does not work.
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //pauses terminal before it closes
    return 0;
}
