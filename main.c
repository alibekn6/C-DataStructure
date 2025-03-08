#include <stdio.h>
#include <string.h>

void greet(const char *string) {
    printf("Hello : %s ", string);
}

int main() {
    char message[] = "Alibek";
    char *string = "Hello";
    
    printf("%s", message);

    printf("\n");

    greet(message);

    return 0;  // Return 0 to indicate successful execution
}
