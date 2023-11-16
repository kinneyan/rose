#include <iostream>
#include "capture.hpp"
#include "screenshot-area-selection.hpp"

int main()
{
    AreaSelect areaSelect;

    int selection[4];
    areaSelect.getAreaSelection(selection);

    return 0;
}
