#include <iostream>

using namespace std;

class TargetMain
{
    public:
        char buffer[20];
        int numbers[20];

        static void func1()
        {
            string s = "You've found and run function 1!";
            string emptyBuffer;
            cout << s << endl;
        }

        static void func2()
        {
            string s = "You've found and run function 2!";
            string emptyBuffer;
            cout << s << endl;
        }

        static void func3()
        {
            string s = "You've found and run function 3!";
            string emptyBuffer;
            cout << s << endl;
        }

        void printHW()
        {
            cout << "Hello World!" << endl;
        }
};

int main()
{
    TargetMain tm;
    tm.printHW();
    cout << "Hello World!" << endl;
    return 0;
}
