#include <iostream>
#include "map.h"

using namespace std;

int main() {

    Map<int, int> lst;

    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);
    lst.insert(1, 4);
    lst.insert(11, 5);
    lst.insert(15, 6);
    lst.insert(25, 7);

    lst.Show();

    cout << endl << " ----------------------------------------"<< endl;

    lst.remove(13); //ПРАВИЛЬНЫЙ РЕЗУЛЬТАТ
    lst.Show();
    lst.clear();
    lst.Show();

    return 0;
}