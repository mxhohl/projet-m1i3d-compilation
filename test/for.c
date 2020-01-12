int main() {
    for(int i = 0; i < 5; i++)
        printf("\n");

    int a;
    for(a = 2; a > 0; --a) {
        a = a * 2;
        printf("%d\n", a);
    }

    for (a = 0; a < 10;) {
        printf("%d\n", a);
        ++a;
    }

    return 0;
}
