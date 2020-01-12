int main() {
    int a;
    int b;
    b = 2;
    int c;
    c = b;
    int t1[16];
    int i;
    i = 0;
    while (i < N) {
        t1[i] = i;
        i++;
    }
    a = b * 10;
    while (a > 0) {
        if (a != t1[1] + c) {
            a = a / b;

        };
        printf("ok\n");
        a--;

    }
    return 0;
}
