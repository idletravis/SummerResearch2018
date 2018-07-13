#include <iostream>

using namespace std;

class TargetMain
{
    private:
        char buffer[20];
        int numbers[20];

        static void func1()
        {
            cout << "You've found and run function 1!" << endl;
        }

        static void func2()
        {
            cout << "You've found and run function 2!" << endl;
        }

        static void func3()
        {
            cout << "You've found and run function 3!" << endl;
        }
    public:
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
