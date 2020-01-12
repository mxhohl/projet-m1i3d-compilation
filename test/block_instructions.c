int main() {

    
    int a = 100, b = a;

    for(int i = 0; i < b; i++) {
        if(a/2 == i) {
            return 0;
        }
        printf("test %d\n", i);
    }

    return 0;
}
