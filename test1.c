#define N 16

int main() {
    int a, b = 2;
    int c = b;
    int t1[N];

    for(int i = 0; i < N; i++)
        t1[i] = c;

    a = b * 10;
    while(a > 0) {
        if(a != t1[1]+c) {
            a = a / b;
        }
        printf("ok\n");
        a--;
    }

    return 0;
}
