#include <stdio.h>
#include <ovm/test.h>

int main(int argc, const char* argv[]) {
    int a = 2;
    a = add_two(a);
    printf("Hello, world! %i", a);
}