#include <stdioh>
#define N 16

int main() {
int i;
int ty[N], tx[N];
for (i = 0; i < N/2; i++) {
tx[i] = 1;
}
for (i = N/2; i < N; i++) {
tx[i] = 2;
}
for (i = 0; i < N; i++) {
ty[i] = 2 * N + 1;
}
for (i = N/4; i < 3*N/4; i++) {
ty[i] = (N + 5) * tx[i] + ty[i];
}
return 0;
}
