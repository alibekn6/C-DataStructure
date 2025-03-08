#include "string.h"


int main() {
    String str = create("HELLO alibek");
    printStr(str);
    append(&str, "again hello");
    printStr(str);
    return 0;
    
}