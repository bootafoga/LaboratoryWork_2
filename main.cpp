#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "map.h"

using namespace std;

int main(int argc, char* argv[]) {

    Map<int, int> lst;

    cout << "\n~Now make tree and show result~\n\n";
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);
    lst.insert(1, 4);
    lst.insert(11, 5);
    lst.insert(15, 6);
    lst.insert(25, 7);

    lst.Show();

    cout << "\n~Now remove node with key 13 and show result~\n\n";

    lst.remove(13);
    lst.Show();

    cout << "\n~Now clear tree and show result~\n\n";
    lst.clear();
    lst.Show();

    testing::InitGoogleTest(&argc, argv);
    int b = RUN_ALL_TESTS();

    return 0;
}