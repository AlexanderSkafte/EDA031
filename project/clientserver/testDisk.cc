
#include <iostream>
#include "disk_memory_data_base.h"

using namespace std;

int main() {
	cout << "Testing dmdb: " << endl;
    string root_path = "/Users/Andreas/downloads/cppProject/eda031/project/clientserver";
	DiskMemoryDataBase dbmd(root_path);
}
