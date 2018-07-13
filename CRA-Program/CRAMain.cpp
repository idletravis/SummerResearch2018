#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>

using namespace std;


string objDumpCommand(string fp) //returns the objdump command and outputs to a file in the parent directory
{
    string outfile; outfile.append(fp); outfile.replace(outfile.find(".", outfile.length()-6), outfile.length() ,"-dsmbl.txt"); //appends -dsmbl.txt to the name of the file given
    string command = "objdump -d -M intel "; command.append(fp); command.append(" >> "); command.append(outfile); //creates the objdump command string to be passed to system() and output to file
    cout << "Attempting to output disassembly to output file within the parent directory of selected file. Output file name: " << outfile << endl; //giving user acknowledgement of input
    return command;
}

string askFile() //asks for a filepath to an object file to be disassembled
{
    cout << "Enter the complete filepath for the object file (.obj, .o) to be disassembled. (Must be shorter than 75 characters, including spaces)" << "\n/home/travis/Desktop/Projects/" << std::flush;
    char buffer[75] = "/home/travis/Desktop/Projects/"; //limits filepath to 75 characters, including spaces - set up to include the Projects directory to save time - 30 characters long
    char fp[44]; cin.getline(fp, 44, '\n'); strcat(buffer, fp); //ensures only 75 total characters are stored in buffer, concats filepath to Projects directory - leaves room for '\0' byte
    return buffer; //gives filepath
}

void findLEA() //asks for a file to be read and outputs memory addresses of LEA commands to terminal
{
    char buffer[75] = "/home/travis/Desktop/Projects/";
    cout << "Input a filepath for the file you want to open, starting from the Projects directory:" << endl;
    char fp[44]; cin.getline(fp, 44, '\n');
    strcat(buffer, fp);
    fstream f((string)buffer, ios::in | ios::app);
    string command(64, ' ');
    cout << "Full filepath for file to read from is: " << buffer << endl;
    f.is_open() ? cout << "File has been opened." << endl : cout << "File failed to open." << endl;
    int ind;
    while(!f.eof())
    {
        getline(f, command);
        ind = command.find("lea",0,3);
        if(ind != (signed)string::npos) //not sure why warning for signed comparison is necessary here but not next line vvvvvv (already converted to unsigned when assigned to int?)
            if(command.substr(ind, command.length()).find("ve", ind, 2) == string::npos)
                cout << "Found LEA command:     " << command << endl;
    }
    flush(cout);
    f.close();
}

int main()
{
    system(objDumpCommand(askFile()).c_str());
    findLEA(); //not working
    //cout << "Press 'R' to rerun the program." << endl;
    //char input; cin.get(input); if(input == 'r'){ flush(cout); main();} //intended to rerun the program from the start using recursion. does not work.
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //pauses terminal before it closes
    return 0;
}
